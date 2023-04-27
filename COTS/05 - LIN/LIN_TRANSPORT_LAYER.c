

#include "LIN_TRANSPORT_LAYER.h"
#include "LIN_NETWORK_LAYER.h"
#include "LIN_TYPES.h"


//#ifdef LIN_TRANSPORT_LAYER

typedef struct{

    lin_SID_t sid;
    void (*Handler)(Lin_Frame_Slot_t* Slot);

}Lin_SID_Handler_Item_t;

extern lin_NAD_t Lin_NAD;
extern l_u16 Lin_Supplier_Id;
extern l_u16 Lin_Function_Id;

extern void lin_sid_CallBack(Lin_Frame_Slot_t* Slot);

static void lin_Assign_NAD_Hanlder(Lin_Frame_Slot_t *Slot);

Lin_SID_Handler_Item_t Lin_SID_Handler[] = {
    {
    .sid = LIN_SID_ASSIGN_NAD,
    .Handler = lin_Assign_NAD_Hanlder
    }
};


static void lin_Assign_NAD_Hanlder(Lin_Frame_Slot_t *Slot)
{
    LIN_SF_REQUEST_t *Request = (LIN_SF_REQUEST_t*)(Slot->Data);

    //#ifdef PLATFORM_IS_BIG_INDIAN

        u16 Sup = (Request->Data[1]) | ((u16)Request->Data[0] << 8);
        u16 Fun = (Request->Data[3]) | ((u16)Request->Data[2] << 8);

    //#endif 

    if((Lin_Supplier_Id == Sup) && (Lin_Function_Id == Fun)){

        Lin_NAD = Request->Data[4];

    }else{
        /*Invalid _id*/
    }   

}

static void lin_Transport_Layer_Req_Handling(Lin_Frame_Slot_t*slot)
{
    LIN_SF_REQUEST_t* Req = (LIN_SF_REQUEST_t*)(slot->Data);
    
    switch(Req->pci.PCI_type)
    {

    case LIN_PCI_SF :
                    if((Req->nad == Lin_NAD) || (Req->nad == LIN_NAD_BROADCAST)){

                        u8 i = 0;

                        for(i = 0 ; i < (sizeof(Lin_SID_Handler)/sizeof(Lin_SID_Handler[0])) ; i++){

                            if(Lin_SID_Handler[i].sid == Req->sid){

                                Lin_SID_Handler[i].Handler(slot);

                                lin_sid_CallBack(slot);
                            }else{
                                /* nothingg */
                            }                

                        }                                 

                    }else{
                        /* Different Nad*/
                    }
    break;                                    
    }
}



void lin_Transport_Layer_Handle(Lin_Frame_Slot_t* slot)
{
    switch (slot->Pid)
    {
    case LIN_DIAG_REQUEST:
                        lin_Transport_Layer_Req_Handling(slot);
        break;

    case LIN_DIAG_RESPONSE:

        break;                    
    default:
        break;
    }
}




//#endif