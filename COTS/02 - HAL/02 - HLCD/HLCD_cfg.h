/*******************************************************************/
/*         HLCD Driver         */
/* Target:STM32F401CC                       */
/*Author :Yousef_Ahmed                         */
/*Date   :2023-03-23                                      */
/*******************************************************************/

#ifndef _HLCD_CFG_H
#define _HLCD_CFG_H

#define LCD_DATA_LENGTH_8                    0x10
#define LCD_DATA_LENGTH_4                    0x00

#define LCD_NUM_OF_LINES_1                   0x00                 
#define LCD_NUM_OF_LINES_2                   0x08

#define LCD_FONT_TYPE_5x7                    0x00
#define LCD_FONT_TYPE_5x10                   0x04

#define LCD_DIPLAY_ON                        0x04
#define LCD_DIPLAY_OFF                       0x00

#define LCD_CURSOR_ON                        0x02
#define LCD_CURSOR_OFF                       0x00

#define LCD_BLINK_CURSOR_ON                  0x01
#define LCD_BLINK_CURSOR_OFF                 0x00

#define LCD_FUNCTIONSET_COMMAND              0x20
#define LCD_CLEARDISPLAY_COMMAND             0x01
#define LCD_RETURNHOME_COMMAND               0x02
#define LCD_DISPLAYON_COMMAND                0x08
#define LCD_START_DD_RAM_ADDRESS_COMMAND     0x80
#define LCD_START_CG_RAM_ADDRESS_COMMAND     0x40

#define LCD_BUSYFLAG_ON                      1
#define LCD_BUSYFLAG_OFF                     0

#define LCD_LINE_ONE                         0
#define LCD_LINE_TWO                         1

#define LCD_LINE_ONE_BASE                    0x80
#define LCD_LINE_TWO_BASE                    0xC0

#define LCD_ENABLE_PIN                       2
#define LCD_RW_PIN                           0
#define LCD_RS_PIN                           1

#define LCD_D0_PIN                           3
#define LCD_D1_PIN                           4
#define LCD_D2_PIN                           5
#define LCD_D3_PIN                           6
#define LCD_D4_PIN                           7
#define LCD_D5_PIN                           8
#define LCD_D6_PIN                           9
#define LCD_D7_PIN                           10



#define LCD_PIN_NUMS                         11

#define LCD_BUFFERSIZE                       4

#define LCD_ROWS_NUM                         2
#define LCD_COLUMNS_NUM                      16

/* options

        LCD_DATA_LENGTH_8
        LCD_DATA_LENGTH_4
*/

#define LCD_DATA_LENGTH                      LCD_DATA_LENGTH_8

/* options

        LCD_NUM_OF_LINES_2
        LCD_NUM_OF_LINES_1
*/
#define LCD_NUM_LINES                        LCD_NUM_OF_LINES_2

/* options

        LCD_FONT_TYPE_5x7
        LCD_FONT_TYPE_5x10
*/

#define LCD_FONT_TYPE                        LCD_FONT_TYPE_5x7

/* options

        LCD_DIPLAY_ON
        LCD_DIPLAY_OFF
*/

#define LCD_DISPLAY                          LCD_DIPLAY_ON 

/* options

        LCD_CURSOR_OFF
        LCD_CURSOR_ON
*/

#define LCD_CURSOR                           LCD_CURSOR_OFF

/* options

        LCD_BLINK_CURSOR_OFF
        LCD_BLINK_CURSOR_ON
*/
#define LCD_BLINK_CURSOR                     LCD_BLINK_CURSOR_OFF



typedef struct{
    u8 LCD_u8Port;
    u16 LCD_u16Pin;
    void *LCD_Port;
}LCD_cfg_t;

#endif /*HLCD_CFG_H*/
