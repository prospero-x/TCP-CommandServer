#include <stdint.h>


/* Commands.
    
    NIGHT: UCIRC will start taking pictures. 
 
    DAY:  UCIRC will stop taking pictures. 

    INTERVAL <x>: Time between images is changed to <x> minutes.
                  <x> is an integer. 

    SETTEMP <x>: Thermocontroller is set to regulate temperature to 
                 <x> degrees Celsius. <x> is a float.  

    STATUS: UCIRC will reply with a status word. 
                   
 */
typedef enum {
    NIGHT          = 1,   
    DAY            = 2,
    INTERVAL       = 3,
    TEC_SETTEMP    = 4,
    TEC_SET_ALL    = 5,
    TEC_RESET      = 6,
    STATUS         = 7,
} ucirc_cmd;


/* Command parameters can either be floats 
 * or ints. Either is 4 bytes. */
typedef union {
    int interval;
    float temp;
    char filename[22];
} ucirc_cmd_param;



typedef struct {
    ucirc_cmd cmd;
    ucirc_cmd_param param;
} ucirc_cmd_frame;



typedef struct {
	
    /* IR Camera Information */
    int8_t night;     /* Boolean value: Is UCIRC taking pictures?*/
    int8_t interval;  /* Time (in minutes) between pictures */
  
    /* Ubuntu Information */
    int8_t usage;     /* Percentage usage of the UCIRC microSD card */
    char last_file[22]; /* Last file copied to DP_CPU */

    
    /* Thermocontroller Information: Channel 1 */
    float obj_temp1;
    float sink_temp1;
    float target_temp1;
    float ramp_temp1;
    float model_current1;
    float output_current1;
    float output_voltage1;
    float input_voltage1;
    float bp_temp1;
    int8_t errno1;
    int8_t chan1:1, 
           driv1:3,
           flsh1:1,
           res1:3; /* Unused */
    int8_t inp1:2,
           stat1:2,
           omode1:2,
           gmode1:2;
   
    /* Thermocontroller Information: Channel 2 */
    float obj_temp2;
    float sink_temp2;
    float target_temp2;
    float ramp_temp2;
    float model_current2;
    float output_current2;
    float output_voltage2;
    float input_voltage2;
    float bp_temp2;
    int8_t errno2;
    int8_t chan2:1,
           driv2:3,
           flsh2:1,
           res2:3; /* Unused */
    int8_t inp2:2,
           stat2:2,
           omode2:2,
           gmode2:2;
} ucirc_status_frame;
