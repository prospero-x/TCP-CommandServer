#include <stdio.h>
#include <string.h>
#include "ConsoleIO.h"
#include "ComPort/ComPort.h"
#include "MeComAPI/MeCom.h"
#include <unistd.h>


uint16_t* ParamNumLongInit(){
    uint16_t ParamNums[] = {2000, 2010, 2040, 2051, 2050, 2052, 3020, 3034, 5030, 
        6000, 6001, 6005, 6020, 6021, 6022, 6023, 6100, 6200, 6210, 6225, 6230, 6300, 
        6310, 6320, 50000, 50010, 50011, 51000, 51001, 51002, 52000, 52001, 
        52002, 52003, 52010, 52012, 52100, 52101, 52102};
    uint16_t* rv = (uint16_t*)malloc(sizeof(uint16_t)*41);
    int i;
    for (i = 0; i < 39; i++){
        rv[i] = ParamNums[i];
    }
    return rv;

}

uint16_t* ParamNumFloatInit(){
    uint16_t* rv = (uint16_t*)malloc(sizeof(uint16_t)*90);
    uint16_t ParamNums[] = {2020, 2021, 2030, 2031, 2032, 2033, 2060, 3000, 3003, 
       3002, 3010, 3011, 3012, 3013, 3030, 3031, 3032, 3033, 3040, 3041, 4001, 4002, 
       4010, 4011, 4012, 4020, 4021, 4022, 4023, 4024, 4025, 4040, 4041, 4042, 5001, 5002, 5010, 5011, 5012, 5020, 5021, 5022, 5023, 5024, 5025, 5031, 
       6002, 6003, 6004, 6010, 6013, 6011, 6012, 6110, 6111, 6112,
       6211, 6212, 6213, 6214, 6220, 6221, 6222, 6223, 6224, 50001, 50002, 52200};
    int i;
    for (i = 0; i < 68; i++){ 
      rv[i] = ParamNums[i];
    }
    return rv;
}



uint32_t* ParamValLongInit(){
    uint32_t* rv = (uint32_t*)malloc(sizeof(uint32_t)*39);
    return rv;

}

float* ParamValFloatInit(){
    float* rv = (float*)malloc(sizeof(float)*68);
    return rv;
}

void ParameterSweepLong(uint8_t Address, uint16_t* param_nums, uint32_t* param_vals)
{
    MeParLongFields  Fields;
    int i;
    for (i = 0; i < 39; i++){
        MeCom_ParValuel(Address,param_nums[i], 1, &Fields, MeGet);
        param_vals[i] = Fields.Value;
    }
      
 }   
void ParameterSweepFloat(uint8_t Address, uint16_t* param_nums, float* param_vals)
{
    MeParFloatFields Fields;
    int i;
    for (i = 0; i < 68; i++){
        MeCom_ParValuef(Address,param_nums[i], 1, &Fields, MeGet);
        param_vals[i] = Fields.Value;
    }
      
 } 
void ParameterSetLong(uint8_t Address, uint16_t* param_nums, uint32_t* param_vals)
{
    MeParLongFields Fields;
    int i;
    
    for (i = 0; i < 39; i++){
        Fields.Value = param_vals[i];
        MeCom_ParValuel(Address,param_nums[i], 1, &Fields, MeSet);

    }
      
 }

void ParameterSetFloat(uint8_t Address, uint16_t* param_nums, float* param_vals)
{
    MeParFloatFields Fields;
    int i;
    
    for (i = 0; i < 68; i++){
        Fields.Value = param_vals[i];
        MeCom_ParValuef(Address,param_nums[i], 1, &Fields, MeSet);      
    }
      
 }
