/*************************************************************************************************************************/
/* author : yousef ahmed                                                                                                 */
/* date   : 21/2/2022                                                                                                     */
/* version: V01                                                                                                          */
/*************************************************************************************************************************/ 
#ifndef HLED_CFG_H 
#define HLED_CFG_H 

typedef struct{
    u8 led_Mode;
    u8 led_Port;    // for Led Init
    u32 LED_PORT;   // for Led set
    u8 led_Speed;
    u16 led_Pin;
    u8 led_Otyper;
}LEDCfg_t;

typedef enum{
    LED_Start,
    LED_count
}LED_t;


#endif
