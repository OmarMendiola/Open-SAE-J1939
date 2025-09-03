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

/* Constant ------------------------------------------------------------------*/

/* Variables ------------------------------------------------------------------*/

/* Local Function prototypes -----------------------------------------------*/

/* Functions -----------------------------------------------------------------*/

uint8_t SAE_J1939_Transport_Protocol_Tx (J1939 *j1939, uint8_t DA, uint8_t data[], uint16_t u16DataLength, uint32_t PGN, uint8_t u8priority)
{
        uint32_t can_id = 0;
    uint8_t PDU_format = (uint8_t)(PGN >> 8);
    uint8_t PDU_specific = (uint8_t)PGN;

    // Construcción del ID J1939 de 29 bits
    can_id |= (uint32_t)(u8priority & 0x7) << 26;
    can_id |= 1UL << 25; // EDP (Extended Data Page) - debe ser 1 para J1939
    // El bit 24 (DP) se asume 0 para la mayoría de PGNs comunes

    if (PDU_format < 240) { // PDU1 Format (Destination Addressable)
        can_id |= (uint32_t)PDU_format << 16;
        can_id |= (uint32_t)DA << 8; //destination address
    } else { // PDU2 Format (Global Address)
        can_id |= (uint32_t)PDU_format << 16;
        can_id |= (uint32_t)PDU_specific << 8;
    }

    can_id |= j1939->information_this_ECU.this_ECU_address; // Source Address

    // Llamada a la capa de hardware para la transmisión física
    CAN_Send_Message(can_id, data);
}
