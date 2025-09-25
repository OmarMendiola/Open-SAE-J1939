/*
 * Application_Layer.h
 *
 *  Created on: 14 juli 2021
 *      Author: Daniel Mårtensson
 */

#ifndef SAE_J1939_71_APPLICATION_LAYER_SAE_J1939_71_APPLICATION_LAYER_H_
#define SAE_J1939_71_APPLICATION_LAYER_SAE_J1939_71_APPLICATION_LAYER_H_

/* Enums and structs */
#include "../../Open_SAE_J1939/Structs.h"
#include "../SAE_J1939_Enums/Enum_Control_Byte.h"
#include "../SAE_J1939_Enums/Enum_DM1_DM2.h"
#include "../SAE_J1939_Enums/Enum_DM14_DM15.h"
#include "../SAE_J1939_Enums/Enum_Group_Function_Value.h"
#include "../SAE_J1939_Enums/Enum_NAME.h"
#include "../SAE_J1939_Enums/Enum_PGN.h"
#include "../SAE_J1939_Enums/Enum_Send_Status.h"
#include "../SAE_J1939_Enums/Enum_Aplication_layer.h"
#include "../SAE_J1939_Enums/Enum_SPN_ID.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const J1939_PGN_t g_asPgnDatabase[];
extern const size_t G_SZ_PGN_DATABASE_SIZE;
extern const size_t G_SPN_DATABAE_SIZE;

extern void (*Callback_Function_Application)(SAE_Application_Info);

/* Callback functions */
void SAE_J1939_Set_Application_Callback_Function(void (*Callback_Function_Application_)(SAE_Application_Info));

/* Software identification */
ENUM_J1939_STATUS_CODES SAE_J1939_Send_Request_Software_Identification(J1939 *j1939, uint8_t DA);
ENUM_J1939_STATUS_CODES SAE_J1939_Response_Request_Software_Identification(J1939* j1939, uint8_t DA);
void SAE_J1939_Read_Response_Request_Software_Identification(J1939 *j1939, uint8_t SA, uint8_t data[]);

/* ECU identification */
ENUM_J1939_STATUS_CODES SAE_J1939_Send_Request_ECU_Identification(J1939 *j1939, uint8_t DA);
ENUM_J1939_STATUS_CODES SAE_J1939_Response_Request_ECU_Identification(J1939* j1939, uint8_t DA);
void SAE_J1939_Read_Response_Request_ECU_Identification(J1939 *j1939, uint8_t SA, uint8_t data[]);

/* Component identification */
ENUM_J1939_STATUS_CODES SAE_J1939_Send_Request_Component_Identification(J1939 *j1939, uint8_t DA);
ENUM_J1939_STATUS_CODES SAE_J1939_Response_Request_Component_Identification(J1939* j1939, uint8_t DA);
void SAE_J1939_Read_Response_Request_Component_Identification(J1939 *j1939, uint8_t SA, uint8_t data[]);

/* Proprietary A */
ENUM_J1939_STATUS_CODES SAE_J1939_Send_Request_Proprietary_A(J1939* j1939, uint8_t DA);
ENUM_J1939_STATUS_CODES SAE_J1939_Response_Request_Proprietary_A(J1939* j1939, uint8_t DA);
void SAE_J1939_Read_Response_Request_Proprietary_A(J1939* j1939, uint8_t SA, uint8_t data[]);

/* Proprietary B */
ENUM_J1939_STATUS_CODES SAE_J1939_Send_Request_Proprietary_B(J1939* j1939, uint8_t DA, uint32_t PGN);
ENUM_J1939_STATUS_CODES SAE_J1939_Response_Request_Proprietary_B(J1939* j1939, uint8_t DA, uint32_t PGN, bool * is_supported);
void SAE_J1939_Read_Response_Request_Proprietary_B(J1939* j1939, uint8_t SA, uint32_t PGN, uint8_t data[]);
struct Proprietary_B * Get_Proprietary_B_By_PGN(struct Proprietary * proprietary, uint32_t PGN);

/* Decode functions */
J1939_Decode_Status_e j1939_decode_spn(J1939_Decoded_SPN_t* psResult, const J1939_SPN_t* psSPN, const uint8_t* pu8PgnData);
const J1939_PGN_t* j1939_find_pgn(const J1939_PGN_t* pasPgnDatabase, size_t szDbSize, uint32_t u32PgnNumber);
const J1939_SPN_t* j1939_pgn_find_spn(const J1939_PGN_t* psPGN, uint32_t u32SpnNumber);

#ifdef __cplusplus
}
#endif

#endif /* SAE_J1939_71_APPLICATION_LAYER_SAE_J1939_71_APPLICATION_LAYER_H_ */
