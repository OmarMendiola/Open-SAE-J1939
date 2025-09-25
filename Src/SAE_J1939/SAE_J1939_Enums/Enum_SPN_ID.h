// ================================================
//  @file      Enum_SPN_ID.h
//  @author    
//  @brief     
//  @version   0.1
//  @date      2025-09-CURRENT_DAY
//
//  @copyright Copyright (c) 2025
// ================================================

#ifndef ENUM_SPN_ID_H_
#define ENUM_SPN_ID_H_

#ifdef __cplusplus
extern "C" {
#endif

/* =================== Types ====================== */
/**
 * @brief Enumeración de identificadores locales para SPNs de J1939.
 *
 * Esta enumeración proporciona un identificador único e incremental para un
 * conjunto de Suspect Parameter Numbers (SPNs) de varios PGNs.
 * Esto facilita el manejo de los parámetros internamente en el software.
 */
typedef enum
{
    SPN_LOCAL_ID_START = 0, // Valor de inicio para que el primer ID real sea 1

    /* --- SPNs de PGN 65265 (Cruise Control/Vehicle Speed 1 - CCVS1) --- */
    SPN_Two_Speed_Axle_Switch,
    SPN_Parking_Brake_Switch,
    SPN_Cruise_Control_Pause_Switch,
    SPN_Wheel_Based_Vehicle_Speed,
    SPN_Cruise_Control_Active,
    SPN_Cruise_Control_Enable_Switch,
    SPN_Brake_Switch,
    SPN_Clutch_Switch,
    SPN_Cruise_Control_Set_Switch,
    SPN_Cruise_Control_Coast_Decelerate_Switch,
    SPN_Cruise_Control_Resume_Switch,
    SPN_Cruise_Control_Accelerate_Switch,
    SPN_Cruise_Control_Set_Speed,
    SPN_PTO_State,
    SPN_Cruise_Control_States,
    SPN_Idle_Increment_Switch,
    SPN_Idle_Decrement_Switch,
    SPN_Engine_Test_Mode_Switch,
    SPN_Engine_Shutdown_Override_Switch,

    /* --- SPNs de PGN 61441 (Electronic Brake Controller 1 - EBC1) --- */
    SPN_ASR_Engine_Control_Active,
    SPN_ASR_Brake_Control_Active,
    SPN_Anti_Lock_Braking_ABS_Active,
    SPN_EBS_Brake_Switch,
    SPN_Brake_Pedal_Position,
    SPN_ABS_Off_road_Switch,
    SPN_ASR_Off_road_Switch,
    SPN_ASR_Hill_Holder_Switch,
    SPN_Traction_Control_Override_Switch,
    SPN_Accelerator_Interlock_Switch,
    SPN_Engine_Derate_Switch,
    SPN_Auxiliary_Engine_Shutdown_Switch,
    SPN_Remote_Accelerator_Enable_Switch,
    SPN_Engine_Retarder_Selection,
    SPN_ABS_Fully_Operational,
    SPN_EBS_Red_Warning_Signal,
    SPN_ABS_EBS_Amber_Warning_Signal,
    SPN_ATC_ASR_Information_Signal,
    SPN_Source_Address_of_Controlling_Device_for_Brake_Control,
    SPN_Trailer_ABS_Status,
    SPN_Tractor_Mounted_Trailer_ABS_Warning_Signal,

    /* --- SPNs de PGN 57344 (Cab Message 1 - CM1) --- */
    SPN_Requested_Percent_Fan_Speed,
    SPN_Cab_Interior_Temperature_Command,
    SPN_Auxiliary_Heater_Coolant_Pump_Request,
    SPN_Battery_Main_Switch_Hold_Request,
    SPN_Operator_Seat_Direction_Switch,
    SPN_Seat_Belt_Switch,
    SPN_Vehicle_Limiting_Speed_Governor_Decrement_Switch,
    SPN_Vehicle_Limiting_Speed_Governor_Increment_Switch,
    SPN_Vehicle_Limiting_Speed_Governor_Enable_Switch,
    SPN_Automatic_Gear_Shifting_Enable_Switch,
    SPN_Engine_Automatic_Start_Enable_Switch,
    SPN_Auxiliary_Heater_Mode_Request,
    SPN_Request_Engine_Zone_Heating,
    SPN_Request_Cab_Zone_Heating,
    SPN_Selected_Maximum_Vehicle_Speed_Limit,

    /* --- SPNs de PGN 61444 (Electronic Engine Controller 1 - EEC1) --- */
    SPN_Engine_Torque_Mode,
    SPN_Drivers_Demand_Engine_Percent_Torque,
    SPN_Actual_Engine_Percent_Torque,
    SPN_Engine_Speed,
    SPN_Source_Address_of_Controlling_Device_for_Engine_Control,
    SPN_Engine_Starter_Mode,
    SPN_Engine_Demand_Percent_Torque,

    /* --- SPNs de PGN 65262 (Engine Temperature 1 - ET1) --- */
    SPN_Engine_Coolant_Temperature,
    SPN_Fuel_Temperature,
    SPN_Engine_Oil_Temperature_1,
    SPN_Turbo_Oil_Temperature,
    SPN_Engine_Intercooler_Temperature,
    SPN_Engine_Intercooler_Thermostat_Opening,

    /* --- SPNs de PGN 65263 (Engine Fluid Level/Pressure 1 - EFL/P1) --- */
    SPN_Fuel_Delivery_Pressure,
    SPN_Extended_Crankcase_Blow_by_Pressure,
    SPN_Engine_Oil_Level,
    SPN_Engine_Oil_Pressure,
    SPN_Crankcase_Pressure,
    SPN_Coolant_Pressure,
    SPN_Coolant_Level,

    /* --- SPNs de PGN 65270 (Inlet/Exhaust Conditions 1 - IC1) --- */
    SPN_Particulate_Trap_Inlet_Pressure,
    SPN_Boost_Pressure,
    SPN_Intake_Manifold_1_Temperature,
    SPN_Air_Inlet_Pressure,
    SPN_Air_Filter_1_Differential_Pressure,
    SPN_Exhaust_Gas_Temperature,
    SPN_Coolant_Filter_Differential_Pressure,

    /* --- SPNs de PGN 65253 (Engine Hours, Revolutions - HOURS) --- */
    SPN_Total_Engine_Hours,
    SPN_Total_Engine_Revolutions,

    /* --- SPNs de PGN 65257 (Fuel Consumption (Liquid) - LFC) --- */
    SPN_Trip_Fuel,
    SPN_Total_Fuel_Used,

    /* --- SPNs de PGN 65266 (Fuel Economy (Liquid) - LFE) --- */
    SPN_Fuel_Rate,
    SPN_Instantaneous_Fuel_Economy,
    SPN_Average_Fuel_Economy,
    SPN_Throttle_Position,

    /* --- SPNs de PGN 65271 (Vehicle Electrical Power - VEP) --- */
    SPN_Net_Battery_Current,
    SPN_Alternator_Current,
    SPN_Alternator_Potential_Voltage,
    SPN_Electrical_Potential_Voltage,
    SPN_Battery_Potential_Voltage_Switched,

    /* --- SPNs de PGN 65276 (Dash Display - DD) --- */
    SPN_Washer_Fluid_Level,
    SPN_Fuel_Level,
    SPN_Fuel_Filter_Differential_Pressure,
    SPN_Engine_Oil_Filter_Differential_Pressure,
    SPN_Cargo_Ambient_Temperature,

    ENUM_SPN_LOCAL_ID_COUNT // Elemento final para saber el número total de IDs
} ENUM_SPN_LOCAL_ID;

#ifdef __cplusplus
}
#endif

#endif // ENUM_SPN_ID_H_