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
    {.u32Number = 69,   .pszName = "Two Speed Axle Switch",                      .eLocalId = SPN_Two_Speed_Axle_Switch,                      .u8StartByte = 0, .u8StartBit = 0, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 70,   .pszName = "Parking Brake Switch",                     .eLocalId = SPN_Parking_Brake_Switch,                     .u8StartByte = 0, .u8StartBit = 2, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1633, .pszName = "Cruise Control Pause Switch",              .eLocalId = SPN_Cruise_Control_Pause_Switch,              .u8StartByte = 0, .u8StartBit = 4, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 84,   .pszName = "Wheel-Based Vehicle Speed",                .eLocalId = SPN_Wheel_Based_Vehicle_Speed,                .u8StartByte = 1, .u8StartBit = 0, .u8LengthBits = 16, .fScaling = 0.00390625f, .fOffset = 0, .eUnitId = eUnitPhy_KMH},
    {.u32Number = 595,  .pszName = "Cruise Control Active",                    .eLocalId = SPN_Cruise_Control_Active,                    .u8StartByte = 3, .u8StartBit = 0, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 596,  .pszName = "Cruise Control Enable Switch",             .eLocalId = SPN_Cruise_Control_Enable_Switch,             .u8StartByte = 3, .u8StartBit = 2, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 597,  .pszName = "Brake Switch",                             .eLocalId = SPN_Brake_Switch,                             .u8StartByte = 3, .u8StartBit = 4, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 598,  .pszName = "Clutch Switch",                            .eLocalId = SPN_Clutch_Switch,                            .u8StartByte = 3, .u8StartBit = 6, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 599,  .pszName = "Cruise Control Set Switch",                .eLocalId = SPN_Cruise_Control_Set_Switch,                .u8StartByte = 4, .u8StartBit = 0, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 600,  .pszName = "Cruise Control Coast (Decelerate) Switch", .eLocalId = SPN_Cruise_Control_Coast_Decelerate_Switch, .u8StartByte = 4, .u8StartBit = 2, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 601,  .pszName = "Cruise Control Resume Switch",             .eLocalId = SPN_Cruise_Control_Resume_Switch,             .u8StartByte = 4, .u8StartBit = 4, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 602,  .pszName = "Cruise Control Accelerate Switch",         .eLocalId = SPN_Cruise_Control_Accelerate_Switch,         .u8StartByte = 4, .u8StartBit = 6, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 86,   .pszName = "Cruise Control Set Speed",                 .eLocalId = SPN_Cruise_Control_Set_Speed,                 .u8StartByte = 5, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_KMH},
    {.u32Number = 976,  .pszName = "PTO State",                                .eLocalId = SPN_PTO_State,                                .u8StartByte = 6, .u8StartBit = 0, .u8LengthBits = 5,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 527,  .pszName = "Cruise Control States",                    .eLocalId = SPN_Cruise_Control_States,                    .u8StartByte = 6, .u8StartBit = 5, .u8LengthBits = 3,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 968,  .pszName = "Idle Increment Switch",                    .eLocalId = SPN_Idle_Increment_Switch,                    .u8StartByte = 7, .u8StartBit = 0, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 967,  .pszName = "Idle Decrement Switch",                    .eLocalId = SPN_Idle_Decrement_Switch,                    .u8StartByte = 7, .u8StartBit = 2, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 966,  .pszName = "Engine Test Mode Switch",                  .eLocalId = SPN_Engine_Test_Mode_Switch,                  .u8StartByte = 7, .u8StartBit = 4, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1237, .pszName = "Engine Shutdown Override Switch",          .eLocalId = SPN_Engine_Shutdown_Override_Switch,          .u8StartByte = 7, .u8StartBit = 6, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
};

// --- SPNs para PGN 61441 (Electronic Brake Controller 1 - EBC1) ---
const J1939_SPN_t g_asSpnsPGN61441[] = {
    {.u32Number = 561,  .pszName = "ASR Engine Control Active",                .eLocalId = SPN_ASR_Engine_Control_Active,                .u8StartByte = 0, .u8StartBit = 0, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 562,  .pszName = "ASR Brake Control Active",                 .eLocalId = SPN_ASR_Brake_Control_Active,                 .u8StartByte = 0, .u8StartBit = 2, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 563,  .pszName = "Anti-Lock Braking (ABS) Active",           .eLocalId = SPN_Anti_Lock_Braking_ABS_Active,           .u8StartByte = 0, .u8StartBit = 4, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1121, .pszName = "EBS Brake Switch",                         .eLocalId = SPN_EBS_Brake_Switch,                         .u8StartByte = 0, .u8StartBit = 6, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 521,  .pszName = "Brake Pedal Position",                     .eLocalId = SPN_Brake_Pedal_Position,                     .u8StartByte = 1, .u8StartBit = 0, .u8LengthBits = 8, .fScaling = 0.4f, .fOffset = 0, .eUnitId = eUnitPhy_Percentage},
    {.u32Number = 575,  .pszName = "ABS Off-road Switch",                      .eLocalId = SPN_ABS_Off_road_Switch,                      .u8StartByte = 2, .u8StartBit = 0, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 576,  .pszName = "ASR Off-road Switch",                      .eLocalId = SPN_ASR_Off_road_Switch,                      .u8StartByte = 2, .u8StartBit = 2, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 577,  .pszName = "ASR 'Hill Holder' Switch",                 .eLocalId = SPN_ASR_Hill_Holder_Switch,                 .u8StartByte = 2, .u8StartBit = 4, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1238, .pszName = "Traction Control Override Switch",         .eLocalId = SPN_Traction_Control_Override_Switch,         .u8StartByte = 2, .u8StartBit = 6, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 972,  .pszName = "Accelerator Interlock Switch",             .eLocalId = SPN_Accelerator_Interlock_Switch,             .u8StartByte = 3, .u8StartBit = 0, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 971,  .pszName = "Engine Derate Switch",                     .eLocalId = SPN_Engine_Derate_Switch,                     .u8StartByte = 3, .u8StartBit = 2, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 970,  .pszName = "Auxiliary Engine Shutdown Switch",         .eLocalId = SPN_Auxiliary_Engine_Shutdown_Switch,         .u8StartByte = 3, .u8StartBit = 4, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 969,  .pszName = "Remote Accelerator Enable Switch",         .eLocalId = SPN_Remote_Accelerator_Enable_Switch,         .u8StartByte = 3, .u8StartBit = 6, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 973,  .pszName = "Engine Retarder Selection",                .eLocalId = SPN_Engine_Retarder_Selection,                .u8StartByte = 4, .u8StartBit = 0, .u8LengthBits = 8, .fScaling = 0.4f, .fOffset = 0, .eUnitId = eUnitPhy_Percentage},
    {.u32Number = 1243, .pszName = "ABS Fully Operational",                    .eLocalId = SPN_ABS_Fully_Operational,                    .u8StartByte = 5, .u8StartBit = 0, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1439, .pszName = "EBS Red Warning Signal",                   .eLocalId = SPN_EBS_Red_Warning_Signal,                   .u8StartByte = 5, .u8StartBit = 2, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1438, .pszName = "ABS/EBS Amber Warning Signal",             .eLocalId = SPN_ABS_EBS_Amber_Warning_Signal,             .u8StartByte = 5, .u8StartBit = 4, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1793, .pszName = "ATC/ASR Information Signal",               .eLocalId = SPN_ATC_ASR_Information_Signal,               .u8StartByte = 5, .u8StartBit = 6, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1481, .pszName = "Source Address of Controlling Device for Brake Control", .eLocalId = SPN_Source_Address_of_Controlling_Device_for_Brake_Control, .u8StartByte = 6, .u8StartBit = 0, .u8LengthBits = 8, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1836, .pszName = "Trailer ABS Status",                       .eLocalId = SPN_Trailer_ABS_Status,                       .u8StartByte = 7, .u8StartBit = 4, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1792, .pszName = "Tractor-Mounted Trailer ABS Warning Signal", .eLocalId = SPN_Tractor_Mounted_Trailer_ABS_Warning_Signal, .u8StartByte = 7, .u8StartBit = 6, .u8LengthBits = 2, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
};

// --- SPNs para PGN 57344 (Cab Message 1 - CM1) ---
const J1939_SPN_t g_asSpnsPGN57344[] = {
    {.u32Number = 986,  .pszName = "Requested Percent Fan Speed",                .eLocalId = SPN_Requested_Percent_Fan_Speed,                .u8StartByte = 0, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 0.4f, .fOffset = 0, .eUnitId = eUnitPhy_Percentage},
    {.u32Number = 1691, .pszName = "Cab Interior Temperature Command",           .eLocalId = SPN_Cab_Interior_Temperature_Command,           .u8StartByte = 1, .u8StartBit = 0, .u8LengthBits = 16, .fScaling = 0.03125f, .fOffset = -273.0f, .eUnitId = eUnitPhy_CELSIUS},
    {.u32Number = 1684, .pszName = "Auxiliary Heater Coolant Pump Request",      .eLocalId = SPN_Auxiliary_Heater_Coolant_Pump_Request,      .u8StartByte = 3, .u8StartBit = 0, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1682, .pszName = "Battery Main Switch Hold Request",           .eLocalId = SPN_Battery_Main_Switch_Hold_Request,           .u8StartByte = 3, .u8StartBit = 2, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1714, .pszName = "Operator Seat Direction Switch",             .eLocalId = SPN_Operator_Seat_Direction_Switch,             .u8StartByte = 3, .u8StartBit = 4, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1856, .pszName = "Seat Belt Switch",                           .eLocalId = SPN_Seat_Belt_Switch,                           .u8StartByte = 3, .u8StartBit = 6, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1655, .pszName = "Vehicle Limiting Speed Governor Decrement Switch", .eLocalId = SPN_Vehicle_Limiting_Speed_Governor_Decrement_Switch, .u8StartByte = 4, .u8StartBit = 2, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1654, .pszName = "Vehicle Limiting Speed Governor Increment Switch", .eLocalId = SPN_Vehicle_Limiting_Speed_Governor_Increment_Switch, .u8StartByte = 4, .u8StartBit = 4, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1653, .pszName = "Vehicle Limiting Speed Governor Enable Switch",  .eLocalId = SPN_Vehicle_Limiting_Speed_Governor_Enable_Switch,  .u8StartByte = 4, .u8StartBit = 6, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1666, .pszName = "Automatic Gear Shifting Enable Switch",      .eLocalId = SPN_Automatic_Gear_Shifting_Enable_Switch,      .u8StartByte = 5, .u8StartBit = 4, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1656, .pszName = "Engine Automatic Start Enable Switch",       .eLocalId = SPN_Engine_Automatic_Start_Enable_Switch,       .u8StartByte = 5, .u8StartBit = 6, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1683, .pszName = "Auxiliary Heater Mode Request",              .eLocalId = SPN_Auxiliary_Heater_Mode_Request,              .u8StartByte = 6, .u8StartBit = 0, .u8LengthBits = 4,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1685, .pszName = "Request Engine Zone Heating",                .eLocalId = SPN_Request_Engine_Zone_Heating,                .u8StartByte = 6, .u8StartBit = 4, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1686, .pszName = "Request Cab Zone Heating",                   .eLocalId = SPN_Request_Cab_Zone_Heating,                   .u8StartByte = 6, .u8StartBit = 6, .u8LengthBits = 2,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 2596, .pszName = "Selected Maximum Vehicle Speed Limit",       .eLocalId = SPN_Selected_Maximum_Vehicle_Speed_Limit,       .u8StartByte = 7, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
};

// --- SPNs para PGN 61444 (Electronic Engine Controller 1 - EEC1) ---
const J1939_SPN_t g_asSpnsPGN61444[] = {
    {.u32Number = 899,  .pszName = "Engine Torque Mode",                             .eLocalId = SPN_Engine_Torque_Mode,                             .u8StartByte = 0, .u8StartBit = 0, .u8LengthBits = 4,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 512,  .pszName = "Driver's Demand Engine - Percent Torque",      .eLocalId = SPN_Drivers_Demand_Engine_Percent_Torque,      .u8StartByte = 1, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 1.0f, .fOffset = -125.0f, .eUnitId = eUnitPhy_Percentage},
    {.u32Number = 513,  .pszName = "Actual Engine - Percent Torque",               .eLocalId = SPN_Actual_Engine_Percent_Torque,               .u8StartByte = 2, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 1.0f, .fOffset = -125.0f, .eUnitId = eUnitPhy_Percentage},
    {.u32Number = 190,  .pszName = "Engine Speed",                                   .eLocalId = SPN_Engine_Speed,                                   .u8StartByte = 3, .u8StartBit = 0, .u8LengthBits = 16, .fScaling = 0.125f, .fOffset = 0, .eUnitId = eUnitPhy_RPM},
    {.u32Number = 1483, .pszName = "Source Address of Controlling Device for Engine Control", .eLocalId = SPN_Source_Address_of_Controlling_Device_for_Engine_Control, .u8StartByte = 5, .u8StartBit = 0, .u8LengthBits = 8, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 1675, .pszName = "Engine Starter Mode",                            .eLocalId = SPN_Engine_Starter_Mode,                            .u8StartByte = 6, .u8StartBit = 0, .u8LengthBits = 4, .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_Binary},
    {.u32Number = 2432, .pszName = "Engine Demand - Percent Torque",               .eLocalId = SPN_Engine_Demand_Percent_Torque,               .u8StartByte = 7, .u8StartBit = 0, .u8LengthBits = 8, .fScaling = 1.0f, .fOffset = -125.0f, .eUnitId = eUnitPhy_Percentage},
};

// --- SPNs para PGN 65262 (Engine Temperature 1 - ET1) ---
const J1939_SPN_t g_asSpnsPGN65262[] = {
    {.u32Number = 110,  .pszName = "Engine Coolant Temperature",              .eLocalId = SPN_Engine_Coolant_Temperature,              .u8StartByte = 0, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 1.0f, .fOffset = -40.0f, .eUnitId = eUnitPhy_CELSIUS},
    {.u32Number = 174,  .pszName = "Fuel Temperature",                        .eLocalId = SPN_Fuel_Temperature,                        .u8StartByte = 1, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 1.0f, .fOffset = -40.0f, .eUnitId = eUnitPhy_CELSIUS},
    {.u32Number = 175,  .pszName = "Engine Oil Temperature 1",                .eLocalId = SPN_Engine_Oil_Temperature_1,                .u8StartByte = 2, .u8StartBit = 0, .u8LengthBits = 16, .fScaling = 0.03125f, .fOffset = -273.0f, .eUnitId = eUnitPhy_CELSIUS},
    {.u32Number = 176,  .pszName = "Turbo Oil Temperature",                   .eLocalId = SPN_Turbo_Oil_Temperature,                   .u8StartByte = 4, .u8StartBit = 0, .u8LengthBits = 16, .fScaling = 0.03125f, .fOffset = -273.0f, .eUnitId = eUnitPhy_CELSIUS},
    {.u32Number = 52,   .pszName = "Engine Intercooler Temperature",          .eLocalId = SPN_Engine_Intercooler_Temperature,          .u8StartByte = 6, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 1.0f, .fOffset = -40.0f, .eUnitId = eUnitPhy_CELSIUS},
    {.u32Number = 1134, .pszName = "Engine Intercooler Thermostat Opening",   .eLocalId = SPN_Engine_Intercooler_Thermostat_Opening,   .u8StartByte = 7, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 0.4f, .fOffset = 0, .eUnitId = eUnitPhy_Percentage},
};

// --- SPNs para PGN 65263 (Engine Fluid Level/Pressure 1 - EFL/P1) ---
const J1939_SPN_t g_asSpnsPGN65263[] = {
    {.u32Number = 94,   .pszName = "Fuel Delivery Pressure",                .eLocalId = SPN_Fuel_Delivery_Pressure,                .u8StartByte = 0, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 4.0f, .fOffset = 0, .eUnitId = eUnitPhy_KPA},
    {.u32Number = 22,   .pszName = "Extended Crankcase Blow-by Pressure",   .eLocalId = SPN_Extended_Crankcase_Blow_by_Pressure,   .u8StartByte = 1, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 0.05f, .fOffset = 0, .eUnitId = eUnitPhy_KPA},
    {.u32Number = 98,   .pszName = "Engine Oil Level",                      .eLocalId = SPN_Engine_Oil_Level,                      .u8StartByte = 2, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 0.4f, .fOffset = 0, .eUnitId = eUnitPhy_Percentage},
    {.u32Number = 100,  .pszName = "Engine Oil Pressure",                   .eLocalId = SPN_Engine_Oil_Pressure,                   .u8StartByte = 3, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 4.0f, .fOffset = 0, .eUnitId = eUnitPhy_KPA},
    {.u32Number = 101,  .pszName = "Crankcase Pressure",                    .eLocalId = SPN_Crankcase_Pressure,                    .u8StartByte = 4, .u8StartBit = 0, .u8LengthBits = 16, .fScaling = 0.0078125f, .fOffset = -250.0f, .eUnitId = eUnitPhy_KPA},
    {.u32Number = 109,  .pszName = "Coolant Pressure",                      .eLocalId = SPN_Coolant_Pressure,                      .u8StartByte = 6, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 2.0f, .fOffset = 0, .eUnitId = eUnitPhy_KPA},
    {.u32Number = 111,  .pszName = "Coolant Level",                         .eLocalId = SPN_Coolant_Level,                         .u8StartByte = 7, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 0.4f, .fOffset = 0, .eUnitId = eUnitPhy_Percentage},
};

// --- SPNs para PGN 65270 (Inlet/Exhaust Conditions 1 - IC1) ---
const J1939_SPN_t g_asSpnsPGN65270[] = {
    {.u32Number = 81,   .pszName = "Particulate Trap Inlet Pressure",      .eLocalId = SPN_Particulate_Trap_Inlet_Pressure,      .u8StartByte = 0, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 0.5f, .fOffset = 0, .eUnitId = eUnitPhy_KPA},
    {.u32Number = 102,  .pszName = "Boost Pressure",                       .eLocalId = SPN_Boost_Pressure,                       .u8StartByte = 1, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 2.0f, .fOffset = 0, .eUnitId = eUnitPhy_KPA},
    {.u32Number = 105,  .pszName = "Intake Manifold 1 Temperature",        .eLocalId = SPN_Intake_Manifold_1_Temperature,        .u8StartByte = 2, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 1.0f, .fOffset = -40.0f, .eUnitId = eUnitPhy_CELSIUS},
    {.u32Number = 106,  .pszName = "Air Inlet Pressure",                   .eLocalId = SPN_Air_Inlet_Pressure,                   .u8StartByte = 3, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 2.0f, .fOffset = 0, .eUnitId = eUnitPhy_KPA},
    {.u32Number = 107,  .pszName = "Air Filter 1 Differential Pressure",   .eLocalId = SPN_Air_Filter_1_Differential_Pressure,   .u8StartByte = 4, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 0.05f, .fOffset = 0, .eUnitId = eUnitPhy_KPA},
    {.u32Number = 173,  .pszName = "Exhaust Gas Temperature",              .eLocalId = SPN_Exhaust_Gas_Temperature,              .u8StartByte = 5, .u8StartBit = 0, .u8LengthBits = 16, .fScaling = 0.03125f, .fOffset = -273.0f, .eUnitId = eUnitPhy_CELSIUS},
    {.u32Number = 112,  .pszName = "Coolant Filter Differential Pressure", .eLocalId = SPN_Coolant_Filter_Differential_Pressure, .u8StartByte = 7, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 0.5f, .fOffset = 0, .eUnitId = eUnitPhy_KPA},
};

// --- SPNs para PGN 65253 (Engine Hours, Revolutions - HOURS) ---
const J1939_SPN_t g_asSpnsPGN65253[] = {
    {.u32Number = 247, .pszName = "Total Engine Hours",       .eLocalId = SPN_Total_Engine_Hours,       .u8StartByte = 0, .u8StartBit = 0, .u8LengthBits = 32, .fScaling = 0.05f, .fOffset = 0, .eUnitId = eUnitPhy_HOUR},
    {.u32Number = 249, .pszName = "Total Engine Revolutions", .eLocalId = SPN_Total_Engine_Revolutions, .u8StartByte = 4, .u8StartBit = 0, .u8LengthBits = 32, .fScaling = 1000.0f, .fOffset = 0, .eUnitId = eUnitPhy_RPM},
};

// --- SPNs para PGN 65257 (Fuel Consumption (Liquid) - LFC) ---
const J1939_SPN_t g_asSpnsPGN65257[] = {
    {.u32Number = 182, .pszName = "Trip Fuel",       .eLocalId = SPN_Trip_Fuel,       .u8StartByte = 0, .u8StartBit = 0, .u8LengthBits = 32, .fScaling = 0.5f, .fOffset = 0, .eUnitId = eUnitPhy_LITER},
    {.u32Number = 250, .pszName = "Total Fuel Used", .eLocalId = SPN_Total_Fuel_Used, .u8StartByte = 4, .u8StartBit = 0, .u8LengthBits = 32, .fScaling = 0.5f, .fOffset = 0, .eUnitId = eUnitPhy_LITER},
};

// --- SPNs para PGN 65266 (Fuel Economy (Liquid) - LFE) ---
const J1939_SPN_t g_asSpnsPGN65266[] = {
    {.u32Number = 183, .pszName = "Fuel Rate",                  .eLocalId = SPN_Fuel_Rate,                  .u8StartByte = 0, .u8StartBit = 0, .u8LengthBits = 16, .fScaling = 0.05f, .fOffset = 0, .eUnitId = eUnitPhy_LITER_PER_HOUR},
    {.u32Number = 184, .pszName = "Instantaneous Fuel Economy", .eLocalId = SPN_Instantaneous_Fuel_Economy, .u8StartByte = 2, .u8StartBit = 0, .u8LengthBits = 16, .fScaling = 0.001953125f, .fOffset = 0, .eUnitId = eUnitPhy_KM_PER_LITER},
    {.u32Number = 185, .pszName = "Average Fuel Economy",       .eLocalId = SPN_Average_Fuel_Economy,       .u8StartByte = 4, .u8StartBit = 0, .u8LengthBits = 16, .fScaling = 0.001953125f, .fOffset = 0, .eUnitId = eUnitPhy_KM_PER_LITER},
    {.u32Number = 51,  .pszName = "Throttle Position",          .eLocalId = SPN_Throttle_Position,          .u8StartByte = 6, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 0.4f, .fOffset = 0, .eUnitId = eUnitPhy_Percentage},
};

// --- SPNs para PGN 65271 (Vehicle Electrical Power - VEP) ---
const J1939_SPN_t g_asSpnsPGN65271[] = {
    {.u32Number = 114, .pszName = "Net Battery Current",               .eLocalId = SPN_Net_Battery_Current,               .u8StartByte = 0, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 1.0f, .fOffset = -125.0f, .eUnitId = eUnitPhy_AMPERE},
    {.u32Number = 115, .pszName = "Alternator Current",                .eLocalId = SPN_Alternator_Current,                .u8StartByte = 1, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 1.0f, .fOffset = 0, .eUnitId = eUnitPhy_AMPERE},
    {.u32Number = 167, .pszName = "Alternator Potential (Voltage)",    .eLocalId = SPN_Alternator_Potential_Voltage,    .u8StartByte = 2, .u8StartBit = 0, .u8LengthBits = 16, .fScaling = 0.05f, .fOffset = 0, .eUnitId = eUnitPhy_VOLT},
    {.u32Number = 168, .pszName = "Electrical Potential (Voltage)",    .eLocalId = SPN_Electrical_Potential_Voltage,    .u8StartByte = 4, .u8StartBit = 0, .u8LengthBits = 16, .fScaling = 0.05f, .fOffset = 0, .eUnitId = eUnitPhy_VOLT},
    {.u32Number = 158, .pszName = "Battery Potential (Voltage), Switched", .eLocalId = SPN_Battery_Potential_Voltage_Switched, .u8StartByte = 6, .u8StartBit = 0, .u8LengthBits = 16, .fScaling = 0.05f, .fOffset = 0, .eUnitId = eUnitPhy_VOLT},
};

// --- SPNs para PGN 65276 (Dash Display - DD) ---
const J1939_SPN_t g_asSpnsPGN65276[] = {
    {.u32Number = 80,  .pszName = "Washer Fluid Level",                  .eLocalId = SPN_Washer_Fluid_Level,                  .u8StartByte = 0, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 0.4f, .fOffset = 0, .eUnitId = eUnitPhy_Percentage},
    {.u32Number = 96,  .pszName = "Fuel Level",                          .eLocalId = SPN_Fuel_Level,                          .u8StartByte = 1, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 0.4f, .fOffset = 0, .eUnitId = eUnitPhy_Percentage},
    {.u32Number = 95,  .pszName = "Fuel Filter Differential Pressure",   .eLocalId = SPN_Fuel_Filter_Differential_Pressure,   .u8StartByte = 2, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 2.0f, .fOffset = 0, .eUnitId = eUnitPhy_KPA},
    {.u32Number = 99,  .pszName = "Engine Oil Filter Differential Pressure", .eLocalId = SPN_Engine_Oil_Filter_Differential_Pressure, .u8StartByte = 3, .u8StartBit = 0, .u8LengthBits = 8,  .fScaling = 0.5f, .fOffset = 0, .eUnitId = eUnitPhy_KPA},
    {.u32Number = 169, .pszName = "Cargo Ambient Temperature",           .eLocalId = SPN_Cargo_Ambient_Temperature,           .u8StartByte = 4, .u8StartBit = 0, .u8LengthBits = 16, .fScaling = 0.03125f, .fOffset = -273.0f, .eUnitId = eUnitPhy_CELSIUS},
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
const size_t G_SPN_DATABAE_SIZE = ENUM_SPN_LOCAL_ID_COUNT;

/* Variables ------------------------------------------------------------------*/

/* Local Function prototypes -----------------------------------------------*/

/* Functions -----------------------------------------------------------------*/

