/******************************************************************/
/*DMA Driver                */
/* Target:STM32F401CC                       */
/* Yousef_Ahmed                              */
/* Date:2023-04-10                                       */
/******************************************************************/

#include "STD_TYPES.h"
#include "DMA.h"

#define dma_TRANFER_COMP_INT_FLAG_0                      5
#define dma_TRANFER_COMP_INT_FLAG_1                      11
#define dma_TRANFER_COMP_INT_FLAG_2                      21
#define dma_TRANFER_COMP_INT_FLAG_3                      27

#define dma_HALF_TRANFER_INT_FLAG_0                      4          
#define dma_HALF_TRANFER_INT_FLAG_1                      10          
#define dma_HALF_TRANFER_INT_FLAG_2                      20          
#define dma_HALF_TRANFER_INT_FLAG_3                      26

#define dma_TRANSFER_ERROR_INT_FLAG_0                    3      
#define dma_TRANSFER_ERROR_INT_FLAG_1                    9      
#define dma_TRANSFER_ERROR_INT_FLAG_2                    19      
#define dma_TRANSFER_ERROR_INT_FLAG_3                    25

#define dma_DIRECT_MODE_ERROR_INT_FLAG_0                 2     
#define dma_DIRECT_MODE_ERROR_INT_FLAG_1                 8     
#define dma_DIRECT_MODE_ERROR_INT_FLAG_2                 18     
#define dma_DIRECT_MODE_ERROR_INT_FLAG_3                 24

#define dma_FIFO_ERROR_INT_FLAG_0                        0 
#define dma_FIFO_ERROR_INT_FLAG_1                        6 
#define dma_FIFO_ERROR_INT_FLAG_2                        16 
#define dma_FIFO_ERROR_INT_FLAG_3                        22 


/*************************************typdefs**********************************************/
typedef struct{

    u32 LISR;
    u32 HISR;
    u32 LIFCR;
    u32 HIFCR;
    struct{
        u32 SxCR;
        u32 SxNDTR;
        u32 SxPAR;
        u32 SxM0AR;
        u32 SxM1AR;
        u32 SxFCR;
    }Stream_cfg_t[8];

}DMA_t;

#define DMA1_PTR             ((volatile DMA_t*const)DMA1_BASE_ADDRESS)
#define DMA2_PTR             ((volatile DMA_t*const)DMA2_BASE_ADDRESS)

/*****************************static variables******************************************/

static DMA_cbf CallBack[DMA_Num][dma_Stream_Num];


/*************************function definition******************************************/

DMA_Error_t dma_ConfigStream(DMA_Config_t* Dma_cfg)
{
    DMA_Error_t Local_enuErrorStatus = dma_Ok;

    u32 Local_u32Tmp = 0;

    u16 Local_U16TimeOut = 0;

    if(Dma_cfg == NULL || Dma_cfg->DMA_Id == NULL){

        Local_enuErrorStatus = dma_NullPointer;

    }else if(Dma_cfg->Stream > dma_Stream_Num){

        Local_enuErrorStatus = dma_WrongSreamNum;

    }else if(Dma_cfg->Stream_Channel > dma_Channel_Num){

        Local_enuErrorStatus = dma_WrongConfig;

    }else{

        if((((DMA_t*)(Dma_cfg->DMA_Id))->Stream_cfg_t[Dma_cfg->Stream].SxCR) & dma_STREAM_EN){

            Local_u32Tmp = ((DMA_t*)(Dma_cfg->DMA_Id))->Stream_cfg_t[Dma_cfg->Stream].SxCR;

            Local_u32Tmp &= ~(dma_STREAM_EN);

            ((DMA_t*)(Dma_cfg->DMA_Id))->Stream_cfg_t[Dma_cfg->Stream].SxCR = Local_u32Tmp;

            while(((((DMA_t*)(Dma_cfg->DMA_Id))->Stream_cfg_t[Dma_cfg->Stream].SxCR) & dma_STREAM_EN) && (Local_U16TimeOut < 1000)){

                Local_U16TimeOut++;

                if(Local_U16TimeOut == 1000){

                    Local_enuErrorStatus = dma_FailedToConfigure;

                }

            }
        }
            Local_u32Tmp = ((DMA_t*)(Dma_cfg->DMA_Id))->Stream_cfg_t[Dma_cfg->Stream].SxCR;

            Local_u32Tmp &= (~(dma_CIRCULAR_MODE_EN) | ~(dma_CURRENT_TARGET_EN) | dma_DATA_TRANSFER_CLEAR | ~(dma_DOUBLE_BUFF_MODE_EN) | dma_MDATA_SIZE_CLEAR | ~(dma_MINC_MODE_MSIZE) |
                                dma_MDATA_SIZE_CLEAR | dma_MBURST_CLEAR | dma_PDATA_SIZE_CLEAR | ~(dma_PERI_FLOW_CONTROL_PERI) | ~(dma_PINC_MODE_PSIZE) | dma_PBURST_CLEAR | ~(dma_PERI_INC_OFFSET_SIZE_LINKED_TO_FIXED) |
                                dma_ChANNEL_CLEAR | dma_PRIORIY_LEVEL_CLEAR) ;

            Local_u32Tmp |= (Dma_cfg->Circ_Mode | Dma_cfg->Current_Target | Dma_cfg->Data_Tranfer_Direction | Dma_cfg->Double_Buffer_Mode |
                             Dma_cfg->Mdata_Size | Dma_cfg->Mem_Inc_Mode | Dma_cfg->Memory_Burst | Dma_cfg->Pdata_Size | Dma_cfg->Peri_Flow_Control | Dma_cfg->Peri_Inc_Mode | Dma_cfg->Peripheral_Burst |
                             Dma_cfg->Peripheral_Inc_Size | Dma_cfg->Stream_Channel | Dma_cfg->Stream_Priority | Dma_cfg->Interrupt.Half_Transfer_Comp_Int | Dma_cfg->Interrupt.Transfer_Comp_Int |
                             Dma_cfg->Interrupt.Transfer_Error_Int | Dma_cfg->Interrupt.Direct_Mode_Error_Int);
            
            
            ((DMA_t*)(Dma_cfg->DMA_Id))->Stream_cfg_t[Dma_cfg->Stream].SxCR = Local_u32Tmp;

            Local_u32Tmp = ((DMA_t*)(Dma_cfg->DMA_Id))->Stream_cfg_t[Dma_cfg->Stream].SxFCR;

            Local_u32Tmp |= (Dma_cfg->FIFO_Threshold |Dma_cfg->Direct_Mode | Dma_cfg->Interrupt.FIFO_Error_Int);

            ((DMA_t*)(Dma_cfg->DMA_Id))->Stream_cfg_t[Dma_cfg->Stream].SxFCR = Local_u32Tmp;


        }


    

    return Local_enuErrorStatus;


}

DMA_Error_t dma_ConfigChannel(Channel_Config_t* Stream_cfg )
{
    DMA_Error_t Local_enuErrorStatus = dma_Ok;

    if(Stream_cfg == NULL){

        Local_enuErrorStatus = dma_NullPointer;

    }else if(Stream_cfg->DMA_Stream > dma_Stream_Num){

        Local_enuErrorStatus = dma_WrongSreamNum;

    }else{

        ((DMA_t*)(Stream_cfg->DMA_Id))->Stream_cfg_t[Stream_cfg->DMA_Stream].SxPAR = Stream_cfg->Periphral_Address;

        ((DMA_t*)(Stream_cfg->DMA_Id))->Stream_cfg_t[Stream_cfg->DMA_Stream].SxM0AR = Stream_cfg->Memory_0_Address;

        ((DMA_t*)(Stream_cfg->DMA_Id))->Stream_cfg_t[Stream_cfg->DMA_Stream].SxM1AR = Stream_cfg->Memory_1_Address;

        ((DMA_t*)(Stream_cfg->DMA_Id))->Stream_cfg_t[Stream_cfg->DMA_Stream].SxNDTR = Stream_cfg->Block_Length;


    }

    return Local_enuErrorStatus;

}

DMA_Error_t dma_RegisterCallbackFunction(Dma_Id_t Dma , DMA_Stream_t Stream ,DMA_cbf DMA_CallBackFunction)
{
    DMA_Error_t Local_enuErrorStatus = dma_Ok;

    if(DMA_CallBackFunction == NULL){

        Local_enuErrorStatus = dma_NullPointer;

    }else{

        CallBack[Dma][Stream] = DMA_CallBackFunction;


    }

    return Local_enuErrorStatus;
}

DMA_Error_t dma_Set_State(void* Dma , DMA_Stream_t Stream , DMA_State_t State)
{
    DMA_Error_t Local_enuErrorStatus = dma_Ok;

    u32 Local_u32Tmp = 0;

    if(Dma == NULL){

        Local_enuErrorStatus = dma_NullPointer;

    }else if(Stream > dma_Stream_Num){

        Local_enuErrorStatus = dma_WrongSreamNum;

    }else if(State != dma_Disable && State != dma_Enable){

        Local_enuErrorStatus = dma_WrongConfig;

    }else{

        if(State){

            Local_u32Tmp = ((DMA_t*)Dma)->Stream_cfg_t[Stream].SxCR;

            Local_u32Tmp |= dma_STREAM_EN ; 

            ((DMA_t*)Dma)->Stream_cfg_t[Stream].SxCR = Local_u32Tmp;

        }else{
            Local_u32Tmp = ((DMA_t*)Dma)->Stream_cfg_t[Stream].SxCR;

            Local_u32Tmp &= ~(dma_STREAM_EN) ; 

            ((DMA_t*)Dma)->Stream_cfg_t[Stream].SxCR = Local_u32Tmp;


        }


    }
}



void DMA1_Stream0_IRQHandler(void)
{
    if((DMA1_PTR->LISR) & (1 << dma_TRANFER_COMP_INT_FLAG_0)){

        if(CallBack[DMA1_Id][dma_Stream0]){

            DMA1_PTR->LIFCR |= (1<< dma_TRANFER_COMP_INT_FLAG_0);

            CallBack[DMA1_Id][dma_Stream0]();

        }

    }

    if((DMA1_PTR->LISR) & (1 << dma_HALF_TRANFER_INT_FLAG_0)){

        if(CallBack[DMA1_Id][dma_Stream0]){

            DMA1_PTR->LIFCR |= (1<< dma_HALF_TRANFER_INT_FLAG_0);

            CallBack[DMA1_Id][dma_Stream0]();

        }

    }    
    
}

void DMA1_Stream1_IRQHandler(void)
{

    if((DMA1_PTR->LISR) & (1 << dma_TRANFER_COMP_INT_FLAG_1)){

        if(CallBack[DMA1_Id][dma_Stream1]){

            DMA1_PTR->LIFCR |= (1<< dma_TRANFER_COMP_INT_FLAG_1);

            CallBack[DMA1_Id][dma_Stream1]();

        }

    }

    if((DMA1_PTR->LISR) & (1 << dma_HALF_TRANFER_INT_FLAG_1)){

        if(CallBack[DMA1_Id][dma_Stream1]){

            DMA1_PTR->LIFCR |= (1<< dma_HALF_TRANFER_INT_FLAG_1);

            CallBack[DMA1_Id][dma_Stream1]();

        }

    } 
    
}

void DMA1_Stream2_IRQHandler(void)
{

    if((DMA1_PTR->LISR) & (1 << dma_TRANFER_COMP_INT_FLAG_2)){

        if(CallBack[DMA1_Id][dma_Stream2]){

            DMA1_PTR->LIFCR |= (1<< dma_TRANFER_COMP_INT_FLAG_2);

            CallBack[DMA1_Id][dma_Stream2]();

        }

    }

    if((DMA1_PTR->LISR) & (1 << dma_HALF_TRANFER_INT_FLAG_2)){

        if(CallBack[DMA1_Id][dma_Stream2]){

            DMA1_PTR->LIFCR |= (1<< dma_HALF_TRANFER_INT_FLAG_2);

            CallBack[DMA1_Id][dma_Stream2]();

        }

    }     
    
}

void DMA1_Stream3_IRQHandler(void)
{

    if((DMA1_PTR->LISR) & (1 << dma_TRANFER_COMP_INT_FLAG_3)){

        if(CallBack[DMA1_Id][dma_Stream3]){

            DMA1_PTR->LIFCR |= (1<< dma_TRANFER_COMP_INT_FLAG_3);

            CallBack[DMA1_Id][dma_Stream3]();

        }

    }

    if((DMA1_PTR->LISR) & (1 << dma_HALF_TRANFER_INT_FLAG_3)){

        if(CallBack[DMA1_Id][dma_Stream3]){

            DMA1_PTR->LIFCR |= (1<< dma_HALF_TRANFER_INT_FLAG_3);

            CallBack[DMA1_Id][dma_Stream3]();

        }

    }     
    
}

void DMA1_Stream4_IRQHandler(void)
{

    if((DMA1_PTR->HISR) & (1 << dma_TRANFER_COMP_INT_FLAG_0)){

        if(CallBack[DMA1_Id][dma_Stream4]){

            DMA1_PTR->HIFCR |= (1<< dma_TRANFER_COMP_INT_FLAG_0);

            CallBack[DMA1_Id][dma_Stream4]();

        }

    }

    if((DMA1_PTR->HISR) & (1 << dma_HALF_TRANFER_INT_FLAG_0)){

        if(CallBack[DMA1_Id][dma_Stream4]){

            DMA1_PTR->HIFCR |= (1<< dma_HALF_TRANFER_INT_FLAG_0);

            CallBack[DMA1_Id][dma_Stream4]();

        }

    }     
    
}

void DMA1_Stream5_IRQHandler(void)
{

    if((DMA1_PTR->HISR) & (1 << dma_TRANFER_COMP_INT_FLAG_1)){

        if(CallBack[DMA1_Id][dma_Stream5]){

            DMA1_PTR->HIFCR |= (1<< dma_TRANFER_COMP_INT_FLAG_1);

            CallBack[DMA1_Id][dma_Stream5]();

        }

    }

    if((DMA1_PTR->HISR) & (1 << dma_HALF_TRANFER_INT_FLAG_1)){

        if(CallBack[DMA1_Id][dma_Stream5]){

            DMA1_PTR->HIFCR |= (1<< dma_HALF_TRANFER_INT_FLAG_1);

            CallBack[DMA1_Id][dma_Stream5]();

        }

    }     
    
}

void DMA1_Stream6_IRQHandler(void)
{

    if((DMA1_PTR->HISR) & (1 << dma_TRANFER_COMP_INT_FLAG_2)){

        if(CallBack[DMA1_Id][dma_Stream6]){

            DMA1_PTR->HIFCR |= (1<< dma_TRANFER_COMP_INT_FLAG_2);

            CallBack[DMA1_Id][dma_Stream6]();

        }

    }

    if((DMA1_PTR->HISR) & (1 << dma_HALF_TRANFER_INT_FLAG_2)){

        if(CallBack[DMA1_Id][dma_Stream6]){

            DMA1_PTR->HIFCR |= (1<< dma_HALF_TRANFER_INT_FLAG_2);

            CallBack[DMA1_Id][dma_Stream6]();

        }

    }     
    
}

void DMA1_Stream7_IRQHandler(void)
{

    if((DMA1_PTR->HISR) & (1 << dma_TRANFER_COMP_INT_FLAG_3)){

        if(CallBack[DMA1_Id][dma_Stream7]){

            DMA1_PTR->HIFCR |= (1<< dma_TRANFER_COMP_INT_FLAG_3);

            CallBack[DMA1_Id][dma_Stream7]();

        }

    }

    if((DMA1_PTR->HISR) & (1 << dma_HALF_TRANFER_INT_FLAG_3)){

        if(CallBack[DMA1_Id][dma_Stream7]){

            DMA1_PTR->HIFCR |= (1<< dma_HALF_TRANFER_INT_FLAG_3);

            CallBack[DMA1_Id][dma_Stream7]();

        }

    } 
    
}
/************************************************************************************************/
void DMA2_Stream0_IRQHandler(void)
{

}

void DMA2_Stream1_IRQHandler(void)
{
    
}

void DMA2_Stream2_IRQHandler(void)
{
    
}

void DMA2_Stream3_IRQHandler(void)
{
    
}

void DMA2_Stream4_IRQHandler(void)
{
    
}

void DMA2_Stream5_IRQHandler(void)
{
    
}

void DMA2_Stream6_IRQHandler(void)
{
    
}

void DMA2_Stream7_IRQHandler(void)
{
    
}
