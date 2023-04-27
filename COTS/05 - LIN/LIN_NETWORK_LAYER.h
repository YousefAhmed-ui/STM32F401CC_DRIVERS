#ifndef LIN_NETWORK_LAYER_H
#define LIN_NETWORK_LAYER_H

#include "LIN_TYPES.h"

#define LIN_NETWORK_SLOT_EMPTY     ((void*)0)


typedef struct{

    lin_pid_t Pid;
    LIN_FRAME_t Frame_type;
    l_u8 Data_Length;
    l_u8* Data;

}Lin_Frame_Slot_t;

#ifdef LIN_DYNAMIC_IDS

    typedef struct{

        lin_pid_t Id_In_Lin_Table;
        lin_pid_t input_Id;

    }Lin_Id_Translation_Item_t;

#endif /*LIN_DYNAMIC_IDS*/

extern Lin_Frame_Slot_t* lin_Get_Network_Slot(lin_pid_t Pid);

extern void lin_Network_Rx_Handler(lin_pid_t Pid);

extern void lin_Network_Init(Lin_Frame_Slot_t* Slot_Array , l_u8 Slot_Array_Len);

extern void lin_On_Rx_Frame(Lin_Frame_Slot_t *Slot);


#endif /*LIN_NETWORK_LAYER_H*/