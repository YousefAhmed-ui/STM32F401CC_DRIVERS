


#include "LIN_TYPES.h"
#include "LIN_NETWORK_LAYER.h"
#include "LIN_HW.h"


static Lin_Frame_Slot_t *a_Slot_Array;
static l_u8 Slot_Array_Length;



void lin_Network_Init(Lin_Frame_Slot_t* Slot_Array , l_u8 Slot_Array_Len)
{
    Slot_Array_Length = Slot_Array_Len;

    a_Slot_Array = Slot_Array;

    lin_Enable_rx(L_TRUE);

}

#ifdef OPEN_LIN_DYNAMIC_IDS
        extern Lin_Id_Translation_Item_t lin_Id_Translation_Tab[];
#endif

Lin_Frame_Slot_t* lin_Get_Network_Slot(lin_pid_t Pid)
{
    Lin_Frame_Slot_t *Res = LIN_NETWORK_SLOT_EMPTY;

    l_u8 i = 0;

    #ifdef LIN_DYNAMIC_IDS
        l_u8 Translate_Found = 0;
            for(i = 0 ; i < a_Slot_Array ; i++){

                if(lin_Id_Translation_Tab[i].input_Id == Pid){
                   
                    Pid = lin_Id_Translation_Tab[i].Id_In_Lin_Table;

                    Translate_Found = 1;

                    break; 
                }else{

                    /*Do Nothing*/

                }

            }

            if(Translate_Found == 0){

                Res = NULL;

            }else{

                /*Do Nothing*/

            }
    #endif

    for(i = 0 ; i < Slot_Array_Length ; i++){

        if(a_Slot_Array[i].Pid == Pid){

            Res = &a_Slot_Array[i];

            break;

        }else{
             /*do nothing*/

        }


    }

    return Res;

}

void lin_Network_Rx_Handler(lin_pid_t Pid)
{

    Lin_Frame_Slot_t* Slot = lin_Get_Network_Slot(Pid);

    lin_On_Rx_Frame(Slot);

}