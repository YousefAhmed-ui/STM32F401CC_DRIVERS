

#include "LIN_TYPES.h"
#include "LIN_DATA_LAYER.h"
#include "LIN_HW.h"
#include "LIN_NETWORK_LAYER.h"
#include "LIN_SLAVE_DATA_LAYER.h"


static LIN_Slave_State_t Lin_Slave_State;

static l_u8 Lin_Slave_Data_Count;

 
static t_l_bool lin_Slave_Set_Lin_Frame(t_LIN_DATA_LAYER_FRAME* frame)
{
    t_l_bool Res = L_FALSE;

    Lin_Frame_Slot_t *frame_slot = lin_Get_Network_Slot(frame->Pid);

    if(frame_slot != LIN_NETWORK_SLOT_EMPTY){

        frame->Length = frame_slot->Data_Length;

        frame->Data = frame_slot->Data;

        if(frame_slot->Frame_type == Lin_Frame_Type_Transmit){

            Lin_Slave_State = LIN_SLAVE_DATA_TX;

        }else{

             Lin_Slave_State = LIN_SLAVE_DATA_RX;

        }

        Res = L_TRUE;
    }else{
        /* do nothing*/
    }
}

void lin_Slave_Init(void)
{
    lin_Slave_Reset();
}

void lin_Slave_Reset(void)
{
    Lin_Slave_State = LIN_SLAVE_IDLE;

    Lin_Slave_Data_Count = 0;
}

void lin_Slave_Recieve_Header(l_u8 rx_Byte)
{
    static t_LIN_DATA_LAYER_FRAME loc_Data_Frame;

    static l_u8 Lin_Slave_Data_Buff[LIN_MAX_FRAME_LEN];

    if(lin_Check_For_break() == L_TRUE){

        if(Lin_Slave_State != LIN_SLAVE_IDLE){

            lin_Error_Handler(lin_slave_error_invalid_break);

        }else{
            /* do nothing */
        }

        #ifdef LIN_HW_BREAK_IS_SYNCH_BYTE

            Lin_Slave_State = LIN_SLAVE_PID_RX;

        #else

            Lin_Slave_State = LIN_SLAVE_SYNC_RX;

        #endif

        #ifdef OPEN_LIN_AUTO_BAUND
			lin_Hw_Set_AutoBaud();
		#endif       

    }else{

        switch(Lin_Slave_State){

        case LIN_SLAVE_SYNC_RX :
                                if(rx_Byte != LIN_SYNC_BYTE){
                                    
                                    lin_Error_Handler(lin_slave_error_invalid_synch);

                                    lin_Slave_Reset();

                                }else{

                                    Lin_Slave_State = LIN_SLAVE_PID_RX;

                                } 
        break;

        case LIN_SLAVE_PID_RX:
                                if(lin_Data_Layer_Parity(rx_Byte) == rx_Byte){

                                    loc_Data_Frame.Pid = (lin_pid_t)(rx_Byte & LIN_ID_MASK);

                                }else{

                                    lin_Error_Handler(lin_slave_error_pid_Parity);

                                    lin_Slave_Reset();

                                }

                                if(lin_Slave_Set_Lin_Frame(&loc_Data_Frame) == L_TRUE){

                                    if(Lin_Slave_State == LIN_SLAVE_DATA_TX){

                                        loc_Data_Frame.Checksum = lin_Data_Layer_Checksum(loc_Data_Frame.Pid , loc_Data_Frame.Length , loc_Data_Frame.Data);

                                        if((lin_Hw_Tx_Data(loc_Data_Frame.Data , loc_Data_Frame.Length) == L_FALSE) ||
                                        (lin_Hw_Tx_Data(&loc_Data_Frame.Checksum , (l_u8)sizeof(loc_Data_Frame.Checksum)) == L_FALSE)){

                                            lin_Error_Handler(lin_slave_error_hw_tx);

                                            lin_Slave_Reset();

                                        }else{

                                            lin_Slave_Reset();

                                        }              

                                    }
                                }
        break;

        case LIN_SLAVE_DATA_RX:
                                if(Lin_Slave_Data_Count < loc_Data_Frame.Length){

                                    Lin_Slave_Data_Buff[Lin_Slave_Data_Count] = rx_Byte;

                                    Lin_Slave_Data_Count++;                                            

                                }else{

                                    if(rx_Byte == lin_Data_Layer_Checksum(loc_Data_Frame.Data , loc_Data_Frame.Length , Lin_Slave_Data_Buff)){

                                        LIN_MEMCPY(loc_Data_Frame.Data , Lin_Slave_Data_Buff , loc_Data_Frame.Length);

                                        lin_Network_Rx_Handler(loc_Data_Frame.Pid);


                                    }else{

                                        lin_Error_Handler(lin_slave_error_invalid_checksum);

                                    }

                                    lin_Slave_Reset();

                                }
        break;

        default:
                lin_Slave_Reset();

                lin_Error_Handler(lin_slave_error_invalid_data_rx);

        break;                                                        
        }
    }


}