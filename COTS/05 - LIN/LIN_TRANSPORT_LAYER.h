#ifndef LIN_TRANSPORT_LAYER_H
#define LIN_TRANSPORT_LAYER_H

#include "LIN_TYPES.h"
#include "LIN_NETWORK_LAYER.h"

//#ifdef LIN_TRANSPORT_LAYER

typedef l_u8 lin_NAD_t;
typedef l_u8 lin_SID_t;

typedef enum{

    LIN_SID_ASSIGN_NAD = 0xB0,
    LIN_SID_READY_BY_ID = 0xB2,
    LIN_SID_CONDITIONAL_CHANGE_NAD = 0xB4,
    LIN_SID_DUMP_DATA = 0xB4,
    LIN_SID_SAVED_CONFIG = 0xB6,
    LIN_SID_ASSIGN_FRAME_ID_RANGE = 0xB7

}LIN_enuSID_t;

typedef enum {
	LIN_PCI_SF = 0,
	LIN_PCI_FF = 1,
	LIN_PCI_CF = 2
} LIN_PCI_t;

typedef struct{

    l_u8 Additional;
    l_u8 PCI_type;

}LIN_enuPCI_t;

typedef enum{

    LIN_NAD_SLEEP = 0x00,
    LIN_NAD_FUNCTIONAL = 0x7E,
    LIN_NAD_BROADCAST = 0x7F

}LIN_enuNAD_t;

typedef struct{

    LIN_enuNAD_t nad;
    LIN_enuPCI_t pci;
    LIN_enuSID_t sid;
    l_u8 Data[5];

}LIN_SF_REQUEST_t;

typedef struct{

    LIN_enuNAD_t nad;
    LIN_enuPCI_t pci;
    l_u8 rsid;
    l_u8 Data[5];

}LIN_SF_RESPONSE_t;


void lin_Transport_Layer_Handle(Lin_Frame_Slot_t *Slot);

//#endif/*LIN_TRANSPORT_LAYER*/
#endif/*LIN_TRANSPORT_LAYER_H*/