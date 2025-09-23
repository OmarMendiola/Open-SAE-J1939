/*
 * @file      Aplication_DecodePGN.c
 * @author    
 * @brief     
 * @version   0.1
 * @date      2025-09-CURRENT_DAY
 * 
 * @copyright Copyright (c) 2025
 * 
 */

/* Includes ------------------------------------------------------------------*/
#include "Application_Layer.h"

/* Macros ------------------------------------------------------------------*/

/* Constant ------------------------------------------------------------------*/

/* Variables ------------------------------------------------------------------*/

/* Local Function prototypes -----------------------------------------------*/

/* Functions -----------------------------------------------------------------*/
/**
 * @brief    j1939_decode_spn
 * @details  Decodifica un SPN a partir de un payload de 8 bytes y llena una estructura con el resultado completo.
 * @param[out] psResult      Puntero a la estructura J1939_Decoded_SPN_t donde se almacenará el resultado.
 * @param[in]  psSPN         Puntero a la definición constante del SPN que se desea decodificar.
 * @param[in]  pu8PgnData    Puntero al arreglo de 8 bytes (payload) del PGN.
 * @return   Un código de estado (J1939_Decode_Status_e) que indica el éxito o el tipo de error de la operación.
 */
J1939_Decode_Status_e j1939_decode_spn(J1939_Decoded_SPN_t* psResult, const J1939_SPN_t* psSPN, const uint8_t* pu8PgnData) {
    if (psResult == NULL || psSPN == NULL || pu8PgnData == NULL) {
        return DECODE_STATUS_NULL_POINTER;
    }
    if (psSPN->u8StartByte >= 8) {
        return DECODE_STATUS_INVALID_POS;
    }

    memset(psResult, 0, sizeof(J1939_Decoded_SPN_t));
    psResult->psDefinition = psSPN;

    uint64_t u64RawValue = 0;
    int32_t  s32BitsToCopy = psSPN->u8LengthBits;
    uint8_t  u8CurrentByte = psSPN->u8StartByte;
    uint8_t  u8CurrentBit  = psSPN->u8StartBit;
    uint8_t  u8DestBit     = 0;

    while (s32BitsToCopy > 0 && u8CurrentByte < 8) {
        int32_t s32BitsInByte = 8 - u8CurrentBit;
        int32_t s32BitsThisRound = (s32BitsToCopy < s32BitsInByte) ? s32BitsToCopy : s32BitsInByte;

        uint8_t u8Mask = ((1 << s32BitsThisRound) - 1) << u8CurrentBit;
        uint64_t u64ExtractedBits = (pu8PgnData[u8CurrentByte] & u8Mask) >> u8CurrentBit;
        
        u64RawValue |= (u64ExtractedBits << u8DestBit);

        s32BitsToCopy -= s32BitsThisRound;
        u8DestBit += s32BitsThisRound;
        u8CurrentByte++;
        u8CurrentBit = 0;
    }

    psResult->u64RawValue = u64RawValue;
    psResult->dPhysicalValue = (double)u64RawValue * psSPN->fScaling + psSPN->fOffset;

    return DECODE_STATUS_SUCCESS;
}

/**
 * @brief    j1939_find_pgn
 * @details  Busca la definición de un PGN en una base de datos de PGNs.
 * @param[in]  pasPgnDatabase  Puntero al arreglo (base de datos) de definiciones de PGNs.
 * @param[in]  szDbSize        Número total de elementos en la base de datos.
 * @param[in]  u32PgnNumber    El número del PGN que se desea encontrar.
 * @return   Un puntero constante a la definición del PGN si se encuentra; de lo contrario, retorna NULL.
 */
const J1939_PGN_t* j1939_find_pgn(const J1939_PGN_t* pasPgnDatabase, size_t szDbSize, uint32_t u32PgnNumber) {
    for (size_t i = 0; i < szDbSize; ++i) {
        if (pasPgnDatabase[i].u32Number == u32PgnNumber) {
            return &pasPgnDatabase[i];
        }
    }
    return NULL;
}

/**
 * @brief    j1939_pgn_find_spn
 * @details  Busca la definición de un SPN por su número dentro de una estructura PGN ya encontrada.
 * @param[in]  psPGN         Puntero a la definición del PGN en el que se realizará la búsqueda.
 * @param[in]  u32SpnNumber  El número del SPN que se desea encontrar.
 * @return   Un puntero constante a la definición del SPN si se encuentra; de lo contrario, retorna NULL.
 */
const J1939_SPN_t* j1939_pgn_find_spn(const J1939_PGN_t* psPGN, uint32_t u32SpnNumber) {
    if (psPGN == NULL) {
        return NULL;
    }
    for (uint8_t i = 0; i < psPGN->u8NumSpns; ++i) {
        if (psPGN->pasSPNs[i].u32Number == u32SpnNumber) {
            return &psPGN->pasSPNs[i];
        }
    }
    return NULL;
}