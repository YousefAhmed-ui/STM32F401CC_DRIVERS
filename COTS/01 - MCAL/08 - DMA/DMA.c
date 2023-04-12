/******************************************************************/
/*DMA Driver                */
/* Target:STM32F401CC                       */
/* Yousef_Ahmed                              */
/* Date:2023-04-10                                       */
/******************************************************************/

#include "STD_TYPES.h"
#include "DMA.h"

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