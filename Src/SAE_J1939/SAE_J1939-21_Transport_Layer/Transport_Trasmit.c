/*
 * @file      Transport_Trasmit.c
 * @author    Omar Mendiola
 * @brief     
 * @version   0.1
 * @date      2025-09-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */

/* Includes ------------------------------------------------------------------*/
#include "Transport_Layer.h"

/* Macros ------------------------------------------------------------------*/

#define CAN_ID_PRIORITY_POS               (26U)
#define CAN_ID_PRIORITY_MASK              (0x7U)
#define CAN_ID_EXTENDED_DATA_PAGE_POS     (25U)
#define CAN_ID_EXTENDED_DATA_PAGE_MASK    (0x1U)
#define CAN_ID_DATA_PAGE_POS              (24U)
#define CAN_ID_DATA_PAGE_MASK             (0x1U)
#define CAN_ID_PDU_FORMAT_POS             (16U)
#define CAN_ID_PDU_FORMAT_MASK            (0xFFU)
#define CAN_ID_PDU_SPECIFIC_POS           (8U)
#define CAN_ID_PDU_SPECIFIC_MASK          (0xFFU)
#define CAN_ID_SOURCE_ADDRESS_POS         (0U)
#define CAN_ID_SOURCE_ADDRESS_MASK        (0xFFU)

#define CAN_SET_PRIORITY(CAN_ID,PRIORITY)             (CAN_ID |= ((uint32_t)(PRIORITY       & CAN_ID_PRIORITY_MASK)          << CAN_ID_PRIORITY_POS))
#define CAN_SET_EXTENDED_DATA_PAGE(CAN_ID,EPD)        (CAN_ID |= ((uint32_t)(EPD            & CAN_ID_EXTENDED_DATA_PAGE_MASK)<< CAN_ID_EXTENDED_DATA_PAGE_POS))
#define CAN_SET_DATA_PAGE(CAN_ID,DATA_PAGE)           (CAN_ID |= ((uint32_t)(DATA_PAGE      & CAN_ID_DATA_PAGE_MASK)         << CAN_ID_DATA_PAGE_POS))
#define CAN_SET_PDU_FORMAT(CAN_ID,PDU_FORMAT)         (CAN_ID |= ((uint32_t)(PDU_FORMAT     & CAN_ID_PDU_FORMAT_MASK)        << CAN_ID_PDU_FORMAT_POS))
#define CAN_SET_PDU_SPECIFIC(CAN_ID,PDU_SPECIFIC)     (CAN_ID |= ((uint32_t)(PDU_SPECIFIC   & CAN_ID_PDU_SPECIFIC_MASK)      << CAN_ID_PDU_SPECIFIC_POS))
#define CAN_SET_SOURCE_ADDRESS(CAN_ID,SOURCE_ADDRESS) (CAN_ID |= ((uint32_t)(SOURCE_ADDRESS & CAN_ID_SOURCE_ADDRESS_MASK)    << CAN_ID_SOURCE_ADDRESS_POS))

/* Constant ------------------------------------------------------------------*/

/* Variables ------------------------------------------------------------------*/

/* Local Function prototypes -----------------------------------------------*/

/* Functions -----------------------------------------------------------------*/

uint8_t SAE_J1939_Transport_Protocol_Tx (J1939 *j1939, uint8_t DA, uint8_t data[], uint16_t u16DataLength, uint32_t PGN, uint8_t u8priority)
{
    //single frame
    if(u16DataLength <= 8)
    {
        uint32_t can_id = 0;
        uint8_t PDU_format = (uint8_t)(PGN >> 8);
        uint8_t PDU_specific = (uint8_t)PGN;

        // Construcción del ID J1939 de 29 bits
        CAN_SET_PRIORITY(can_id,u8priority);
        CAN_SET_EXTENDED_DATA_PAGE(can_id,0); // EDP (Extended Data Page) - debe ser 0 para J1939 // For the moment it is always 0
        // El bit 24 (DP) se asume 0 para la mayoría de PGNs comunes
        CAN_SET_DATA_PAGE(can_id,0);
        if (PDU_format < 240) { // PDU1 Format (Destination Addressable)
            CAN_SET_PDU_FORMAT(can_id,PDU_format);
            CAN_SET_PDU_SPECIFIC(can_id,DA); //destination address
        } else { // PDU2 Format (Global Address)
            CAN_SET_PDU_FORMAT(can_id,PDU_format);
            CAN_SET_PDU_SPECIFIC(can_id,PDU_specific); // Group Extension
        }

        CAN_SET_SOURCE_ADDRESS(can_id,j1939->information_this_ECU.this_ECU_address); // Source Address
        // Llamada a la capa de hardware para la transmisión física
        return CAN_Send_Message(can_id, data);
    }
    else
    {/* Multiple messages - Load data */
        	
        j1939->this_ecu_tp_cm.number_of_packages_being_transmitted = SAE_J1939_Transport_Protocol_GetNumberOfPackages(u16DataLength);
        j1939->this_ecu_tp_cm.total_message_size_being_transmitted = u16DataLength;
        for (size_t i = 0; i < u16DataLength; i++)
        {
            j1939->this_ecu_tp_dt.data[i] = data[i];
        }

        /* Send TP CM */
        j1939->this_ecu_tp_cm.PGN_of_the_packeted_message = PGN;
        j1939->this_ecu_tp_cm.control_byte = DA == 0xFF ? CONTROL_BYTE_TP_CM_BAM : CONTROL_BYTE_TP_CM_RTS; /* If broadcast, then use BAM control byte */
        ENUM_J1939_STATUS_CODES status = SAE_J1939_Send_Transport_Protocol_Connection_Management(j1939, DA);
        if(status != STATUS_SEND_OK){
            return status;
        }

        /* Check if we are going to send it directly (BAM) */
        if(j1939->this_ecu_tp_cm.control_byte == CONTROL_BYTE_TP_CM_BAM){
            j1939->from_other_ecu_tp_cm.control_byte = j1939->this_ecu_tp_cm.control_byte;
            return SAE_J1939_Send_Transport_Protocol_Data_Transfer(j1939, DA);
        }
    }

    return STATUS_SEND_OK;
}
