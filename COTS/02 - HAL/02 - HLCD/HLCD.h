/*******************************************************************/
/*         HLCD Driver        */
/* Target:STM32F401CC                       */
/*Author :Yousef_Ahmed                         */
/*Date   :2023-03-23                                      */
/*******************************************************************/

#ifndef _HLCD_H
#define _HLCD_H


#include "HLCD_cfg.h"

#define LCD_BUFFERED            1
#define LCD_NOTBUFFERED         0

typedef enum{
    LCD_enuReqIdle,
    LCD_enuReqWrite
}LCD_enuRequest_t;

typedef enum{
    LCD_enuInitStart,
    LCD_enuInitFunctionSet,
    LCD_enuInitClearDisplay,
    LCD_enuInitReturnHome,
    LCD_enuInitDisplayOn,
    LCD_enuInitStartAddress,
    LCD_enuInitDone
}LCD_enuInit_t;

typedef enum{
    LCD_enuWriteStart,
    LCD_enuWriteSetPosition,
    LCD_enuWriteCharacter,
    LCD_enuWriteDone
}LCD_enuWrite_t;

typedef enum{
    LCD_enuOk,
    LCD_enuErrorNullPtr,
    LCD_enuErrorNoBuffer,
    LCD_enuErrorRowNumber,
    LCD_enuErrorColumnNumber
}LCD_enuErrorStatus_t;

typedef struct{
    u8 LCD_String[32];
    u8 LCD_u8PosX;
    u8 LCD_u8PosY;
    u8 LCD_u8Size;
    u8 LCD_CurrPos;
    u8 LCD_u8Buffered;
}LCD_strUserData_t;
/*************************************************************************************************************************/
/* Function_Description : Initialize the LCD                                                                             */
/* Inputs   : void                                                                                                       */
/* Return   : void                                                                                                       */
/*************************************************************************************************************************/
extern void LCD_voidInit(void);
/*************************************************************************************************************************/
/* Function_Description :                                                                                                */
/* Inputs   :                                                                                                            */
/* Return   : Error_status either ok or not                                                                              */
/*************************************************************************************************************************/
extern void LCD_Task(void);
/*************************************************************************************************************************/
/* Function_Description :                                                                                                */
/* Inputs   :                                                                                                            */
/* Return   : Error_status either ok or not                                                                              */
/*************************************************************************************************************************/
extern LCD_enuErrorStatus_t LCD_enuWriteString(const u8 *Add_pu8String , u8 Copy_u8Size , u8 Copy_u8PosX , u8 Copy_u8PosY); 



#endif /*HLCD_H*/
