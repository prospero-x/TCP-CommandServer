#ifndef WRITER_H
#define WRITER_H

#include <stdio.h>
#include <string.h>
#include "ConsoleIO.h"
#include "ComPort/ComPort.h"
#include "MeComAPI/MeCom.h"
#include "PeriodicWrite.h"
#include "Parameters.h"
#include "writer.h"
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
typedef struct tm tm;

char* QueryString(float obj_temp, float sink_temp, float target_temp,
		  float baseplate_temp, float out_current, float out_voltage,
		  float in_voltage, long error, long temp_stable);

char* ParamString(uint32_t* long_vals, float* float_vals);

void WritetoTestCSV(char* str, char* filename);

char* TestString(float obj_temp, float sink_temp, float target_temp, float out_current, float out_voltage);

void WriteToCSV(char* str, char* filename);

void WriteToParamCSV(char* str, char* filename);


#endif 
