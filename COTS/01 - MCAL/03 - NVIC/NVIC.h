/*******************************************************************/
/*         NVIC Driver        */
/* Target:STM32F401CC                       */
/*Author :Yousef_Ahmed                         */
/*Date   :2023-03-02                                      */
/*******************************************************************/

#ifndef _NVIC_H
#define _NVIC_H


#define PRIORITY_GROUP_4_Sub_0             0x05FA0300  // 4 bit group priority(aka preimption) 0 sub priority (aka All nesting)
#define PRIORITY_GROUP_3_SUB_1             0x05FA0400  // 3 bit group priority(aka preimption) 1 sub priority
#define PRIORITY_GROUP_2_SUB_2             0x05FA0500  // 2 bit group priority(aka preimption) 2 sub priority
#define PRIORITY_GROUP_1_SUB_3             0x05FA0600  // 1 bit group priority(aka preimption) 3 sub priority
#define PRIORITY_GROUP_0_SUB_4             0x05FA0700  // 0 bit group priority(aka preimption) 4 sub priority (aka no nesting)

#define PRIORITY_IRQ_0                     0b00000000       
#define PRIORITY_IRQ_1                     0b00010000
#define PRIORITY_IRQ_2                     0b00100000
#define PRIORITY_IRQ_3                     0b00110000
#define PRIORITY_IRQ_4                     0b01000000
#define PRIORITY_IRQ_5                     0b01010000
#define PRIORITY_IRQ_6                     0b01100000
#define PRIORITY_IRQ_7                     0b01110000
#define PRIORITY_IRQ_8                     0b10000000
#define PRIORITY_IRQ_9                     0b10010000
#define PRIORITY_IRQ_10                    0b10100000
#define PRIORITY_IRQ_11                    0b10110000
#define PRIORITY_IRQ_12                    0b11000000
#define PRIORITY_IRQ_13                    0b11010000
#define PRIORITY_IRQ_14                    0b11100000
#define PRIORITY_IRQ_15                    0b11110000


typedef enum{
   nvic_IRQ_0,    //WWDG
   nvic_IRQ_1,    //EXTI16/PVD
   nvic_IRQ_2,    //EXTI21/TAMP_STAMP
   nvic_IRQ_3,    //EXTI22/RTC_WKUP
   nvic_IRQ_4,    //FLASH
   nvic_IRQ_5,    //RCC  
   nvic_IRQ_6,    //EXTI0
   nvic_IRQ_7,    //EXTI1
   nvic_IRQ_8,    //EXTI2
   nvic_IRQ_9,    //EXTI3
   nvic_IRQ_10,   //EXTI4
   nvic_IRQ_11,   //DMA1_Stream0
   nvic_IRQ_12,   //DMA1_Stream1
   nvic_IRQ_13,   //DMA1_Stream2
   nvic_IRQ_14,   //DMA1_Stream3
   nvic_IRQ_15,   //DMA1_Stream4
   nvic_IRQ_16,   //DMA1_Stream5
   nvic_IRQ_17,   //DMA1_Stream6
   nvic_IRQ_18,   //ADC
   nvic_IRQ_19,   //
   nvic_IRQ_20,   //
   nvic_IRQ_21,   //
   nvic_IRQ_22,   //
   nvic_IRQ_23,   //EXTI9_5
   nvic_IRQ_24,   //TIM1_BRK_TIM9
   nvic_IRQ_25,   //TIM1_UP_TIM10
   nvic_IRQ_26,   //TIM1_TRG_COM_TIM11
   nvic_IRQ_27,   //TIM1_CC
   nvic_IRQ_28,   //TIM2
   nvic_IRQ_29,   //TIM3
   nvic_IRQ_30,   //TIM4
   nvic_IRQ_31,   //I2C1_EV
   nvic_IRQ_32,   //I2C1_ER
   nvic_IRQ_33,   //I2C2_EV
   nvic_IRQ_34,   //I2C2_ER
   nvic_IRQ_35,   //SPI1
   nvic_IRQ_36,   //SPI2
   nvic_IRQ_37,   //USART1
   nvic_IRQ_38,   //USART2      
   nvic_IRQ_39,   //
   nvic_IRQ_40,   //EXTI15_10
   nvic_IRQ_41,   //EXTI17 / RTC_Alarm
   nvic_IRQ_42,   //EXTI18 /OTG_FS_WKUP
   nvic_IRQ_43,   //
   nvic_IRQ_44,   //
   nvic_IRQ_45,   //
   nvic_IRQ_46,   //
   nvic_IRQ_47,   //DMA1_Stream7
   nvic_IRQ_48,   //
   nvic_IRQ_49,   //SDIO
   nvic_IRQ_50,   //TIM5
   nvic_IRQ_51,   //SPI3
   nvic_IRQ_52,   //
   nvic_IRQ_53,   //
   nvic_IRQ_54,   //
   nvic_IRQ_55,   //
   nvic_IRQ_56,   //DMA2_Stream0
   nvic_IRQ_57,   //DMA2_Stream1
   nvic_IRQ_58,   //DMA2_Stream2
   nvic_IRQ_59,   //DMA2_Stream3
   nvic_IRQ_60,   //DMA2_Stream4
   nvic_IRQ_61,   //
   nvic_IRQ_62,   //
   nvic_IRQ_63,   //
   nvic_IRQ_64,   //
   nvic_IRQ_65,   //
   nvic_IRQ_66,   //
   nvic_IRQ_67,   //OTG_FS
   nvic_IRQ_68,   //DMA2_Stream5
   nvic_IRQ_69,   //DMA2_Stream6
   nvic_IRQ_70,   //DMA2_Stream7
   nvic_IRQ_71,   //USART6
   nvic_IRQ_72,   //I2C3_EV
   nvic_IRQ_73,   //I2C3_ER
   nvic_IRQ_74,   //
   nvic_IRQ_75,   //
   nvic_IRQ_76,   //
   nvic_IRQ_77,   //
   nvic_IRQ_78,   //
   nvic_IRQ_79,   //
   nvic_IRQ_80,   //
   nvic_IRQ_81,   //FPU
   nvic_IRQ_82,   //
   nvic_IRQ_83,   //
   nvic_IRQ_84,   //SPI4
   nvic_IRQ_85,
   nvic_IRQ_86,
   nvic_IRQ_87,
   nvic_IRQ_88,
   nvic_IRQ_89,
   nvic_IRQ_90,
   nvic_IRQ_91,
   nvic_IRQ_92,
   nvic_IRQ_93,
   nvic_IRQ_94,
   nvic_IRQ_95,
   nvic_IRQ_96,
   nvic_IRQ_97,
   nvic_IRQ_98,
   nvic_IRQ_99,
   nvic_IRQ_100,
   nvic_IRQ_101,
   nvic_IRQ_102,
   nvic_IRQ_103,
   nvic_IRQ_104,
   nvic_IRQ_105,
   nvic_IRQ_106,
   nvic_IRQ_107,
   nvic_IRQ_108,
   nvic_IRQ_109,
   nvic_IRQ_110,
   nvic_IRQ_111,
   nvic_IRQ_112,
   nvic_IRQ_113,
   nvic_IRQ_114,
   nvic_IRQ_115,
   nvic_IRQ_116,
   nvic_IRQ_117,
   nvic_IRQ_118,
   nvic_IRQ_119,
   nvic_IRQ_120,
   nvic_IRQ_121,
   nvic_IRQ_122,
   nvic_IRQ_123,
   nvic_IRQ_124,
   nvic_IRQ_125,
   nvic_IRQ_126,
   nvic_IRQ_127,
   nvic_IRQ_128,
   nvic_IRQ_129,
   nvic_IRQ_130,
   nvic_IRQ_131,
   nvic_IRQ_132,
   nvic_IRQ_133,
   nvic_IRQ_134,
   nvic_IRQ_135,
   nvic_IRQ_136,
   nvic_IRQ_137,
   nvic_IRQ_138,
   nvic_IRQ_139,
   nvic_IRQ_140,
   nvic_IRQ_141,
   nvic_IRQ_142,
   nvic_IRQ_143,
   nvic_IRQ_144,
   nvic_IRQ_145,
   nvic_IRQ_146,
   nvic_IRQ_147,
   nvic_IRQ_148,
   nvic_IRQ_149,
   nvic_IRQ_150,
   nvic_IRQ_151,
   nvic_IRQ_152,
   nvic_IRQ_153,
   nvic_IRQ_154,
   nvic_IRQ_155,
   nvic_IRQ_156,
   nvic_IRQ_157,
   nvic_IRQ_158,
   nvic_IRQ_159,
   nvic_IRQ_160,
   nvic_IRQ_161,
   nvic_IRQ_162,
   nvic_IRQ_163,
   nvic_IRQ_164,
   nvic_IRQ_165,
   nvic_IRQ_166,
   nvic_IRQ_167,
   nvic_IRQ_168,
   nvic_IRQ_169,
   nvic_IRQ_170,
   nvic_IRQ_171,
   nvic_IRQ_172,
   nvic_IRQ_173,
   nvic_IRQ_174,
   nvic_IRQ_175,
   nvic_IRQ_176,
   nvic_IRQ_177,
   nvic_IRQ_178,
   nvic_IRQ_179,
   nvic_IRQ_180,
   nvic_IRQ_181,
   nvic_IRQ_182,
   nvic_IRQ_183,
   nvic_IRQ_184,
   nvic_IRQ_185,
   nvic_IRQ_186,
   nvic_IRQ_187,
   nvic_IRQ_188,
   nvic_IRQ_189,
   nvic_IRQ_190,
   nvic_IRQ_191,
   nvic_IRQ_192,
   nvic_IRQ_193,
   nvic_IRQ_194,
   nvic_IRQ_195,
   nvic_IRQ_196,
   nvic_IRQ_197,
   nvic_IRQ_198,
   nvic_IRQ_199,
   nvic_IRQ_200,
   nvic_IRQ_201,
   nvic_IRQ_202,
   nvic_IRQ_203,
   nvic_IRQ_204,
   nvic_IRQ_205,
   nvic_IRQ_206,
   nvic_IRQ_207,
   nvic_IRQ_208,
   nvic_IRQ_209,
   nvic_IRQ_210,
   nvic_IRQ_211,
   nvic_IRQ_212,
   nvic_IRQ_213,
   nvic_IRQ_214,
   nvic_IRQ_215,
   nvic_IRQ_216,
   nvic_IRQ_217,
   nvic_IRQ_218,
   nvic_IRQ_219,
   nvic_IRQ_220,
   nvic_IRQ_221,
   nvic_IRQ_222,
   nvic_IRQ_223,
   nvic_IRQ_224,
   nvic_IRQ_225,
   nvic_IRQ_226,
   nvic_IRQ_227,
   nvic_IRQ_228,
   nvic_IRQ_229,
   nvic_IRQ_230,
   nvic_IRQ_231,
   nvic_IRQ_232,
   nvic_IRQ_233,
   nvic_IRQ_234,
   nvic_IRQ_235,
   nvic_IRQ_236,
   nvic_IRQ_237,
   nvic_IRQ_238,
   nvic_IRQ_239,
   nvic_IRQ_num

}NVIC_IRQenu_t;

typedef enum{
    nvic_OK,
    nvic_NotOk
}NVIC_enuError_t;

/*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  :                                                                                                             */
/* Return :                                                                                                              */
/*************************************************************************************************************************/ 
NVIC_enuError_t nvic_EnableIRQ(NVIC_IRQenu_t IRQn);
/*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  :                                                                                                             */
/* Return :                                                                                                              */
/*************************************************************************************************************************/
NVIC_enuError_t nvic_DisableIRQ(NVIC_IRQenu_t IRQn);

/*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  :                                                                                                             */
/* Return :                                                                                                              */
/*************************************************************************************************************************/ 
NVIC_enuError_t nvic_SetPendingIRQ(NVIC_IRQenu_t IRQn);
/*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  :                                                                                                             */
/* Return :                                                                                                              */
/*************************************************************************************************************************/
NVIC_enuError_t nvic_ClearPendingIRQ(NVIC_IRQenu_t IRQn);
/*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  :                                                                                                             */
/* Return :                                                                                                              */
/*************************************************************************************************************************/
NVIC_enuError_t nvic_GetActive(NVIC_IRQenu_t IRQn , u8 * Addp_ActiveIrq); 
/*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  :                                                                                                             */
/* Return :                                                                                                              */
/*************************************************************************************************************************/
NVIC_enuError_t nvic_SetPriority(NVIC_IRQenu_t IRQn, u8 priority); 

 /*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  :                                                                                                             */
/* Return :                                                                                                              */
/*************************************************************************************************************************/ 
NVIC_enuError_t nvic_SetPriorityGrouping(u32 priority_grouping);
 /*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  :                                                                                                             */
/* Return :                                                                                                              */
/*************************************************************************************************************************/
void __Enable_Irq();
 /*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  :                                                                                                             */
/* Return :                                                                                                              */
/*************************************************************************************************************************/
void __Disable_Irq();
 /*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  :                                                                                                             */
/* Return :                                                                                                              */
/*************************************************************************************************************************/
void __Enable_fault_irq(void);
 /*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  :                                                                                                             */
/* Return :                                                                                                              */
/*************************************************************************************************************************/
void __Disable_fault_irq(void);
 /*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  :                                                                                                             */
/* Return :                                                                                                              */
/*************************************************************************************************************************/
void __Set_BasePri(u8 Copy_u8Priority);


#endif /*NVIC_H*/
