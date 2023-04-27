


#ifndef LIN_TYPES_H
#define LIN_TYPES_H

#include "STD_TYPES.h"

void myMemCpy(void *dest, void *src, u8 n) 
{ 
    // Typecast src and dest addresses to (char *) 
    char *csrc = (char *)src; 
    char *cdest = (char *)dest; 
    
    // Copy contents of src[] to dest[] 
    for (int i=0; i<n; i++) 
        cdest[i] = csrc[i]; 
} 

#define LIN_MAX_FRAME_LEN                      8U
#define LIN_MAX_FRAME_CHECKSUM_SIAZE           1U
#define L_TRUE                                 TRUE
#define L_FALSE                                FALSE
#define LIN_SYNC_BYTE                          0x55U
#define LIN_ID_MASK                            0x3fU
#define LIN_P0_FLAG                            6
#define LIN_P1_FLAG                            7

#define LIN_DIAG_REQUEST                       0x3CU
#define LIN_DIAG_RESPONSE                      0x3DU

#define LIN_MEMCPY                             myMemCpy

#define LIN_GET_BIT(x,y)                       (((x) >> (y)) & 0x01U)
typedef enum{    
    False,
    True
}t_l_bool;

typedef       u8          l_u8;
typedef       u16         l_u16;
typedef       l_u8        lin_pid_t;
typedef       l_u8        lin_checksum_t;

typedef enum{

    Lin_Frame_Type_Transmit,
    Lin_Frame_Type_Recieve

}LIN_FRAME_t;

typedef enum{

    lin_Ok,
    lin_slave_error_invalid_data_rx,
    lin_slave_error_invalid_checksum,
    lin_slave_error_pid_Parity,
    lin_slave_error_invalid_synch,
    lin_slave_error_invalid_break,
    lin_slave_error_id_not_found,
    lin_slave_error_hw_tx,
    lin_master_error_checksum,
    lin_master_error_header_tx,
    lin_master_error_data_tx,
    lin_master_error_data_rx,
    lin_master_error_data_rx_timeout
    
}t_LIN_ERROR;


void lin_Error_Handler(t_LIN_ERROR Error_Code);

#endif /*LIN_TYPES_H*/