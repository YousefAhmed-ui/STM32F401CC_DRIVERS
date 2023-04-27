#ifndef LIN_HW_H
#define LIN_HW_H

#include "LIN_TYPES.h"
/*
* function description : check if hardware break signal is detected
*
* return : true if detected false if not
*/
extern t_l_bool lin_Check_For_break(void);

extern void lin_Hw_Reset(void);

extern void lin_Enable_rx(t_l_bool status);

extern void lin_Hw_Init(void);

extern t_l_bool lin_Hw_Tx_Data(l_u8* Data , l_u8 Len);

extern t_l_bool lin_Hw_Tx_Break(void);

extern t_l_bool lin_Hw_Tx_Byte(l_u8 Data);

#ifdef LIN_AUTO_BAUD
/*
*
* Start auto baud procedure 
*
*/
extern void lin_Hw_Set_AutoBaud(void);

#endif/*LIN_AUTO_BAUD*/

#endif/*LIN_HW_H*/

