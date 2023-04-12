/*******************************************************************/
/*         DMA Driver        */
/* Target:STM32F401CC                       */
/*Author :Yousef_Ahmed                         */
/*Date   :2023-04-10                                      */
/*******************************************************************/

#ifndef _DMA_H
#define _DMA_H

#define DMA1_BASE_ADDRESS                              0x40026000
#define DMA2_BASE_ADDRESS                              0x40026400
               
#define DMA1                                           (void*)DMA1_BASE_ADDRESS
#define DMA2                                           (void*)DMA2_BASE_ADDRESS
               
               
#define dma_ChANNEL_0                                  0x00000000            
#define dma_ChANNEL_1                                  0x02000000
#define dma_ChANNEL_2                                  0x04000000
#define dma_ChANNEL_3                                  0x06000000
#define dma_ChANNEL_4                                  0x08000000
#define dma_ChANNEL_5                                  0x0A000000
#define dma_ChANNEL_6                                  0x0C000000
#define dma_ChANNEL_7                                  0x0E000000
               
#define dma_MBURST_SINGLE                              0x00000000
#define dma_MBURST_INC4                                0x00800000
#define dma_MBURST_INC8                                0x01000000
#define dma_MBURST_INC16                               0x01800000
               
               
#define dma_PBURST_SINGLE                              0x00000000
#define dma_PBURST_INC4                                0x00200000
#define dma_PBURST_INC8                                0x00400000
#define dma_PBURST_INC16                               0x00600000
               
#define dma_CURRENT_TARGET_EN                          0x00080000      // only in double buffer mode
               
#define dma_DOUBLE_BUFF_MODE_EN                        0x00040000
               
#define dma_PRIORIY_LEVEL_LOW                          0x00000000
#define dma_PRIORIY_LEVEL_MED                          0x00010000
#define dma_PRIORIY_LEVEL_HIGH                         0x00020000
#define dma_PRIORIY_LEVEL_VERY_HIGH                    0x00030000

#define dma_PERI_INC_OFFSET_SIZE_LINKED_TO_PSIZE       0x00000000
#define dma_PERI_INC_OFFSET_SIZE_LINKED_TO_FIXED       0x00008000 // 32 bit alignment


#define dma_MDATA_SIZE_BYTE                            0x00000000
#define dma_MDATA_SIZE_HALF_WORD                       0x00002000
#define dma_MDATA_SIZE_WORD                            0x00004000

#define dma_PDATA_SIZE_BYTE                            0x00000000
#define dma_PDATA_SIZE_HALF_WORD                       0x00000800
#define dma_PDATA_SIZE_WORD                            0x00001000

#define dma_MINC_MODE_FIXED                            0x00000000
#define dma_MINC_MODE_MSIZE                            0x00000400

#define dma_PINC_MODE_FIXED                            0x00000000
#define dma_PINC_MODE_PSIZE                            0x00000200

#define dma_CIRCULAR_MODE_EN                           0x00000100

#define dma_DATA_TRANSFER_PERI_MEM                     0x00000000
#define dma_DATA_TRANSFER_MEM_PERI                     0x00000040
#define dma_DATA_TRANSFER_MEM_MEM                      0x00000080

#define dma_PERI_FLOW_CONTROL_DMA                      0x00000000
#define dma_PERI_FLOW_CONTROL_PERI                     0x00000020

#define dma_TRANSFER_COMP_INT_EN                       0x00000010
#define dma_HALF_TRANSFER_COMP_INT_EN                  0x00000008
#define dma_TRANSFER_ERROR_INT_EN                      0x00000004
#define dma_DIRECT_MODE_ERROR_INT_EN                   0x00000002


#define dma_STREAM_EN                                  0x00000001

#define dma_FIFO_ERROR_INT_EN                          0x00000080
#define dma_DIRECT_MODE_DISABLE                        0x00000004
#define dma_DIRECT_MODE_EN                             0x00000000

#define dma_FIFO_THRESH_SELECT_QUARTER_FULL            0x00000000
#define dma_FIFO_THRESH_SELECT_HALF_FULL               0x00000001
#define dma_FIFO_THRESH_SELECT_THREE_QUARTERS_FULL     0x00000002
#define dma_FIFO_THRESH_SELECT_FULL                    0x00000003

typedef enum{

    dma_Ok,
    dma_Error,
    dma_NullPointer,
    dma_WrongConfig,
    dma_WrongSreamNum

}DMA_Error_t;

typedef enum{

    dma_Stream0, // DMA1 : SPI3_Rx - I2C1_Rx - TIM4_Ch1 - I2S3_EXT_Rx - TIM5_CH3 - TIM5_Up
                 // DMA2 : ADC1 - SPI1_Rx - SPI4_Rx - TIM1_Trig   
    
    dma_Stream1,// DMA1 : I2C3_Rx - TIM2_Up - TIM2_Ch3 - TIM5_Ch4 - TIM5_Trig
                // DMA2 : SPI4_Tx - USART6_Tx - TIM1_Ch1

    dma_Stream2,// DMA1 : SPI3_Rx - I2S3_EXT_Rx - I2C3_Rx - TIM_Ch43 - TIM3_Up - TIM5_Ch4 - I2C2_Rx
                // DMA2 : SPI1_RX - USART1_RX - USART6_RX - TIM1_CH2

    dma_Stream3,// DMA1 : TIM5_CH4 - TIM5_TRIG - I2C2_RX - SPI2_RX - TIM4_CH2 - I2S2_EXT_RX
                // DMA2 : SPI1_TX - SDIO - SPI4_RX - TIM1_CH1

    dma_Stream4,// DMA1 : SPI2_TX - I2S2_EXT_TX - I2C3_TX - TIM3_CH1 - TIM3_TRIG - TIM5_CH2
                // DMA2 : ADC1 - SPI4_TX - TIM1_CH4 - TIM1_TRIG - TIM1_TRIG

    dma_Stream5,// DMA1 : SPI3_TX - 2C1_RX - I2S3_EXT_TX - TIM2_CH1 - USART2_RX - TIM3_CH2 - I2C3_TX
                // DMA2 : SPI1_TX - USART1_RX - TIM1_UP 

    dma_Stream6,// DMA1 : I2C1_TX - TIM4_UP - TIM2_CH2 - TIM2_CH4 - USART2_TX - TIM5_UP
                // DNA2 : TIM1_CH1 - TIM1_CH2 - TIM1_CH3 - SDIO - USART6_TX - TIM1_CH3

    dma_Stream7,// DMA1 : SPI3_TX - I2C1_TX - TIM4_CH3 - TIM2_UP - TIM2_CH4 - TIM3_CH3 - I2C2_TX
                // DMA2 : USART1_TX - USART6_TX
    dma_Stream_Num

}DMA_Stream_t;

typedef enum{
                  //DMA1                                                                                                                       //DMA2                                     
                  //*Stream0******Stream1******Stream2******Stream3*******Stream4*******Stream5*******Stream6*******Stream7******              //*Stream0******Stream1******Stream2******Stream3*******Stream4*******Stream5*******Stream6*******Stream7******                                         
                  //*************************************************************************************************************              //*************************************************************************************************************      
    dma_Channel0, //*SPI3_RX    *           * SPI3_RX    * SPI2_RX     * SPI2_TX     * SPI3_TX     *             * SPI3_TX     * Channel0      //ADC1      *              *             *             * ADC1       *             *  TIM1_CH1    *            *  
    dma_Channel1, //*I2C1_RX    * I2C3_RX   *            *             *             * I2C1_RX     * I2C1_TX     * I2C1_TX     *               //          *              *             *             *            *             *  TIM1_CH2    *            *       
    dma_Channel2, //*TIM4_CH1   *           *I2S3_EXT_RX * TIM4_CH2    *I2S2_EXT_TX  * I2S3_EXT_TX * TIM4_UP     * TIM4_CH3    *               //          *              *             *             *            *             *  TIM1_CH3    *            *  
    dma_Channel3, //*I2S3_EXT_RX* TIM2_UP   * I2C3_RX    * I2S2_EXT_RX * I2C3_TX     * TIM2_CH1    * TIM2_CH2    * TIM2_UP     * Channel1      //          *              *             *             *            *             *              *            *   
                  //            * TIM2_CH3  *            *             *             *             * TIM2_CH4    * TIM2_CH4    * Channel2      //          *              *             *             *            *             *              *            *                            
    dma_Channel5, //*           *           *TIM3_CH4    *             *TIM3_CH1     * TIM3_CH2    *             * TIM3_CH3    * Channel3      // SPI1_RX  *              * SPI1_RX     *  SPI1_TX    *            *  SPI1_TX    *              *            *        
                  //            *           *TIM3_UP     *             *TIM3_TRIG    *             *             *             * Channel4      // SPI4_RX  * SPI4_TX      * USART1_RX   *  SDIO       *            *  USART1_RX  * SDIO         * USART1_TX  *      
    dma_Channel6, //*TIM5_CH3   * TIM5_CH4  * TIM5_CH1   * TIM5_CH4    * TIM5_CH2    * I2C3_TX     * TIM5_UP     *             * Channel5      //          * USART6_RX    * USART6_RX   * SPI4_RX     * SPI4_TX    *             * USART6_TX    * USART6_TX  * 
                  //*TIM5_UP    * TIM5_TRIG *            * TIM5_TRIG   *             *             *             *             * Channel6      //TIM1_TRIG * TIM1_CH1     * TIM1_CH2    * TIM1_CH1    * TIM1_CH4   *  TIM1_UP    * TIM1_CH3     *            *   
                                                                                                                                               //          *              *             *             *            *   TIM1_TRIG *              *            * 
                                                                                                                                               //          *              *             *             *            *   TIM1_COM  *              *            * 
    dma_Channel7, //*           *           * I2C2_RX    * I2C2_RX     *             *             *             * I2C2_TX     * Channel7      //          *              *             *             *            *             *              *            *    
    dma_Channel_Num

}DMA_Channel_ID_t;


typedef struct{

    DMA_Stream_t Stream;
    void* DMA_Id;
    u32 Stream_Channel;
    u32 Memory_Burst;
    u32 Peripheral_Burst;
    u32 Current_Target;
    u32 Double_Buffer_Mode;
    u32 Stream_Priority;
    u32 Peripheral_Inc_Size;
    u32 Mdata_Size;
    u32 Pdata_Size;
    u32 Mem_Inc_Mode;
    u32 Peri_Inc_Mode;
    u32 Circ_Mode;
    u32 Data_Tranfer_Direction;
    u32 Peri_Flow_Control;
    u32 Stram_Enable;
    u32 Direct_Mode;
    u32 FIFO_Threshold;

    struct{

        u32 Transfer_Comp_Int;
        u32 Half_Transfer_Comp_Int;
        u32 Transfer_Error_Int;
        u32 Direct_Mode_Error_Int;
        u32 FIFO_Error_Int;

    }Interrupt;
}DMA_Config_t;

typedef struct{

    DMA_Stream_t DMA_Stream;
    void* DMA_Id;
    u32 Periphral_Address;
    u32 Memory_0_Address;
    u32 Memory_1_Address;
    u16 Block_Length;

}Channel_Config_t;


typedef void (*DMA_cbf)(void);

/*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  : void                                                                                                        */
/* Return :  void                                                                                                        */
/*************************************************************************************************************************/
extern void dma_ConfigStream(DMA_Config_t* Dma_cfg);
/*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  : void                                                                                                        */
/* Return :  void                                                                                                        */
/*************************************************************************************************************************/
extern DMA_Error_t dma_ConfigChannel(Channel_Config_t* Channel_cfg );
/*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  : void                                                                                                        */
/* Return :  void                                                                                                        */
/*************************************************************************************************************************/
extern DMA_Error_t dma_RegisterCallbackFunction(DMA_cbf DMA_CallBackFunction);


#endif /*DMA_H*/
