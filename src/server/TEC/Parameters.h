#ifndef PARAM_H
#define PARAM_H

#include <stdio.h>
#include <string.h>
#include "ConsoleIO.h"
#include "ComPort/ComPort.h"
#include "MeComAPI/MeCom.h"

   
        
uint16_t* ParamNumLongInit();
          
uint16_t* ParamNumFloatInit();
          
uint32_t* ParamValLongInit();

float* ParamValFloatInit();
        
void ParameterSweepLong(uint8_t Address, uint16_t* param_nums, uint32_t* param_vals);

void ParameterSweepFloat(uint8_t Address, uint16_t* param_nums, float* param_vals);

void ParameterSetLong(uint8_t Address, uint16_t* param_nums, uint32_t* param_vals);

void ParameterSetFloat(uint8_t Address, uint16_t* param_nums, float* param_vals);

#endif