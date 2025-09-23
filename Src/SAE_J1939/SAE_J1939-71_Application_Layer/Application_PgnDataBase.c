/*
 * @file      Application_PgnDataBase.c
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
// --- SPNs para PGN 65265 (Cruise Control/Vehicle Speed - CCVS) ---
const J1939_SPN_t g_asSpnsPGN65265[] = {
    {.u32Number = 69,  .pszName = "Two Speed Axle Switch",                 .u8StartByte = 0, .u8StartBit = 0, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 70,  .pszName = "Parking Brake Switch",                  .u8StartByte = 0, .u8StartBit = 2, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1633,.pszName = "Cruise Control Pause Switch",           .u8StartByte = 0, .u8StartBit = 4, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 84,  .pszName = "Wheel-Based Vehicle Speed",             .u8StartByte = 1, .u8StartBit = 0, .u8LengthBits = 16, .fScaling = 0.00390625f, .fOffset = 0, .eUnitId = eUnitPhy_KMH},
    {.u32Number = 595, .pszName = "Cruise Control Active",                 .u8StartByte = 3, .u8StartBit = 0, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 596, .pszName = "Cruise Control Enable Switch",          .u8StartByte = 3, .u8StartBit = 2, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 597, .pszName = "Brake Switch",                          .u8StartByte = 3, .u8StartBit = 4, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 598, .pszName = "Clutch Switch",                         .u8StartByte = 3, .u8StartBit = 6, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 599, .pszName = "Cruise Control Set Switch",             .u8StartByte = 4, .u8StartBit = 0, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 600, .pszName = "Cruise Control Coast (Decelerate) Switch",.u8StartByte = 4, .u8StartBit = 2, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 601, .pszName = "Cruise Control Resume Switch",            .u8StartByte = 4, .u8StartBit = 4, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 602, .pszName = "Cruise Control Accelerate Switch",      .u8StartByte = 4, .u8StartBit = 6, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 86,  .pszName = "Cruise Control Set Speed",              .u8StartByte = 5, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_KMH},
    {.u32Number = 976, .pszName = "PTO State",                             .u8StartByte = 6, .u8StartBit = 0, .u8LengthBits = 5,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 527, .pszName = "Cruise Control States",                 .u8StartByte = 6, .u8StartBit = 5, .u8LengthBits = 3,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 968, .pszName = "Idle Increment Switch",                 .u8StartByte = 7, .u8StartBit = 0, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 967, .pszName = "Idle Decrement Switch",                 .u8StartByte = 7, .u8StartBit = 2, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 966, .pszName = "Engine Test Mode Switch",               .u8StartByte = 7, .u8StartBit = 4, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1237,.pszName = "Engine Shutdown Override Switch",       .u8StartByte = 7, .u8StartBit = 6, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
};

// --- SPNs para PGN 61441 (Electronic Brake Controller 1 - EBC1) ---
const J1939_SPN_t g_asSpnsPGN61441[] = {
    {.u32Number = 561, .pszName = "ASR Engine Control Active",       .u8StartByte = 0, .u8StartBit = 0, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 562, .pszName = "ASR Brake Control Active",        .u8StartByte = 0, .u8StartBit = 2, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 563, .pszName = "Anti-Lock Braking (ABS) Active",  .u8StartByte = 0, .u8StartBit = 4, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1121,.pszName = "EBS Brake Switch",                .u8StartByte = 0, .u8StartBit = 6, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 521, .pszName = "Brake Pedal Position",            .u8StartByte = 1, .u8StartBit = 0, .u8LengthBits = 8, .fScaling = 0.4f, .fOffset = 0, .eUnitId = eUnitPhy_Percentage},
    {.u32Number = 575, .pszName = "ABS Off-road Switch",             .u8StartByte = 2, .u8StartBit = 0, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 576, .pszName = "ASR Off-road Switch",             .u8StartByte = 2, .u8StartBit = 2, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 577, .pszName = "ASR 'Hill Holder' Switch",        .u8StartByte = 2, .u8StartBit = 4, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1238,.pszName = "Traction Control Override Switch",.u8StartByte = 2, .u8StartBit = 6, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 972, .pszName = "Accelerator Interlock Switch",    .u8StartByte = 3, .u8StartBit = 0, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 971, .pszName = "Engine Derate Switch",            .u8StartByte = 3, .u8StartBit = 2, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 970, .pszName = "Auxiliary Engine Shutdown Switch",.u8StartByte = 3, .u8StartBit = 4, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 969, .pszName = "Remote Accelerator Enable Switch",.u8StartByte = 3, .u8StartBit = 6, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 973, .pszName = "Engine Retarder Selection",       .u8StartByte = 4, .u8StartBit = 0, .u8LengthBits = 8, .fScaling = 0.4f, .fOffset = 0, .eUnitId = eUnitPhy_Percentage},
    {.u32Number = 1243,.pszName = "ABS Fully Operational",           .u8StartByte = 5, .u8StartBit = 0, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1439,.pszName = "EBS Red Warning Signal",          .u8StartByte = 5, .u8StartBit = 2, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1438,.pszName = "ABS/EBS Amber Warning Signal",    .u8StartByte = 5, .u8StartBit = 4, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1793,.pszName = "ATC/ASR Information Signal",      .u8StartByte = 5, .u8StartBit = 6, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1481,.pszName = "Source Address of Controlling Device for Brake Control",.u8StartByte = 6, .u8StartBit = 0, .u8LengthBits = 8, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1836,.pszName = "Trailer ABS Status",              .u8StartByte = 7, .u8StartBit = 4, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1792,.pszName = "Tractor-Mounted Trailer ABS Warning Signal",.u8StartByte = 7, .u8StartBit = 6, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
};

// --- SPNs para PGN 57344 (Cab Message 1 - CM1) ---
const J1939_SPN_t g_asSpnsPGN57344[] = {
    {.u32Number = 986, .pszName = "Requested Percent Fan Speed",        .u8StartByte = 0, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 0.4f, .fOffset = 0, .eUnitId = eUnitPhy_Percentage},
    {.u32Number = 1691,.pszName = "Cab Interior Temperature Command",     .u8StartByte = 1, .u8StartBit = 0, .u8LengthBits = 16, .fScaling = 0.03125f, .fOffset = -273.0f, .eUnitId = eUnitPhy_CELSIUS},
    {.u32Number = 1684,.pszName = "Auxiliary Heater Coolant Pump Request",.u8StartByte = 3, .u8StartBit = 0, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1682,.pszName = "Battery Main Switch Hold Request",     .u8StartByte = 3, .u8StartBit = 2, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1714,.pszName = "Operator Seat Direction Switch",       .u8StartByte = 3, .u8StartBit = 4, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1856,.pszName = "Seat Belt Switch",                   .u8StartByte = 3, .u8StartBit = 6, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1655,.pszName = "Vehicle Limiting Speed Governor Decrement Switch",.u8StartByte = 4, .u8StartBit = 2, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1654,.pszName = "Vehicle Limiting Speed Governor Increment Switch",.u8StartByte = 4, .u8StartBit = 4, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1653,.pszName = "Vehicle Limiting Speed Governor Enable Switch",.u8StartByte = 4, .u8StartBit = 6, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1666,.pszName = "Automatic Gear Shifting Enable Switch",.u8StartByte = 5, .u8StartBit = 4, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1656,.pszName = "Engine Automatic Start Enable Switch", .u8StartByte = 5, .u8StartBit = 6, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1683,.pszName = "Auxiliary Heater Mode Request",      .u8StartByte = 6, .u8StartBit = 0, .u8LengthBits = 4,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1685,.pszName = "Request Engine Zone Heating",        .u8StartByte = 6, .u8StartBit = 4, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1686,.pszName = "Request Cab Zone Heating",           .u8StartByte = 6, .u8StartBit = 6, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 2596,.pszName = "Selected Maximum Vehicle Speed Limit",.u8StartByte = 7, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
};

// --- SPNs para PGN 61444 (Electronic Engine Controller 1 - EEC1) ---
const J1939_SPN_t g_asSpnsPGN61444[] = {
    {.u32Number = 899, .pszName = "Engine Torque Mode",               .u8StartByte = 0, .u8StartBit = 0, .u8LengthBits = 4,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 512, .pszName = "Driver's Demand Engine - Percent Torque",.u8StartByte = 1, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 1.0f, .fOffset = -125.0f, .eUnitId = eUnitPhy_Percentage},
    {.u32Number = 513, .pszName = "Actual Engine - Percent Torque",     .u8StartByte = 2, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 1.0f, .fOffset = -125.0f, .eUnitId = eUnitPhy_Percentage},
    {.u32Number = 190, .pszName = "Engine Speed",                     .u8StartByte = 3, .u8StartBit = 0, .u8LengthBits = 16, .fScaling = 0.125f, .fOffset = 0, .eUnitId = eUnitPhy_RPM},
    {.u32Number = 1483,.pszName = "Source Address of Controlling Device for Engine Control",.u8StartByte = 5, .u8StartBit = 0, .u8LengthBits = 8, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1675,.pszName = "Engine Starter Mode",              .u8StartByte = 6, .u8StartBit = 0, .u8LengthBits = 4, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 2432,.pszName = "Engine Demand - Percent Torque",   .u8StartByte = 7, .u8StartBit = 0, .u8LengthBits = 8, .fScaling = 1.0f, .fOffset = -125.0f, .eUnitId = eUnitPhy_Percentage},
};

// --- SPNs para PGN 65262 (Engine Temperature 1 - ET1) ---
const J1939_SPN_t g_asSpnsPGN65262[] = {
    {.u32Number = 110, .pszName = "Engine Coolant Temperature",        .u8StartByte = 0, .u8StartBit = 0, .u8LengthBits = 8, .fScaling = 1.0f, .fOffset = -40.0f, .eUnitId = eUnitPhy_CELSIUS},
    {.u32Number = 174, .pszName = "Fuel Temperature",                  .u8StartByte = 1, .u8StartBit = 0, .u8LengthBits = 8, .fScaling = 1.0f, .fOffset = -40.0f, .eUnitId = eUnitPhy_CELSIUS},
    {.u32Number = 175, .pszName = "Engine Oil Temperature 1",          .u8StartByte = 2, .u8StartBit = 0, .u8LengthBits = 16,.fScaling = 0.03125f, .fOffset = -273.0f, .eUnitId = eUnitPhy_CELSIUS},
    {.u32Number = 176, .pszName = "Turbo Oil Temperature",             .u8StartByte = 4, .u8StartBit = 0, .u8LengthBits = 16,.fScaling = 0.03125f, .fOffset = -273.0f, .eUnitId = eUnitPhy_CELSIUS},
    {.u32Number = 52,  .pszName = "Engine Intercooler Temperature",    .u8StartByte = 6, .u8StartBit = 0, .u8LengthBits = 8, .fScaling = 1.0f, .fOffset = -40.0f, .eUnitId = eUnitPhy_CELSIUS},
    {.u32Number = 1134,.pszName = "Engine Intercooler Thermostat Opening",.u8StartByte = 7, .u8StartBit = 0, .u8LengthBits = 8, .fScaling = 0.4f, .fOffset = 0, .eUnitId = eUnitPhy_Percentage},
};

// --- SPNs para PGN 65263 (Engine Fluid Level/Pressure 1 - EFL/P1) ---
const J1939_SPN_t g_asSpnsPGN65263[] = {
    {.u32Number = 94,  .pszName = "Fuel Delivery Pressure",         .u8StartByte = 0, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 4.0f, .fOffset = 0, .eUnitId = eUnitPhy_KPA},
    {.u32Number = 22,  .pszName = "Extended Crankcase Blow-by Pressure",.u8StartByte = 1, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 0.05f, .fOffset = 0, .eUnitId = eUnitPhy_KPA},
    {.u32Number = 98,  .pszName = "Engine Oil Level",               .u8StartByte = 2, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 0.4f, .fOffset = 0, .eUnitId = eUnitPhy_Percentage},
    {.u32Number = 100, .pszName = "Engine Oil Pressure",            .u8StartByte = 3, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 4.0f, .fOffset = 0, .eUnitId = eUnitPhy_KPA},
    {.u32Number = 101, .pszName = "Crankcase Pressure",             .u8StartByte = 4, .u8StartBit = 0, .u8LengthBits = 16, .fScaling = 0.0078125f, .fOffset = -250.0f, .eUnitId = eUnitPhy_KPA},
    {.u32Number = 109, .pszName = "Coolant Pressure",               .u8StartByte = 6, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 2.0f, .fOffset = 0, .eUnitId = eUnitPhy_KPA},
    {.u32Number = 111, .pszName = "Coolant Level",                  .u8StartByte = 7, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 0.4f, .fOffset = 0, .eUnitId = eUnitPhy_Percentage},
};

// --- SPNs para PGN 65270 (Inlet/Exhaust Conditions 1 - IC1) ---
const J1939_SPN_t g_asSpnsPGN65270[] = {
    {.u32Number = 81,  .pszName = "Particulate Trap Inlet Pressure",   .u8StartByte = 0, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 0.5f, .fOffset = 0, .eUnitId = eUnitPhy_KPA},
    {.u32Number = 102, .pszName = "Boost Pressure",                    .u8StartByte = 1, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 2.0f, .fOffset = 0, .eUnitId = eUnitPhy_KPA},
    {.u32Number = 105, .pszName = "Intake Manifold 1 Temperature",     .u8StartByte = 2, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 1.0f, .fOffset = -40.0f, .eUnitId = eUnitPhy_CELSIUS},
    {.u32Number = 106, .pszName = "Air Inlet Pressure",                .u8StartByte = 3, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 2.0f, .fOffset = 0, .eUnitId = eUnitPhy_KPA},
    {.u32Number = 107, .pszName = "Air Filter 1 Differential Pressure",.u8StartByte = 4, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 0.05f, .fOffset = 0, .eUnitId = eUnitPhy_KPA},
    {.u32Number = 173, .pszName = "Exhaust Gas Temperature",           .u8StartByte = 5, .u8StartBit = 0, .u8LengthBits = 16, .fScaling = 0.03125f, .fOffset = -273.0f, .eUnitId = eUnitPhy_CELSIUS},
    {.u32Number = 112, .pszName = "Coolant Filter Differential Pressure",.u8StartByte = 7, .u8StartBit = 0, .u8LengthBits = 8, .fScaling = 0.5f, .fOffset = 0, .eUnitId = eUnitPhy_KPA},
};

// --- SPNs para PGN 65253 (Engine Hours, Revolutions - HOURS) ---
const J1939_SPN_t g_asSpnsPGN65253[] = {
    {.u32Number = 247, .pszName = "Total Engine Hours",      .u8StartByte = 0, .u8StartBit = 0, .u8LengthBits = 32, .fScaling = 0.05f, .fOffset = 0, .eUnitId = eUnitPhy_HOUR},
    {.u32Number = 249, .pszName = "Total Engine Revolutions",.u8StartByte = 4, .u8StartBit = 0, .u8LengthBits = 32, .fScaling = 1000.0f, .fOffset = 0, .eUnitId = eUnitPhy_RPM}, // Units are Revolutions, using RPM as placeholder
};

// --- SPNs para PGN 65257 (Fuel Consumption (Liquid) - LFC) ---
const J1939_SPN_t g_asSpnsPGN65257[] = {
    {.u32Number = 182, .pszName = "Trip Fuel",     .u8StartByte = 0, .u8StartBit = 0, .u8LengthBits = 32, .fScaling = 0.5f, .fOffset = 0, .eUnitId = eUnitPhy_LITER},
    {.u32Number = 250, .pszName = "Total Fuel Used",.u8StartByte = 4, .u8StartBit = 0, .u8LengthBits = 32, .fScaling = 0.5f, .fOffset = 0, .eUnitId = eUnitPhy_LITER},
};

// --- SPNs para PGN 65266 (Fuel Economy (Liquid) - LFE) ---
const J1939_SPN_t g_asSpnsPGN65266[] = {
    {.u32Number = 183, .pszName = "Fuel Rate",                .u8StartByte = 0, .u8StartBit = 0, .u8LengthBits = 16, .fScaling = 0.05f, .fOffset = 0, .eUnitId = eUnitPhy_LITER_PER_HOUR}, // Custom unit
    {.u32Number = 184, .pszName = "Instantaneous Fuel Economy",.u8StartByte = 2, .u8StartBit = 0, .u8LengthBits = 16, .fScaling = 0.001953125f, .fOffset = 0, .eUnitId = eUnitPhy_KM_PER_LITER},
    {.u32Number = 185, .pszName = "Average Fuel Economy",     .u8StartByte = 4, .u8StartBit = 0, .u8LengthBits = 16, .fScaling = 0.001953125f, .fOffset = 0, .eUnitId = eUnitPhy_KM_PER_LITER},
    {.u32Number = 51,  .pszName = "Throttle Position",        .u8StartByte = 6, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 0.4f, .fOffset = 0, .eUnitId = eUnitPhy_Percentage},
};

// --- SPNs para PGN 65271 (Vehicle Electrical Power - VEP) ---
const J1939_SPN_t g_asSpnsPGN65271[] = {
    {.u32Number = 114, .pszName = "Net Battery Current",              .u8StartByte = 0, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 1.0f, .fOffset = -125.0f, .eUnitId = eUnitPhy_AMPERE}, // Custom unit
    {.u32Number = 115, .pszName = "Alternator Current",               .u8StartByte = 1, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_AMPERE}, // Custom unit
    {.u32Number = 167, .pszName = "Alternator Potential (Voltage)",   .u8StartByte = 2, .u8StartBit = 0, .u8LengthBits = 16, .fScaling = 0.05f, .fOffset = 0, .eUnitId = eUnitPhy_VOLT},
    {.u32Number = 168, .pszName = "Electrical Potential (Voltage)",   .u8StartByte = 4, .u8StartBit = 0, .u8LengthBits = 16, .fScaling = 0.05f, .fOffset = 0, .eUnitId = eUnitPhy_VOLT},
    {.u32Number = 158, .pszName = "Battery Potential (Voltage), Switched",.u8StartByte = 6, .u8StartBit = 0, .u8LengthBits = 16, .fScaling = 0.05f, .fOffset = 0, .eUnitId = eUnitPhy_VOLT},
};

// --- SPNs para PGN 65276 (Dash Display - DD) ---
const J1939_SPN_t g_asSpnsPGN65276[] = {
    {.u32Number = 80,  .pszName = "Washer Fluid Level",               .u8StartByte = 0, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 0.4f, .fOffset = 0, .eUnitId = eUnitPhy_Percentage},
    {.u32Number = 96,  .pszName = "Fuel Level",                       .u8StartByte = 1, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 0.4f, .fOffset = 0, .eUnitId = eUnitPhy_Percentage},
    {.u32Number = 95,  .pszName = "Fuel Filter Differential Pressure",.u8StartByte = 2, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 2.0f, .fOffset = 0, .eUnitId = eUnitPhy_KPA},
    {.u32Number = 99,  .pszName = "Engine Oil Filter Differential Pressure",.u8StartByte = 3, .u8StartBit = 0, .u8LengthBits = 8, .fScaling = 0.5f, .fOffset = 0, .eUnitId = eUnitPhy_KPA},
    {.u32Number = 169, .pszName = "Cargo Ambient Temperature",        .u8StartByte = 4, .u8StartBit = 0, .u8LengthBits = 16, .fScaling = 0.03125f, .fOffset = -273.0f, .eUnitId = eUnitPhy_CELSIUS},
};


// --- ARREGLO PRINCIPAL DE PGNs (Nuestra Base de Datos) ---
const J1939_PGN_t g_asPgnDatabase[] = {
    {.u32Number = 65265, .pszName = "Cruise Control/Vehicle Speed", .u8Priority = 6, .pasSPNs = g_asSpnsPGN65265, .u8NumSpns = sizeof(g_asSpnsPGN65265) / sizeof(J1939_SPN_t)},
    {.u32Number = 61441, .pszName = "Electronic Brake Controller 1",.u8Priority = 6, .pasSPNs = g_asSpnsPGN61441, .u8NumSpns = sizeof(g_asSpnsPGN61441) / sizeof(J1939_SPN_t)},
    {.u32Number = 57344, .pszName = "Cab Message 1",                .u8Priority = 6, .pasSPNs = g_asSpnsPGN57344, .u8NumSpns = sizeof(g_asSpnsPGN57344) / sizeof(J1939_SPN_t)},
    {.u32Number = 61444, .pszName = "Electronic Engine Controller 1", .u8Priority = 3, .pasSPNs = g_asSpnsPGN61444, .u8NumSpns = sizeof(g_asSpnsPGN61444) / sizeof(J1939_SPN_t)},
    {.u32Number = 65262, .pszName = "Engine Temperature 1",         .u8Priority = 6, .pasSPNs = g_asSpnsPGN65262, .u8NumSpns = sizeof(g_asSpnsPGN65262) / sizeof(J1939_SPN_t)},
    {.u32Number = 65263, .pszName = "Engine Fluid Level/Pressure 1",.u8Priority = 6, .pasSPNs = g_asSpnsPGN65263, .u8NumSpns = sizeof(g_asSpnsPGN65263) / sizeof(J1939_SPN_t)},
    {.u32Number = 65270, .pszName = "Inlet/Exhaust Conditions 1",     .u8Priority = 6, .pasSPNs = g_asSpnsPGN65270, .u8NumSpns = sizeof(g_asSpnsPGN65270) / sizeof(J1939_SPN_t)},
    {.u32Number = 65253, .pszName = "Engine Hours, Revolutions",      .u8Priority = 6, .pasSPNs = g_asSpnsPGN65253, .u8NumSpns = sizeof(g_asSpnsPGN65253) / sizeof(J1939_SPN_t)},
    {.u32Number = 65257, .pszName = "Fuel Consumption (Liquid)",      .u8Priority = 6, .pasSPNs = g_asSpnsPGN65257, .u8NumSpns = sizeof(g_asSpnsPGN65257) / sizeof(J1939_SPN_t)},
    {.u32Number = 65266, .pszName = "Fuel Economy (Liquid)",          .u8Priority = 6, .pasSPNs = g_asSpnsPGN65266, .u8NumSpns = sizeof(g_asSpnsPGN65266) / sizeof(J1939_SPN_t)},
    {.u32Number = 65271, .pszName = "Vehicle Electrical Power",       .u8Priority = 6, .pasSPNs = g_asSpnsPGN65271, .u8NumSpns = sizeof(g_asSpnsPGN65271) / sizeof(J1939_SPN_t)},
    {.u32Number = 65276, .pszName = "Dash Display",                   .u8Priority = 6, .pasSPNs = g_asSpnsPGN65276, .u8NumSpns = sizeof(g_asSpnsPGN65276) / sizeof(J1939_SPN_t)},
};

// Variable global para el tamaño de la base de datos
const size_t G_SZ_PGN_DATABASE_SIZE = sizeof(g_asPgnDatabase) / sizeof(J1939_PGN_t);

/* Variables ------------------------------------------------------------------*/

/* Local Function prototypes -----------------------------------------------*/

/* Functions -----------------------------------------------------------------*/

