#include "tec.h"
#include "reply.h"
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

#include "TEC/ComPort/ComPort.h"
#include "TEC/MeComAPI/MeCom.h"

int tec_set_float_val(float val, int param_id, int channel);
int tec_set_int_val(float val, int param_id, int channel);


/* Temperature range macros are defined in temperature.h */
bool temp_in_range(float temp)
{
	return temp <= MAX_TEMP && temp >= MIN_TEMP;
}

/* Reset the device. */
bool tec_reset_device(int address)
{
   ComPort_Open(COMPORT_NUMBER, COMPORT_BAUD_RATE);
   bool rv = MeCom_ResetDevice(address);
   ComPort_Close();
   return rv;
}

/* Set a float value . */
int tec_set_float_val(float new_val, int param_id, int channel)
{

    ComPort_Open(COMPORT_NUMBER,COMPORT_BAUD_RATE);
    MeParFloatFields Fields;

    /* Read the target temperature of the TEC before modifying it. 
       This function writes to the float field of the FIELDS struct. */
    MeCom_ParValuef(ADDRESS, param_id, channel, &Fields, MeGet);
    float initial_val = Fields.Value;

	/* Set the target temperature to the new value. */
	Fields.Value = new_val; 
    MeCom_ParValuef(ADDRESS,param_id,channel,&Fields, MeSet);


    /* Read the target temperature again to verify modify success. */
    MeCom_ParValuef(ADDRESS, param_id,channel, &Fields, MeGet);
    
    ComPort_Close();
    /* Return the appropriate value. */
    return Fields.Value == new_val;
}


/* Set an integer value  */
int tec_set_int_val(int new_val, int param_id, int channel)
{

    ComPort_Open(COMPORT_NUMBER,COMPORT_BAUD_RATE);
    MeParLongFields Fields;

    /* Read the target temperature of the TEC before modifying it. 
       This function writes to the float field of the FIELDS struct. */
    MeCom_ParValuel(ADDRESS, param_id, channel, &Fields, MeGet);
    int initial_val = Fields.Value;

	/* Set the target temperature to the new value. */
	Fields.Value = new_val; 
    MeCom_ParValuel(ADDRESS,param_id,channel,&Fields, MeSet);


    /* Read the target temperature again to verify modify success. */
    MeCom_ParValuel(ADDRESS, param_id,channel, &Fields, MeGet);
    

    ComPort_Close();
    /* Return the appropriate value. */
    return Fields.Value == new_val;
}


/* Read an integer value */
int tec_get_int_val(int param_id, int channel)
{
	ComPort_Open(COMPORT_NUMBER,COMPORT_BAUD_RATE);
         
	MeParLongFields Fields;
	MeCom_ParValuel(ADDRESS, param_id, channel, &Fields, MeGet);
	ComPort_Close();
	return Fields.Value;
}



/* Read a float value */
float tec_get_float_val(int param_id, int channel)
{
	ComPort_Open(COMPORT_NUMBER,COMPORT_BAUD_RATE);
	MeParFloatFields Fields;
	MeCom_ParValuef(ADDRESS, param_id, channel, &Fields, MeGet);
	ComPort_Close();
	return Fields.Value;
}
