#include <stdio.h>
#include <string.h>
#include <time.h>
#include "writer.h"
#include <unistd.h>
#include "PeriodicWrite.h"

// #define ONESECOND 999999
// #define ONEHOUR 999999*60*60

// typedef struct tm tm;

// void UpdateRealClock(tm ** info){
//   time_t c;
//   time(&c);
//   *info = localtime(&c);
// }

// void WritePeriodically(int period, tm * info, float obj_temp,
// 		                              float sink_temp,
// 		                              float target_temp,
// 		                              float baseplate_temp,
// 		                              float out_current,
// 		                              float out_voltage,
// 		                              float in_voltage,
// 		                              long error,
// 		                              long temp_stable
// 		                                               )
// {
   
// 	    UpdateRealClock(&info);
// 	    int seconds = info -> tm_sec;

// 	     Wait until the next multiple of <period> seconds 
// 	    if ((seconds % period) != 0)
// 	        usleep((period - (seconds % period))*ONESECOND);
// 	    WriteToCSV(QueryString(obj_temp,
// 				   sink_temp,
// 				   target_temp,
// 				   baseplate_temp,
// 				   out_current,
// 				   out_voltage,
// 				   in_voltage,
// 				   error,
// 				   temp_stable));
// 	    printf("Writing at %s", asctime(info));
// 	    /* Wait another <period> seconds*/
// 	    usleep(period*ONESECOND);

// }

// void WriteEveryFewHours(int period, tm* info, uint32_t* long_vals, float* float_vals)
// {
// 	UpdateRealClock(&info);
// 	int seconds = info -> tm_sec;
// 	if ((seconds % period) != 0)
//             usleep((period - (seconds%period))*ONESECOND + ONESECOND);
//     WriteToParamCSV(ParamString(long_vals, float_vals));
//     printf("Writing the Parameters at %s", asctime(info));
//     usleep(period*ONESECOND);
// }