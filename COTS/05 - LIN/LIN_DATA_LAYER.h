


#ifndef LIN_DATA_LAYER_H
#define LIN_DATA_LAYER_H

#include "LIN_TYPES.h"

/*
      Lin Frame Structure
*/

typedef struct{

    lin_pid_t Pid;
    l_u8 Length;
    l_u8 *Data;
    lin_checksum_t Checksum;

}t_LIN_DATA_LAYER_FRAME;

/*
* funtion description : this function calculates th parity for the protected id sent by the lin master
* p0 which is bit 6 in the pid is odd parity and p1 which is bit 7 is even parity
*
* inputs : Pid
*
* output : Calculated Parity from xoring the even and odd bits according to lin specs 2.2A
*/
extern lin_pid_t lin_Data_Layer_Parity(lin_pid_t Pid);
/*
* function description : this function calculates the checksum for the protected id and the data 
*
* inputs : Pid - Data - Length
*
* output : Checksum for all the frame
*/
extern lin_checksum_t lin_Data_Layer_Checksum(lin_pid_t Pid , l_u8 Length ,const l_u8* Data);


#endif