#ifndef TEMP_H
#define TEMP_H

/* Full Parameter State */
#define PARAM_PROGRAM "/root/TEC/Full"
#define GOOD_PARAMS_1 "/root/TEC/LargeParams/GoodState_1.csv"
#define GOOD_PARAMS_2 "/root/TEC/LargeParams/GoodState_2.csv"
#define COMMAND_SIZE 100

#define FULL_PATH_SIZE 100
#define LARGE_PARAM_PATH "/root/TEC/LargeParams/"


/* Temperature */
#define PAR_ID_OBJECT_TEMP               1000
#define PAR_ID_TARGET_TEMP               3000
#define PAR_ID_RAMP_TEMP                 1011
#define PAR_ID_TEMP_PROXIMITY_WIDTH      3002
#define PAR_ID_TEMP_IS_STABLE            1200
#define PAR_ID_COARSE_RAMP_TEMPERATURE   3003
#define PAR_ID_TEMP_MIN_THRESHOLD        4010
#define PAR_ID_TEMP_MAX_THRESHOLD        4011

/* Current */
#define PAR_ID_OUTPUT_CURRENT 	         1020
#define PAR_ID_CURRENT_LIMIT             2030

/* Votlage */
#define PAR_ID_OUTPUT_VOLTAGE 	         1021
#define PAR_ID_VOLTAGE_LIMIT             2031

/* Regulation Modes */
#define PAR_ID_INPUT_SELECTION           2000
#define PAR_ID_OUTPUT_STAGE_ENABLE       2010
#define PAR_ID_REGULATION_MODE           3020


/* PID Algorithm parameters */
#define PAR_ID_PID_KP                    3010
#define PAR_ID_PID_TI                    3011
#define PAR_ID_PID_TD                    3012


/* Device identifiers */
#define ADDRESS 0
#define CHANNEL_ONE 1
#define CHANNEL_TWO 2
#define FULL_TEC_RESET_CHANNEL 3
#define COMPORT_NUMBER 0
#define COMPORT_BAUD_RATE 57600 

#define MIN_TEMP -20
#define MAX_TEMP 40


bool temp_in_range(float temp);

/* Reset the device. */
bool tec_reset_device(int address);

/* Modify values on the TEC */
int tec_set_float_val(float new_val, int param_id, int channel);
int tec_set_int_val(int new_val, int param_id, int channel);

/* Read values from the TEC */
int tec_get_int_val(int param_id, int channel);
float tec_get_float_val(int param_id, int channel);


#endif /* temp.h */
