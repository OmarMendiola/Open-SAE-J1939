/*
 * @file      Open_SAE_J1939_Test.c
 * @author    
 * @brief     
 * @version   0.1
 * @date      2025-09-CURRENT_DAY
 * 
 * @copyright Copyright (c) 2025
 * 
 */

/* Includes ------------------------------------------------------------------*/
#include "Open_SAE_J1939.h"

/* Macros ------------------------------------------------------------------*/

/* Constant ------------------------------------------------------------------*/

/* Variables ------------------------------------------------------------------*/

/* Local Function prototypes -----------------------------------------------*/
#ifdef __cplusplus //temporal solution to link C functions with C++ code
extern "C" {
#endif

extern void AtCommand_PrintWrapper(const char* format) ;

#ifdef __cplusplus
}
#endif

/* Functions -----------------------------------------------------------------*/
void Open_SAE_J1939_Test_Trasmission(J1939* j1939)
{
uint8_t u8Result;
    uint8_t data[8] = {0};
    data[0] = 0x01;
    data[1] = 0x02;
    data[2] = 0x03;
    data[3] = 0x04;
    data[4] = 0x05;
    data[5] = 0x06;
    data[6] = 0x07;
    data[7] = 0x08;

    u8Result = SAE_J1939_Transport_Protocol_Tx(j1939, 0xFF, data, 8, 0x00F005, 6); // Send a DM1 message as a test

    if (u8Result == STATUS_SEND_OK) {
        AtCommand_PrintWrapper("J1939 Test Transmission: Message sent successfully.\n\r");
    } else if (u8Result == STATUS_SEND_ERROR) {
        AtCommand_PrintWrapper("J1939 Test Transmission: Error sending message.\n\r");
    } else if (u8Result == STATUS_SEND_BUSY) {
        AtCommand_PrintWrapper("J1939 Test Transmission: Busy, message not sent.\n\r");
    } else
    {
        /* code */
    }
    
};

void Open_SAE_J1939_Test_Trasmission_multipacket(J1939* j1939)
{
uint8_t u8Result;
    uint8_t data[1000] = {0xDE};
    data[0] = 0x01;
    data[1] = 0x02;
    data[2] = 0x03;
    data[3] = 0x04;
    data[4] = 0x05;
    data[5] = 0x06;
    data[6] = 0x07;
    data[7] = 0x08;

    u8Result = SAE_J1939_Transport_Protocol_Tx(j1939, 0xFF, data, 8, 0x00F004, 7); // Send a DM1 message as a test

    if (u8Result == STATUS_SEND_OK) {
        AtCommand_PrintWrapper("J1939 Test Transmission: Message sent successfully.\n\r");
    } else if (u8Result == STATUS_SEND_ERROR) {
        AtCommand_PrintWrapper("J1939 Test Transmission: Error sending message.\n\r");
    } else if (u8Result == STATUS_SEND_BUSY) {
        AtCommand_PrintWrapper("J1939 Test Transmission: Busy, message not sent.\n\r");
    } else
    {
        /* code */
    }
    
};
