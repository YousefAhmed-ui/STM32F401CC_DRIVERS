#ifndef LIN_SLAVE_DATA_LAYER_H
#define LIN_SLAVE_DATA_LAYER_H

#include "LIN_TYPES.h"

typedef enum{

    LIN_SLAVE_IDLE,
    LIN_SLAVE_SYNC_RX,
    LIN_SLAVE_PID_RX,
    LIN_SLAVE_DATA_RX,
    LIN_SLAVE_DATA_TX

}LIN_Slave_State_t;


extern void lin_Slave_Init(void);

extern void lin_Slave_Reset(void);

extern void lin_Slave_Recieve_Header(l_u8 rx_Byte);

#endif