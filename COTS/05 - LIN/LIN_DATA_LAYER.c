
#include "LIN_TYPES.h"
#include "LIN_DATA_LAYER.h"
#include "LIN_HW.h"


lin_pid_t lin_Data_Layer_Parity(lin_pid_t Pid)
{
    lin_pid_t Res = 0;

    Res = (lin_pid_t)(LIN_GET_BIT(Pid,0) ^ LIN_GET_BIT(Pid , 1) ^ LIN_GET_BIT(Pid , 2) ^ LIN_GET_BIT(Pid , 4)) << LIN_P0_FLAG;

    Res |= (lin_pid_t)(~(LIN_GET_BIT(Pid , 1 ) ^ LIN_GET_BIT(Pid , 3) ^ LIN_GET_BIT(Pid , 4) ^ LIN_GET_BIT(Pid , 5)) << LIN_P1_FLAG);

    Res |=(lin_pid_t)(LIN_ID_MASK & Pid);

    return Res;
}


lin_checksum_t lin_Data_Layer_Checksum(lin_pid_t Pid , l_u8 Length ,const l_u8* Data)
{
    l_u8 i = 0;

    l_u16 Res;

    /*Diagnostic request have classic checksum*/
    if((Pid == LIN_DIAG_REQUEST) || (Pid == LIN_DIAG_RESPONSE)){

        Res = 0;
    
    }else{

        Res = lin_Data_Layer_Parity(Pid);

    }

    for( i = 0 ; i < Length ; i++){

        Res += Data[i];

        if(Res > 0xFF){

            Res -= 0xFF;

        }else{

            /* Do nothing*/

        }

    }

    return (lin_checksum_t)(~Res);

}