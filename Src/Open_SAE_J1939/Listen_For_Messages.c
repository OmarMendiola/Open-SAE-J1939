/*
 * Listen_For_Messages.c
 *
 *  Created on: 14 juli 2021
 *      Author: Daniel Mårtensson
 */

#include "Open_SAE_J1939.h"
#include "stdio.h"
#include "CircularBuffer.h"

/* Layers */
#include "../ISO_11783/ISO_11783-7_Application_Layer/Application_Layer.h"
#include "../Hardware/Hardware.h"

#define TEST_LISTEN_FOR_MESSAGES 0

#ifdef __cplusplus //temporal solution to link C functions with C++ code
extern "C" {
#endif

// VARIABLES
CIRCULAR_BUF_DEFINE(casPGN_RX_buffer,J1939_RX_PGN_t,10);

extern void AtCommand_PrintWrapper(const char* format) ;

#ifdef __cplusplus
}
#endif

char pszBuffer[127];

static inline void test_check_bufffer_counters(void)
{
#if TEST_LISTEN_FOR_MESSAGES == 1
	#warning "TEST_LISTEN_FOR_MESSAGES is enabled"
	snprintf(pszBuffer,(sizeof(pszBuffer) - 1), "Buffer head: %u | Buffer tail: %u | Buffer size: %u | Buffer capacity: %u \n\r", casPGN_RX_buffer.head, casPGN_RX_buffer.tail, circular_buf_get_size(&casPGN_RX_buffer), circular_buf_get_capacity(&casPGN_RX_buffer));
	AtCommand_PrintWrapper(pszBuffer);
#endif
}

static inline void test_print_CAN_message(J1939_CAN_ID* pcan_Id, uint32_t ID, uint32_t PGN, uint8_t* data)
{
#if TEST_LISTEN_FOR_MESSAGES == 1
	#warning "test_print_CAN_message is enabled"
	/* Debug print */	
	snprintf(pszBuffer,(sizeof(pszBuffer) - 1), "J1939 Received: ID: 0x%08X | PGN: 0x%05X | Pri: %u | DP: %u | PF: %u | PS/DA: %u | SA: %u | Data: ", ID, PGN, pcan_Id->fields.priority, pcan_Id->fields.data_page, pcan_Id->fields.pdu_format, pcan_Id->fields.pdu_specific, pcan_Id->fields.source_address);
	AtCommand_PrintWrapper(pszBuffer);
	snprintf(pszBuffer,(sizeof(pszBuffer) - 1), " %02X %02X %02X %02X %02X %02X %02X %02X \n\r", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
	AtCommand_PrintWrapper(pszBuffer);
	AtCommand_PrintWrapper("\n\r");
#endif
}



/* This function should be called all the time, or be placed inside an interrupt listener */
ENUM_J1939_RX_MSG Open_SAE_J1939_Listen_For_Messages(J1939* j1939) {
	uint32_t ID = 0;
	uint8_t data[8] = {0};
	ENUM_J1939_RX_MSG rx_msg = RX_MSG_NONE;
	J1939_CAN_ID* pcan_Id;
	bool is_new_message = CAN_Read_Message(&ID, data);
	if(is_new_message) {
		/* Save latest */
		j1939->ID = ID;
		memcpy(j1939->data, data, 8);
		j1939->ID_and_data_is_updated = true;

		uint8_t id0 = ID >> 24;
		uint8_t id1 = ID >> 16; /* PDU Format (PF) */
		uint8_t DA = ID >> 8; 	/* PDU Specific (PS) or destination address which is this ECU. if DA = 0xFF = broadcast to all ECU. Sometimes DA can be an ID number too */
		uint8_t SA = ID; 	/* Source address of the ECU that we got the message from */

		uint32_t PGN;

		/* Properly calculate PGN based on PF (id1) */
		if (id1 >= 240){
    			PGN = (ID >> 8) & 0x3FFFFUL; /* Mask for including EDP, DP, PF, and PS in the PGN */
		}else{
    			PGN = (ID >> 8) & 0x3FF00UL; /* Mask for including EDP, DP, and PF only (exclude PS) */
		}

		pcan_Id = (J1939_CAN_ID*)&ID;

		// Find PGN in database
		const J1939_PGN_t* psPGN_info = j1939_find_pgn(g_asPgnDatabase, G_SZ_PGN_DATABASE_SIZE,PGN);
		if(psPGN_info != NULL) {
			test_print_CAN_message(pcan_Id, ID, PGN, data); //test ofmm
			// PGN found in database
			if(circular_buf_is_full(&casPGN_RX_buffer) == false) {
				test_check_bufffer_counters(); //test ofmm
				// We have space in h buffer
				J1939_RX_PGN_t pgn_entry;
				pgn_entry.psPGNInfo = (J1939_PGN_t*)psPGN_info;
				memcpy(pgn_entry.au8Data, data, 8);
				circular_buf_push(&casPGN_RX_buffer, &pgn_entry);
			}
			else {
			}
		} else {
			// PGN not found in database
			// Handle unknown PGN if necessary
		}

		rx_msg = RX_MSG_NOT_SUPPORTED;

		/* Read request from other ECU */
		if (id0 == 0x18 && id1 == 0xEA && (DA == j1939->information_this_ECU.this_ECU_address || DA == 0xFF)){
			SAE_J1939_Read_Request(j1939, SA, data);
			rx_msg = RX_MSG_REQ;
		}else if (id0 == 0x18 && id1 == 0xD9 && DA == j1939->information_this_ECU.this_ECU_address){
			SAE_J1939_Read_Request_DM14(j1939, SA, data);
			rx_msg = RX_MSG_REQ_DM14;

		/* Read status from other ECU */
		}else if(id0 == 0x18 && id1 == 0xE8 && DA == j1939->information_this_ECU.this_ECU_address){
			SAE_J1939_Read_Acknowledgement(j1939, SA, data);
			rx_msg = RX_MSG_ACK;
		}else if (id0 == 0x18 && id1 == 0xD8 && DA == j1939->information_this_ECU.this_ECU_address){
			SAE_J1939_Read_Response_DM15(j1939, SA, data);
			rx_msg = RX_MSG_DM15;
		}else if(id0 == 0x18 && id1 == 0xD7 && DA == j1939->information_this_ECU.this_ECU_address){
			SAE_J1939_Read_Binary_Data_Transfer_DM16(j1939, SA, data);
			rx_msg = RX_MSG_DM16;

		/* Read Transport Protocol information from other ECU */
		}else if(id0 == 0x1C && id1 == 0xEC && (DA == j1939->information_this_ECU.this_ECU_address || DA == 0xFF)){
			SAE_J1939_Read_Transport_Protocol_Connection_Management(j1939, SA, data);
			rx_msg = RX_MSG_TP_CONN_MANAGEMENT;
		}else if (id0 == 0x1C && id1 == 0xEB && (DA == j1939->information_this_ECU.this_ECU_address || DA == 0xFF)){
			SAE_J1939_Read_Transport_Protocol_Data_Transfer(j1939, SA, data);
			rx_msg = RX_MSG_TP_CONN_DATA_TRANSFER;

		/* Read response request from other ECU - This are response request. They are responses from other ECU about request from this ECU */
		}else if (id0 == 0x14 && id1 == 0xEF && DA == 0x23) {
			SAE_J1939_Read_Response_Request_Proprietary_A(j1939, SA, data);										/* Manufacturer specific data */
			rx_msg = RX_MSG_RESP_REQ_PROPRIETARY_A;
		}else if (((PGN >= PGN_PROPRIETARY_B_START) && (PGN <= PGN_PROPRIETARY_B_END)) || 
				  ((PGN >= PGN_PROPRIETARY_B2_START) && (PGN <= PGN_PROPRIETARY_B2_END))) {
			SAE_J1939_Read_Response_Request_Proprietary_B(j1939, SA, PGN, data);								/* Manufacturer specific data (B) */
			rx_msg = RX_MSG_RESP_REQ_PROPRIETARY_B;
		}else if (id0 == 0x18 && id1 == 0xEE && DA == 0xFF && SA != 0xFE){
			SAE_J1939_Read_Response_Request_Address_Claimed(j1939, SA, data);									/* This is a broadcast response request */
			rx_msg = RX_MSG_RESP_REQ_ADDR_CLAIMED;
		}else if (id0 == 0x18 && id1 == 0xEE && DA == 0xFF && SA == 0xFE) {
			SAE_J1939_Read_Address_Not_Claimed(j1939, SA, data);												/* This is error */
			rx_msg = RX_MSG_ADDR_NOT_CLAIMED;

		}else if (id0 == 0x18 && id1 == 0xFE && DA == 0xCA){
			SAE_J1939_Read_Response_Request_DM1(j1939, SA, data, 1); 											/* Assume that errors_dm1_active = 1 */
			rx_msg = RX_MSG_RESP_REQ_DM1;
		}else if (id0 == 0x18 && id1 == 0xFE && DA == 0xCB){
			SAE_J1939_Read_Response_Request_DM2(j1939, SA, data, 1); 											/* Assume that errors_dm2_active = 1 */
			rx_msg = RX_MSG_RESP_REQ_DM2;
		}else if (id0 == 0x18 && id1 == 0xFE && DA == 0xDA){
			SAE_J1939_Read_Response_Request_Software_Identification(j1939, SA, data);
			rx_msg = RX_MSG_RESP_REQ_SOFTWARE_IDENTIFICATION;
		}else if (id0 == 0x18 && id1 == 0xFD && DA == 0xC5){
			SAE_J1939_Read_Response_Request_ECU_Identification(j1939, SA, data);
			rx_msg = RX_MSG_RESP_REQ_ECU_IDENTIFICATION;
		}else if (id0 == 0x18 && id1 == 0xFE && DA == 0xEB){
			SAE_J1939_Read_Response_Request_Component_Identification(j1939, SA, data);
			rx_msg = RX_MSG_RESP_REQ_COMPONENT_IDENTIFICATION;
		}else if (id0 == 0x0C && id1 == 0xFE && DA >= 0x10 && DA <= 0x1F){
			ISO_11783_Read_Response_Request_Auxiliary_Estimated_Flow(j1939, SA, DA & 0xF, data);				/* DA & 0xF = Valve number. Total 16 valves from 0 to 15 */
			rx_msg = RX_MSG_RESP_REQ_AUX_ESTIMATED_FLOW;
		}else if (id0 == 0x0C && id1 == 0xC6 && DA == j1939->information_this_ECU.this_ECU_address){
			ISO_11783_Read_Response_Request_General_Purpose_Valve_Estimated_Flow(j1939, SA, data);
			rx_msg = RX_MSG_RESP_REQ_GP_VALVE_ESTIMATED_FLOW;
		}else if (id0 == 0x0C && id1 == 0xFF && DA >= 0x20 && DA <= 0x2F) {
			ISO_11783_Read_Response_Request_Auxiliary_Valve_Measured_Position(j1939, SA, DA & 0xF, data); 		/* DA & 0xF = Valve number. Total 16 valves from 0 to 15 */
			rx_msg = RX_MSG_RESP_REQ_AUX_VALVE_MEASURED_POSITION;

		/* Read command from other ECU */
		}else if (id0 == 0x0C && id1 == 0xFE && DA >= 0x30 && DA <= 0x3F){
			ISO_11783_Read_Auxiliary_Valve_Command(j1939, SA, DA & 0xF, data); 									/* DA & 0xF = Valve number. Total 16 valves from 0 to 15 */
			rx_msg = RX_MSG_AUX_VALVE_CMD;
		}else if (id0 == 0x0C && id1 == 0xC4 && DA == j1939->information_this_ECU.this_ECU_address){
			ISO_11783_Read_General_Purpose_Valve_Command(j1939, SA, data);										/* General Purpose Valve Command have only one valve */
			rx_msg = RX_MSG_GP_VALVE_CMD;
		}else if (id0 == 0x0 && id1 == 0x2 && (DA == j1939->information_this_ECU.this_ECU_address || DA == 0xFF)){
			SAE_J1939_Read_Address_Delete(j1939, data);															/* Not a SAE J1939 standard */
			rx_msg = RX_MSG_NOT_SAE_J1939;
		}else{
			rx_msg = RX_MSG_UNKNOWN;																			/* The message was not meant for this ECU */
		}
		/* Add more else if statement here */
	}
	else
	{
		///AtCommand_PrintWrapper("NO LLEgo mensaje");
	}
	return rx_msg;
}


 bool Open_SAE_J1939_ReadPGN(J1939_RX_PGN_t* pReceivedPGN)
 {
	 if(circular_buf_is_empty(&casPGN_RX_buffer) == false) 
	 {
		test_check_bufffer_counters(); //test ofmm
		circular_buf_pop(&casPGN_RX_buffer, pReceivedPGN);
		 return true;
	 } else 
	 {
		//test_check_bufffer_counters(); //test ofmm
		 return false;
	 }
 }	

 J1939_Decode_Status_e  Open_SAE_J1939_DecodeSPN(J1939_Decoded_SPN_t* psResult, const J1939_SPN_t* psSPN, const uint8_t* pu8PgnData)
 {
	J1939_Decode_Status_e eStatus = j1939_decode_spn(&psResult, psSPN, pu8PgnData);
	return eStatus;
 }