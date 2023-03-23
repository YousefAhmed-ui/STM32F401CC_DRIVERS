/*************************************************************************************************************************/
/* author : yousef ahmed                                                                                                 */
/* date   : 2/6/2022                                                                                                     */
/* version: V01                                                                                                          */
/*************************************************************************************************************************/ 
#ifndef BIT_MATH_h
#define BIT_MATH_h 

#define  SET_BIT(VAR,BIT)    VAR |=  (1<<(BIT))  
#define  CLR_BIT(VAR,BIT)    VAR &= ~(1<<(BIT))
#define  GET_BIT(VAR,BIT)    ((VAR >> BIT)& 1 )
#define  TOG_BIT(VAR,BIT)    VAR ^=  (1<<(BIT)) 


#endif