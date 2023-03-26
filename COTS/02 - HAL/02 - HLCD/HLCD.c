/******************************************************************/
/*HLCD Driver                */
/* Target:STM32F401CC                       */
/* Yousef_Ahmed                              */
/* Date:2023-03-23                                       */
/******************************************************************/

#include "STD_TYPES.h"
#include "GPIO.h"
#include "HLCD.h"

typedef enum{
    LCD_enuEnableOff,
    LCD_enuEnableOn
}LCD_enuEnableState_t;

static void LCD_voidSendCommand(u8 Copy_u8Command , u8 Copy_u8RWValue , u8 Copy_u8RSValue);
static void LCD_voidSetEnable(u8 Copy_u8Value);
static void LCD_voidInitProcess(void);
static void LCD_voidWriteProcess(void);


static LCD_enuInit_t        LCD_enuInitState   = LCD_enuInitStart;
static LCD_enuWrite_t       LCD_enuWriteState  = LCD_enuWriteStart;
static LCD_enuEnableState_t LCD_enuEnable      = LCD_enuEnableOff;
static LCD_enuRequest_t     LCD_enuCurrRequest = LCD_enuReqIdle;

static u8   LCD_u8BusyFlag        = LCD_BUSYFLAG_OFF;
static u8   LCD_u8CurrentBuffer   = 0;
static u8   LCD_u8CurrentPosition = 0;
static u8   LCD_u8BufferIndex     = 0;

static LCD_strUserData_t LCD_strUserData[LCD_BUFFERSIZE];

extern const LCD_cfg_t LCD_Pins[LCD_PIN_NUMS];



void LCD_voidInit(void)
{
    u8 Local_u8PinIndex = 0;

    GPIO_strInit_t lcd_cfg;

    for(Local_u8PinIndex = 0 ; Local_u8PinIndex < LCD_PIN_NUMS ; Local_u8PinIndex++)
    {
        lcd_cfg.GPIO_Port = LCD_Pins[Local_u8PinIndex].LCD_u8Port;
        lcd_cfg.GPIO_Pin = LCD_Pins[Local_u8PinIndex].LCD_u16Pin;
        lcd_cfg.GPIO_Mode = gpio_OUPUT_PP_MODE;
        lcd_cfg.GPIO_Speed = gpio_MEDIUM_SPEED;

        gpio_Init(&lcd_cfg);
    }

    LCD_u8BusyFlag = LCD_BUSYFLAG_ON;
}

LCD_enuErrorStatus_t LCD_enuWriteString(const u8 *Add_pu8String , u8 Copy_u8Size , u8 Copy_u8PosX , u8 Copy_u8PosY)
{
    LCD_enuErrorStatus_t Local_enuErrorStatus = LCD_enuOk;

    u8 Local_u8BufferIndex = 0;

    u8 Local_u8CharBuffer = 0;

    if(Add_pu8String == NULL)
    {
        Local_enuErrorStatus = LCD_enuErrorNullPtr;
    }
    else if(Copy_u8PosX > LCD_COLUMNS_NUM)
    {
        Local_enuErrorStatus = LCD_enuErrorColumnNumber;
    }
    else if(Copy_u8PosY > LCD_ROWS_NUM)
    {
        Local_enuErrorStatus = LCD_enuErrorRowNumber;
    }
    else
    {
        for(Local_u8BufferIndex = 0 ; Local_u8BufferIndex < LCD_BUFFERSIZE ; Local_u8BufferIndex++)
        {
            if(LCD_strUserData[Local_u8BufferIndex].LCD_u8Buffered == LCD_NOTBUFFERED)
            {
                for(Local_u8CharBuffer = 0 ; Local_u8CharBuffer < Copy_u8Size ; Local_u8CharBuffer++)
                {
                    LCD_strUserData[Local_u8BufferIndex].LCD_String[Local_u8CharBuffer] = Add_pu8String[Local_u8CharBuffer];
                }

                LCD_strUserData[Local_u8BufferIndex].LCD_CurrPos = 0;
                LCD_strUserData[Local_u8BufferIndex].LCD_u8Buffered = LCD_BUFFERED;
                LCD_strUserData[Local_u8BufferIndex].LCD_u8PosX = Copy_u8PosX;
                LCD_strUserData[Local_u8BufferIndex].LCD_u8PosY = Copy_u8PosY;
                LCD_strUserData[Local_u8BufferIndex].LCD_u8Size = Copy_u8Size;


                if(LCD_enuCurrRequest == LCD_enuReqIdle)
                {
                    LCD_enuCurrRequest = LCD_enuReqWrite;
                    LCD_enuWriteState = LCD_enuWriteStart;
                }
                break;
            }
        }

        if(Local_u8BufferIndex == LCD_BUFFERSIZE)
        {
            Local_enuErrorStatus = LCD_enuErrorNoBuffer;
        }
    }

    return Local_enuErrorStatus;
}



void LCD_Task(void)
{
    if(LCD_enuInitState != LCD_enuInitDone)
    {
        LCD_voidInitProcess();
    }
    else
    {
        switch(LCD_enuCurrRequest){
            case LCD_enuReqWrite:
                LCD_voidWriteProcess();
            break;

            default:
            break;    

            
        }
    }

}


static void LCD_voidInitProcess(void)
{
    switch(LCD_enuInitState){
        case LCD_enuInitStart:
            LCD_enuInitState = LCD_enuInitFunctionSet;
            LCD_voidSetEnable(LCD_enuEnableOff);
        break;

        case LCD_enuInitFunctionSet:
            if(LCD_enuEnable == LCD_enuEnableOff)
            {
                LCD_voidSendCommand(LCD_FUNCTIONSET_COMMAND | LCD_DATA_LENGTH | LCD_NUM_LINES | LCD_FONT_TYPE , GPIO_RESET_VALUE , GPIO_RESET_VALUE);
                LCD_enuEnable = LCD_enuEnableOn;
                LCD_voidSetEnable(LCD_enuEnableOn);
            }
            else
            {
                LCD_enuEnable = LCD_enuEnableOff;
                LCD_voidSetEnable(LCD_enuEnableOff);
                LCD_enuInitState = LCD_enuInitClearDisplay;
            }

         break;

         case LCD_enuInitClearDisplay:
            if(LCD_enuEnable = LCD_enuEnableOff)
            {
                LCD_voidSendCommand(LCD_CLEARDISPLAY_COMMAND , GPIO_RESET_VALUE , GPIO_RESET_VALUE);
                LCD_enuEnable = LCD_enuEnableOn;
                LCD_voidSetEnable(LCD_enuEnableOn);
            }
            else
            {
                LCD_enuEnable = LCD_enuEnableOff;
                LCD_voidSetEnable(LCD_enuEnableOff);
                LCD_enuInitState = LCD_enuInitReturnHome;                
            }

        break;

        case LCD_enuInitReturnHome:
            if(LCD_enuEnable == LCD_enuEnableOff)
            {
                LCD_voidSendCommand(LCD_RETURNHOME_COMMAND , GPIO_RESET_VALUE , GPIO_RESET_VALUE);
                LCD_enuEnable = LCD_enuEnableOn;
                LCD_voidSetEnable(LCD_enuEnableOn);
            }
            else
            {
                LCD_enuEnable = LCD_enuEnableOff;
                LCD_voidSetEnable(LCD_enuEnableOff);
                LCD_enuInitState = LCD_enuInitDisplayOn;                
            }

        break;

        case LCD_enuInitDisplayOn:
            if(LCD_enuEnable == LCD_enuEnableOff)
            {
                LCD_voidSendCommand(LCD_DISPLAYON_COMMAND | LCD_DISPLAY | LCD_BLINK_CURSOR | LCD_CURSOR , GPIO_RESET_VALUE , GPIO_RESET_VALUE);
                LCD_enuEnable = LCD_enuEnableOn;
                LCD_voidSetEnable(LCD_enuEnableOn);
            }
            else
            {
                LCD_enuEnable = LCD_enuEnableOff;
                LCD_voidSetEnable(LCD_enuEnableOff);
                LCD_enuInitState = LCD_enuInitStartAddress;                
            }

        break;

        case LCD_enuInitStartAddress:
            if(LCD_enuEnable == LCD_enuEnableOff)
            {
                LCD_voidSendCommand(LCD_START_DD_RAM_ADDRESS_COMMAND , GPIO_RESET_VALUE , GPIO_RESET_VALUE);
                LCD_enuEnable = LCD_enuEnableOn;
                LCD_voidSetEnable(LCD_enuEnableOn);
            }
            else
            {
                LCD_enuEnable = LCD_enuEnableOff;
                LCD_voidSetEnable(LCD_enuEnableOff);
                LCD_enuInitState = LCD_enuInitDone;  

            }

        break;

        case LCD_enuInitDone:
            LCD_u8BusyFlag = LCD_BUSYFLAG_OFF;
        break;                                

    }
}


static void LCD_voidWriteProcess(void)
{
    switch(LCD_enuWriteState){

        case LCD_enuWriteStart:

            LCD_enuWriteState = LCD_enuWriteSetPosition;

        break;

        case LCD_enuWriteSetPosition:

            LCD_u8BusyFlag = LCD_BUSYFLAG_ON;

            if(LCD_enuEnable == LCD_enuEnableOff)
            {
                switch(LCD_strUserData[LCD_u8CurrentBuffer].LCD_u8PosY){

                    case LCD_LINE_ONE:

                        LCD_voidSendCommand(LCD_LINE_ONE_BASE + LCD_strUserData[LCD_u8CurrentBuffer].LCD_u8PosX , GPIO_RESET_VALUE , GPIO_RESET_VALUE);
                   
                    break;

                    case LCD_LINE_TWO:

                        LCD_voidSendCommand(LCD_LINE_TWO_BASE + LCD_strUserData[LCD_u8CurrentBuffer].LCD_u8PosX , GPIO_RESET_VALUE , GPIO_RESET_VALUE);
                   
                    break;
                            
                }

                LCD_voidSetEnable(LCD_enuEnableOn);
                LCD_enuEnable = LCD_enuEnableOn;
            }
            else
            {
                LCD_enuEnable = LCD_enuEnableOff;
                LCD_voidSetEnable(LCD_enuEnableOff);
                LCD_enuWriteState = LCD_enuWriteCharacter;
            }

        break;

        case LCD_enuWriteCharacter:

            if(LCD_strUserData[LCD_u8CurrentBuffer].LCD_CurrPos < LCD_strUserData[LCD_u8CurrentBuffer].LCD_u8Size)
            {
                if(LCD_enuEnable == LCD_enuEnableOff)
                {
                    LCD_u8CurrentPosition = LCD_strUserData[LCD_u8CurrentBuffer].LCD_CurrPos;
                    LCD_voidSendCommand(LCD_strUserData[LCD_u8CurrentBuffer].LCD_String[LCD_u8CurrentPosition] , GPIO_RESET_VALUE , GPIO_RESET_VALUE);
                    LCD_voidSetEnable(LCD_enuEnableOn);
                    LCD_enuEnable = LCD_enuEnableOn;
                }
                else
                {
                    LCD_enuEnable = LCD_enuEnableOff;
                    LCD_voidSetEnable(LCD_enuEnableOff);
                    LCD_strUserData[LCD_u8CurrentBuffer].LCD_CurrPos++;
                }
            }
            else
            {
                LCD_enuWriteState = LCD_enuWriteDone;
            }

        break;


        case LCD_enuWriteDone:
            LCD_strUserData[LCD_u8CurrentBuffer].LCD_u8Buffered = LCD_NOTBUFFERED;

            for(LCD_u8BufferIndex = 0 ; LCD_u8BufferIndex < LCD_BUFFERSIZE ; LCD_u8BufferIndex++)
            {
                if(LCD_strUserData[LCD_u8BufferIndex].LCD_u8Buffered == LCD_BUFFERED){

                break;

                }
            }

            if(LCD_u8BufferIndex == LCD_BUFFERSIZE)
            {
                LCD_enuCurrRequest = LCD_enuReqIdle;
                LCD_u8CurrentBuffer = 0;
                LCD_u8BusyFlag = LCD_BUSYFLAG_OFF;
            }
            else
            {
                LCD_enuWriteState = LCD_enuWriteStart;
                LCD_u8CurrentBuffer = LCD_u8BufferIndex;

                if(LCD_u8CurrentBuffer == LCD_BUFFERSIZE)
                {
                    LCD_u8CurrentBuffer = 0;
                }
            }

        break;                    
    }
    

}


static void LCD_voidSetEnable(u8 Copy_u8Value)
{
    gpio_SetPinValue(LCD_Pins[LCD_ENABLE_PIN].LCD_Port , LCD_Pins[LCD_ENABLE_PIN].LCD_u16Pin , Copy_u8Value);
}

static void LCD_voidSendCommand(u8 Copy_u8Command , u8 Copy_u8RWValue , u8 Copy_u8RSValue)
{
    gpio_SetPinValue(LCD_Pins[LCD_RW_PIN].LCD_Port , LCD_Pins[LCD_RW_PIN].LCD_u16Pin , Copy_u8RWValue);
    gpio_SetPinValue(LCD_Pins[LCD_RS_PIN].LCD_Port , LCD_Pins[LCD_RS_PIN].LCD_u16Pin , Copy_u8RSValue);

    gpio_SetPinValue(LCD_Pins[LCD_D0_PIN].LCD_Port , LCD_Pins[LCD_D0_PIN].LCD_u16Pin , ((Copy_u8Command >> 0) & 1));
    gpio_SetPinValue(LCD_Pins[LCD_D1_PIN].LCD_Port , LCD_Pins[LCD_D1_PIN].LCD_u16Pin , ((Copy_u8Command >> 1) & 1));
    gpio_SetPinValue(LCD_Pins[LCD_D2_PIN].LCD_Port , LCD_Pins[LCD_D2_PIN].LCD_u16Pin , ((Copy_u8Command >> 2) & 1));
    gpio_SetPinValue(LCD_Pins[LCD_D3_PIN].LCD_Port , LCD_Pins[LCD_D3_PIN].LCD_u16Pin , ((Copy_u8Command >> 3) & 1));
    gpio_SetPinValue(LCD_Pins[LCD_D4_PIN].LCD_Port , LCD_Pins[LCD_D4_PIN].LCD_u16Pin , ((Copy_u8Command >> 4) & 1));
    gpio_SetPinValue(LCD_Pins[LCD_D5_PIN].LCD_Port , LCD_Pins[LCD_D5_PIN].LCD_u16Pin , ((Copy_u8Command >> 5) & 1));
    gpio_SetPinValue(LCD_Pins[LCD_D6_PIN].LCD_Port , LCD_Pins[LCD_D6_PIN].LCD_u16Pin , ((Copy_u8Command >> 6) & 1));
    gpio_SetPinValue(LCD_Pins[LCD_D7_PIN].LCD_Port , LCD_Pins[LCD_D7_PIN].LCD_u16Pin , ((Copy_u8Command >> 7) & 1));
}