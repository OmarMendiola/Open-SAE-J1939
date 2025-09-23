// ================================================
//  @file      Enum_Aplication_Layer.h
//  @author    
//  @brief     
//  @version   0.1
//  @date      2025-09-CURRENT_DAY
//
//  @copyright Copyright (c) 2025
// ================================================

#ifndef ENUM_TRANSPORT_LAYER_H_
#define ENUM_TRANSPORT_LAYER_H_

#ifdef __cplusplus
extern "C" {
#endif

/* =================== Includes =================== */
// #include <stdint.h>
// #include <stddef.h>

/* =================== Defines ==================== */
// #define EXAMPLE_DEFINE 1

/* =================== Types ====================== */
typedef enum {
    DECODE_STATUS_SUCCESS,
    DECODE_STATUS_NULL_POINTER,
    DECODE_STATUS_INVALID_POS
} J1939_Decode_Status_e;






#ifdef __cplusplus
}
#endif

#endif // ENUM_TRANSPORT_LAYER_H_