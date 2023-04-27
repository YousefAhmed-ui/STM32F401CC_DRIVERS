#ifndef LIN_MASTER_DATA_LAYER_H
#define LIN_MASTER_DATA_LAYER_H

#include "LIN_TYPES.h"
#include "LIN_NETWORK_LAYER.h"

typedef struct{

    u8 Offset_ms;
    u8 Response_Wait_ms;
    Lin_Frame_Slot_t slot;

}Master_Frame_Table_Item_t;

void lin_master_dl_init(Master_Frame_Table_Item_t *Addp_Master_Frame_Item , l_u8 Master_Fram_Table_Size);
t_l_bool lin_master_dl_rx(l_u8 rx_Byte); 
void lin_master_dl_handler(l_u8 ms_passed);
void lin_master_dl_rx_callback(Lin_Frame_Slot_t* slot);

/* this functions by default are handled by lin_mastr_dl_handler */
t_l_bool lin_master_data_tx_header(Lin_Frame_Slot_t  *slot);
t_l_bool lin_master_data_tx_data(Lin_Frame_Slot_t *slot);




#endif