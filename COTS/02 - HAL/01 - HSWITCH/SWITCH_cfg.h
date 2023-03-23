/*************************************************************************************************************************/
/* author : yousef ahmed                                                                                                 */
/* date   : 21/2/2023                                                                                                    */
/* version: V01                                                                                                          */
/*************************************************************************************************************************/ 
#ifndef SWITCH_CFG_H
#define SWITCH_CFG_H


typedef struct{
    u8 switch_Mode;
    u8 switch_Port;
    u8 switch_Pin;
}SWITCHCfg_t;

typedef enum{
    switch_Start,
    switch_count
}SWITCH_t;


#endif