

#include "LIN_TYPES.h"
#include "LIN_DATA_LAYER.h"
#include "LIN_NETWORK_LAYER.h"
#include "LIN_HW.h"
#include "LIN_MASTER_DATA_LAYER.h"

typedef enum {
	lin_MASTER_IDLE,
	lin_MASTER_DATA_RX,
	lin_MASTER_TX_DATA,
} t_lin_master_state;

static t_lin_master_state lin_master_state;
static l_u8 master_rx_count = 0;
static l_u8 master_table_index = 0;
static Master_Frame_Table_Item_t *master_frame_table;
static l_u8 master_frame_table_size = 0;
static l_u16 time_passed_since_last_frame_ms = 0;

static void lin_master_goto_idle(t_l_bool next_item);
static void data_layer_next_item(void);
static Master_Frame_Table_Item_t* get_current_item(void);

static void lin_master_goto_idle(t_l_bool next_item)
{
	master_rx_count = 0;
	lin_master_state = lin_MASTER_IDLE;
	time_passed_since_last_frame_ms = 0;
	if (next_item)
	{
		data_layer_next_item();
	} else {
		/* do nothing */
	}
}


void lin_master_dl_init(Master_Frame_Table_Item_t *p_master_frame_table, l_u8 p_master_frame_table_size)
{
	master_frame_table = p_master_frame_table;
	master_frame_table_size = p_master_frame_table_size;
	lin_master_goto_idle(L_FALSE);
}

static Master_Frame_Table_Item_t* get_current_item(void)
{
	return &(master_frame_table[master_table_index]);
}

static void data_layer_next_item(void)
{

	if (master_table_index >= (l_u8)(master_frame_table_size - 1u))
	{
		master_table_index = 0;
	} else {
		master_table_index ++;
	}
}


t_l_bool lin_master_data_tx_header(Lin_Frame_Slot_t  *slot)
{
	t_l_bool result = L_TRUE;
	result = (lin_hw_tx_break()) && result;
	result = (lin_hw_tx_byte(0x55)) && result;
	result = (lin_hw_tx_byte(lin_data_layer_parity(slot->Pid))) && result;
	return result;
}

t_l_bool lin_master_data_tx_data(Lin_Frame_Slot_t *slot)
{
	l_u8 i = 0;
	t_l_bool result = L_TRUE;
	for (i = 0; i < slot->Data_Length; i++)
	{
		result = (lin_hw_tx_byte(slot->Data[i])) && result;
	}

	result = (lin_hw_tx_byte(lin_data_layer_checksum(slot->Pid, slot->Data_Length, slot->Data))) && result;
	return result;
}

t_l_bool lin_master_dl_rx(l_u8 rx_byte)
{
	Lin_Frame_Slot_t* slot = &(get_current_item()->slot);
	static l_u8 frame_tmp_buffer[LIN_MAX_FRAME_LEN];
	t_l_bool pending = False;

	if (lin_master_state == lin_MASTER_DATA_RX)
	{
		if (master_rx_count < slot->Data_Length)
		{
			frame_tmp_buffer[master_rx_count] = rx_byte;
			master_rx_count ++;
			pending = L_TRUE;
		} else
		{
			if (rx_byte == lin_data_layer_checksum(slot->Pid,slot->Data_Length,frame_tmp_buffer))
			{
				(void)lin_memcpy(slot->Data,frame_tmp_buffer,slot->Data_Length);
				lin_master_dl_rx_callback(slot);
			} else
			{
				lin_error_handler(lin_master_error_checksum);
			}
			lin_master_goto_idle(L_TRUE);
		}
	}
	return pending;
}


void lin_master_dl_handler(l_u8 ms_passed)
{
	Master_Frame_Table_Item_t* master_table_item = get_current_item();

	if (master_frame_table_size > 0u)
	{
		time_passed_since_last_frame_ms += ms_passed;
		if (lin_master_state == lin_MASTER_IDLE)
		{
			if ((master_table_item->Offset_ms) < time_passed_since_last_frame_ms)
			{
				time_passed_since_last_frame_ms = 0;
				if (lin_master_data_tx_header(&master_table_item->slot) == L_TRUE)
				{
					if (master_table_item->slot.Frame_type == Lin_Frame_Type_Transmit)
					{
						lin_master_state = lin_MASTER_TX_DATA;
					} else
					{
						lin_master_state = lin_MASTER_DATA_RX;
						master_rx_count = 0;
						lin_set_rx_enabled(L_TRUE);
					}
				} else
				{
					lin_error_handler(lin_master_error_header_tx);
					lin_master_state = lin_MASTER_IDLE;
				}
			}
		} else
		{
			/* do nothing */
		}
		switch (lin_master_state)
		{
			case lin_MASTER_IDLE:
			{
				lin_set_rx_enabled(False);
				/* do nothing */
				break;
			}
			case lin_MASTER_DATA_RX:
			{
				if (time_passed_since_last_frame_ms > master_table_item->Response_Wait_ms)
				{
					lin_error_handler(lin_master_error_data_rx_timeout);
					lin_master_goto_idle(L_TRUE);
				} else
				{
					/*data reception handled by lin_master_data_layer_rx, timeout handled here*/
				}
				break;
			}

			case lin_MASTER_TX_DATA:
			{
				if (lin_master_data_tx_data(&master_table_item->slot) == L_TRUE)
				{
					lin_master_goto_idle(L_TRUE);
				} else
				{
					lin_error_handler(lin_master_error_data_tx);
					lin_master_state = lin_MASTER_IDLE;
				}
				break;
			}
			default:
				/* do nothing */
				break;
		}
	} else {
		/* empty master table do nothing */
	}
}