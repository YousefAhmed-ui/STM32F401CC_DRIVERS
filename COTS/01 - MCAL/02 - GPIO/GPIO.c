/*************************************************************************************************************************/
/* author : yousef ahmed                                                                                                 */
/* date   : 14/1/2022                                                                                                     */
/* version: V01                                                                                                          */
/*************************************************************************************************************************/ 
#include "GPIO.h"

typedef struct{
    u32 MODER;
    u32 OTYPER;
    u32 OSPEEDR;
    u32 PUPDR;
    u32 IDR;
    u32 ODR;
    u32 BSRR;
    u32 LCKR;
    u32 AFRL;
    u32 AFRH;
}GPIOReg_t;


#define GPIOA_BASE_ADD            0x40020000
#define GPIOB_BASE_ADD            0x40020400
#define GPIOC_BASE_ADD            0x40020800
#define GPIOD_BASE_ADD            0x40020C00
#define GPIOE_BASE_ADD            0x40021000
#define GPIOH_BASE_ADD            0x40021C00

#define GPIOA                     ((GPIOReg_t *const)GPIOA_BASE_ADD)
#define GPIOB                     ((GPIOReg_t *const)GPIOB_BASE_ADD)
#define GPIOC                     ((GPIOReg_t *const)GPIOC_BASE_ADD)
#define GPIOD                     ((GPIOReg_t *const)GPIOD_BASE_ADD)
#define GPIOE                     ((GPIOReg_t *const)GPIOE_BASE_ADD)
#define GPIOH                     ((GPIOReg_t *const)GPIOH_BASE_ADD)

#define GET_PIN_MASK               1
#define GPIO_TRUE                  1
#define GPIO_FALSE                 0

#define GET_MODE_MASK              0b11000
#define GET_TYPE_MASK              0b00100
#define GET_PUPDR_MASK             0b00011
#define MODE_SHIFT_MASK            3
#define TYPE_SHIFT_MASK            2
#define REGISTER_OFFSET            2
#define MAX_PIN_CONFIG             65536
#define BSRR_RESET_OFFSET               16

GPIO_enuErrorStatus_t gpio_Init(GPIO_strInit_t * Addp_PortInit)
{
    GPIO_enuErrorStatus_t Local_enuErrorStatus = GPIO_Ok;
    u32 Local_u32ModeReg = 0;
    u32 Local_u32TypeReg  = 0;
    u32 Local_u32PUPReg = 0;
    u16 Local_u16Pin = 0;
    u8 Local_u8Iterator = 0;
    if(Addp_PortInit -> GPIO_Port > MAX_PORT_NUM)
    {
        Local_enuErrorStatus = GPIO_NotOk;
    }
    else if(Addp_PortInit -> GPIO_Pin > MAX_PIN_COUNT)
    {
        Local_enuErrorStatus = GPIO_NotOk;
    }
    else if(Addp_PortInit -> GPIO_Speed > gpio_VERY_HIGH_SPEED)
    {
        Local_enuErrorStatus = GPIO_NotOk;
    }
    else
    {
       for(Local_u8Iterator = 0 ; Local_u8Iterator < GPIO_PIN_NUM ; Local_u8Iterator++)
       {
            Local_u16Pin = (((Addp_PortInit -> GPIO_Pin) >> Local_u8Iterator) & GET_PIN_MASK );

            if( Local_u16Pin == GPIO_TRUE )
            {
                switch( Addp_PortInit -> GPIO_Port )
                {
                    case GPIO_PORTA :

                        Local_u32ModeReg = (((Addp_PortInit -> GPIO_Mode) & GET_MODE_MASK ) >> MODE_SHIFT_MASK );
                        GPIOA -> MODER |= (Local_u32ModeReg << Local_u8Iterator * REGISTER_OFFSET);

                        Local_u32TypeReg = (((Addp_PortInit -> GPIO_Mode) & GET_TYPE_MASK) >> TYPE_SHIFT_MASK);
                        GPIOA -> OTYPER |= (Local_u32TypeReg << Local_u8Iterator);

                        Local_u32PUPReg = ((Addp_PortInit -> GPIO_Mode) &  GET_PUPDR_MASK );
                        GPIOA -> PUPDR |=(Local_u32PUPReg << Local_u8Iterator * REGISTER_OFFSET);

                        GPIOA -> OSPEEDR |= ((Addp_PortInit -> GPIO_Speed) << Local_u8Iterator * REGISTER_OFFSET);

                    break;

                    case GPIO_PORTB :

                        Local_u32ModeReg = (((Addp_PortInit -> GPIO_Mode) & GET_MODE_MASK ) >> MODE_SHIFT_MASK );
                        GPIOB -> MODER |= (Local_u32ModeReg << Local_u8Iterator * REGISTER_OFFSET);

                        Local_u32TypeReg = (((Addp_PortInit -> GPIO_Mode) & GET_TYPE_MASK) >> TYPE_SHIFT_MASK);
                        GPIOB -> OTYPER |= (Local_u32TypeReg << Local_u8Iterator);

                        Local_u32PUPReg = ((Addp_PortInit -> GPIO_Mode) &  GET_PUPDR_MASK );
                        GPIOB -> PUPDR |=(Local_u32PUPReg << Local_u8Iterator * REGISTER_OFFSET);

                        GPIOB -> OSPEEDR |= ((Addp_PortInit -> GPIO_Speed) << Local_u8Iterator * REGISTER_OFFSET);

                    break;

                    case GPIO_PORTC :
                        Local_u32ModeReg = (((Addp_PortInit -> GPIO_Mode) & GET_MODE_MASK ) >> MODE_SHIFT_MASK );
                        GPIOC -> MODER |= (Local_u32ModeReg << Local_u8Iterator * REGISTER_OFFSET);

                        Local_u32TypeReg = (((Addp_PortInit -> GPIO_Mode) & GET_TYPE_MASK) >> TYPE_SHIFT_MASK);
                        GPIOC -> OTYPER |= (Local_u32TypeReg << Local_u8Iterator);

                        Local_u32PUPReg = ((Addp_PortInit -> GPIO_Mode) &  GET_PUPDR_MASK );
                        GPIOC -> PUPDR |=(Local_u32PUPReg << Local_u8Iterator * REGISTER_OFFSET);

                        GPIOC -> OSPEEDR |= ((Addp_PortInit -> GPIO_Speed) << Local_u8Iterator * REGISTER_OFFSET);

                    break;

                    case GPIO_PORTD :

                        Local_u32ModeReg = (((Addp_PortInit -> GPIO_Mode) & GET_MODE_MASK ) >> MODE_SHIFT_MASK );
                        GPIOD -> MODER |= (Local_u32ModeReg << Local_u8Iterator * REGISTER_OFFSET);

                        Local_u32TypeReg = (((Addp_PortInit -> GPIO_Mode) & GET_TYPE_MASK) >> TYPE_SHIFT_MASK);
                        GPIOD -> OTYPER |= (Local_u32TypeReg << Local_u8Iterator);

                        Local_u32PUPReg = ((Addp_PortInit -> GPIO_Mode) &  GET_PUPDR_MASK );
                        GPIOD -> PUPDR |=(Local_u32PUPReg << Local_u8Iterator * REGISTER_OFFSET);

                        GPIOD -> OSPEEDR |= ((Addp_PortInit -> GPIO_Speed) << Local_u8Iterator * REGISTER_OFFSET);

                    break;

                    case GPIO_PORTE :

                        Local_u32ModeReg = (((Addp_PortInit -> GPIO_Mode) & GET_MODE_MASK ) >> MODE_SHIFT_MASK );
                        GPIOE -> MODER |= (Local_u32ModeReg << Local_u8Iterator * REGISTER_OFFSET);

                        Local_u32TypeReg = (((Addp_PortInit -> GPIO_Mode) & GET_TYPE_MASK) >> TYPE_SHIFT_MASK);
                        GPIOE -> OTYPER |= (Local_u32TypeReg << Local_u8Iterator);

                        Local_u32PUPReg = ((Addp_PortInit -> GPIO_Mode) &  GET_PUPDR_MASK );
                        GPIOE -> PUPDR |=(Local_u32PUPReg << Local_u8Iterator * REGISTER_OFFSET);

                        GPIOE -> OSPEEDR |= ((Addp_PortInit -> GPIO_Speed) << Local_u8Iterator * REGISTER_OFFSET);

                    break;

                    case GPIO_PORTH :

                        Local_u32ModeReg = (((Addp_PortInit -> GPIO_Mode) & GET_MODE_MASK ) >> MODE_SHIFT_MASK );
                        GPIOH -> MODER |= (Local_u32ModeReg << Local_u8Iterator * REGISTER_OFFSET);

                        Local_u32TypeReg = (((Addp_PortInit -> GPIO_Mode) & GET_TYPE_MASK) >> TYPE_SHIFT_MASK);
                        GPIOH -> OTYPER |= (Local_u32TypeReg << Local_u8Iterator);

                        Local_u32PUPReg = ((Addp_PortInit -> GPIO_Mode) &  GET_PUPDR_MASK );
                        GPIOH -> PUPDR |=(Local_u32PUPReg << Local_u8Iterator * REGISTER_OFFSET);

                        GPIOH -> OSPEEDR |= ((Addp_PortInit -> GPIO_Speed) << Local_u8Iterator * REGISTER_OFFSET);

                    break;

                }//switch
            }//if
       }//for
    }//else
    return Local_enuErrorStatus;
}


GPIO_enuErrorStatus_t gpio_SetPinValue( void * Copy_voidPtrPort , u16 Copy_u16Pin , u8 Copy_u8PinValue )
{
    GPIO_enuErrorStatus_t Local_enuErroStatus = GPIO_Ok;
    u16 Local_u16CurrentPin = 0 ;
    u8 Local_u8Iterator = 0;
    if( Copy_voidPtrPort == NULL )
    {
        Local_enuErroStatus = GPIO_NotOk;
    }
    else if( Copy_u16Pin > MAX_PIN_CONFIG )
    {
        Local_enuErroStatus = GPIO_NotOk;
    }
    else if( (Copy_u8PinValue != GPIO_SET_VALUE ) && (Copy_u8PinValue != GPIO_RESET_VALUE ) )
    {
        Local_enuErroStatus = GPIO_NotOk;
    }
    else
    {
        for(Local_u8Iterator = 0 ; Local_u8Iterator < GPIO_PIN_NUM ; Local_u8Iterator++)
       {
            Local_u16CurrentPin = ( (Copy_u16Pin >> Local_u8Iterator)  & GET_PIN_MASK );

            if( Local_u16CurrentPin == GPIO_TRUE )
            {
                if( Copy_u8PinValue == GPIO_SET_VALUE)
                {
                    ((GPIOReg_t *)Copy_voidPtrPort) -> BSRR |= (1<<Local_u8Iterator);
                }
                else
                {
                    ((GPIOReg_t *)Copy_voidPtrPort) -> BSRR |= (1<<Local_u8Iterator+BSRR_RESET_OFFSET);
                } 
                //switch( Copy_u8Port )
                //{
                //    case GPIO_PORTA :
                //            if( Copy_u8PinValue == GPIO_SET_VALUE)
                //            {
                //                GPIOA -> BSRR |= (1<<Local_u8Iterator);
                //            }
                //            else // reset the pin
                //            {
                //                GPIOA -> BSRR |= (1<<Local_u8Iterator+BSRR_RESET_OFFSET);
                //            }
//
                //    break;
//
                //    case GPIO_PORTB :
                //            if( Copy_u8PinValue == GPIO_SET_VALUE)
                //            {
                //                GPIOB -> BSRR |= (1<<Local_u8Iterator);
                //            }
                //            else // reset the pin
                //            {
                //                GPIOB -> BSRR |= (1<<Local_u8Iterator+BSRR_RESET_OFFSET);
                //            }
//
                //    break;
//
                //    case GPIO_PORTC :
                //            if( Copy_u8PinValue == GPIO_SET_VALUE)
                //            {
                //                GPIOC -> BSRR |= (1<<Local_u8Iterator);
                //            }
                //            else // reset the pin
                //            {
                //                GPIOC -> BSRR |= (1<<Local_u8Iterator+BSRR_RESET_OFFSET);
                //            }
//
                //    break;
//
                //    case GPIO_PORTD :
                //            if( Copy_u8PinValue == GPIO_SET_VALUE)
                //            {
                //                GPIOD -> BSRR |= (1<<Local_u8Iterator);
                //            }
                //            else // reset the pin
                //            {
                //                GPIOD -> BSRR |= (1<<Local_u8Iterator+BSRR_RESET_OFFSET);
                //            }
//
                //    break;
//
                //    case GPIO_PORTE :
                //            if( Copy_u8PinValue == GPIO_SET_VALUE)
                //            {
                //                GPIOE -> BSRR |= (1<<Local_u8Iterator);
                //            }
                //            else // reset the pin
                //            {
                //                GPIOE -> BSRR |= (1<<Local_u8Iterator+BSRR_RESET_OFFSET);
                //            }
//
                //    break;
//
                //    case GPIO_PORTH :
                //            if( Copy_u8PinValue == GPIO_SET_VALUE)
                //            {
                //                GPIOH -> BSRR |= (1<<Local_u8Iterator);
                //            }
                //            else // reset the pin
                //            {
                //                GPIOH -> BSRR |= (1<<Local_u8Iterator+BSRR_RESET_OFFSET);
                //            }
//
                //    break;                                                                                
//
//
                //}//switch
            }//if
       }//for
    }//else
    return Local_enuErroStatus;
    
}

GPIO_enuErrorStatus_t gpio_GetPinValue( u8 Copy_u8Port , u16 Copy_u16Pin , u8 * Addp_GetVal )
{
    GPIO_enuErrorStatus_t Local_enuErroStatus = GPIO_Ok;
    u32 Local_u32ModeReg = 0;
    u16 Local_u16CurrentPin = 0;
    u8 Local_u8Iterator = 0;
    if( Copy_u8Port > GPIO_PORTH)
    {
        Local_enuErroStatus = GPIO_NotOk;
    }
    else if( Copy_u16Pin > MAX_PIN_CONFIG )
    {
        Local_enuErroStatus = GPIO_NotOk;
    }
    else if( Addp_GetVal == NULL)
    {
         Local_enuErroStatus = GPIO_NotOk;
    }
    else
    {
       for(Local_u8Iterator = 0 ; Local_u8Iterator < GPIO_PIN_NUM ; Local_u8Iterator++)
        {
            Local_u16CurrentPin = ( (Copy_u16Pin >> Local_u8Iterator)  & GET_PIN_MASK );

            if( Local_u16CurrentPin == GPIO_TRUE )
            {
                break;
            }
        }
        switch(Copy_u8Port)
        {
            case GPIO_PORTA :

                     Local_u32ModeReg = (( GPIOA -> MODER ) >> (Local_u8Iterator * REGISTER_OFFSET) ); 

                     *Addp_GetVal  = ((GPIOA -> IDR) >> Local_u8Iterator) & GET_PIN_MASK;
            break;

            case GPIO_PORTB :

                     Local_u32ModeReg = (( GPIOB -> MODER ) >> (Local_u8Iterator * REGISTER_OFFSET) ); 

                     *Addp_GetVal  = ((GPIOB -> IDR) >> Local_u8Iterator) & GET_PIN_MASK;
            break;

            case GPIO_PORTC :

                     Local_u32ModeReg = (( GPIOC -> MODER ) >> (Local_u8Iterator * REGISTER_OFFSET) ); 

                     *Addp_GetVal  = ((GPIOC -> IDR) >> Local_u8Iterator) & GET_PIN_MASK;
            break;

            case GPIO_PORTD :

                     Local_u32ModeReg = (( GPIOD -> MODER ) >> (Local_u8Iterator * REGISTER_OFFSET) ); 

                     *Addp_GetVal  = ((GPIOD -> IDR) >> Local_u8Iterator) & GET_PIN_MASK;
            break;

            case GPIO_PORTE :

                     Local_u32ModeReg = (( GPIOE -> MODER ) >> (Local_u8Iterator * REGISTER_OFFSET) ); 

                     *Addp_GetVal  = ((GPIOE -> IDR) >> Local_u8Iterator) & GET_PIN_MASK;
            break;

            case GPIO_PORTH :

                     Local_u32ModeReg = (( GPIOH -> MODER ) >> (Local_u8Iterator * REGISTER_OFFSET) ); 

                     *Addp_GetVal  = ((GPIOH -> IDR) >> Local_u8Iterator) & GET_PIN_MASK;
            break;                        
        }//switch     
    }//else

    return Local_enuErroStatus;    
}

