
/*===============================================================================*/
/*                             IMPORT                                            */
/*===============================================================================*/

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
/*===============================================================================*/
/*                             MACROS                                            */
/*===============================================================================*/
#define WAITTIME 60
#define HOURSWAIT 0.00139
#define ONESECOND 999999
#define COMPORT_NUMBER 0
#define BAUD_RATE 57600

/*===============================================================================*/
/*                             GLOBALS                                           */
/*===============================================================================*/

const char* _csv_header = "Month,Day,Year,Hour,Minute,Second,OutputStageInputSelection, OutputStageEnable,"
                          "GeneralOperatingMode, DeviceAddress, RS485CH1BaudRate, RS485CH1ResponseDelay,"
                          "ModelizationMode, PeltierPositiveCurrentIs, SinkTemperatureSelection, ObjMeasPGAGain,"
                          "ObjMeasCurrentSource, ObjMeasSensorTypeSelection, DisplayType, DisplayLineDefText,"
                          "DisplayLineAltText, DisplayLineAltMode, PbcFunction, FanControlEnable,"
                          "FanActualTempSource, FanSpeedBypass, PwmFrequency, MiscActObjectTempSource,"
                          "MiscDelayTillReset, MiscError108Delay, LiveEnable, SineRampStartPoint,"
                          "ObjectTargetTempSourceSelection, AtmAutoTuningStart, AtmAutoTuningCancel," 
                          " AtmThermalModelSpeed, LutTableStart, LutTableStop, LutTableStatus, LutCurrentTableLine,"
                          " LutTableIDSelection, LutNrOfRepetitions, PbcEnableFunction, PbcSetOutputToPushPull," 
                          " PbcSetOutputStates, Ope_SetStaticCurrent, Ope_SetStaticVoltage, Ope_CurrentLimitation,"
                          " Ope_VoltageLimitation, Ope_CurrentErrorThreshold, Ope_VoltageErrorThreshold,"
                          " Ope_ComWatchDogTimeout, Tem_TargetObjectTemp, Tem_CoarseTempRamp, Tem_ProximityWidth,"
                          " Tem_Kp, Tem_Ti, Tem_Td, Tem_DPartDampPT1, Tem_PeltierMaxCurrent, Tem_PeltierMaxVoltage," 
                          " Tem_PeltierCoolingCapacity, Tem_PeltierDeltaTemperature, Tem_ResistorResistance,"
                          " Tem_ResistorMaxCurrent, Obj_TemperatureOffset, Obj_TemperatureGain, Obj_LowerErrorThreshold," 
                          " Obj_UpperErrorThreshold, Obj_MaxTempChange, Obj_NTCLowerPointTemperature,"
                          " Obj_NTCLowerPointResistance, Obj_NTCMiddlePointTemperature, Obj_NTCMiddlePointResistance,"
                          " Obj_NTCUpperPointTemperature, Obj_NTCUpperPointResistance, Obj_StabilityTemperatureWindow,"
                          " Obj_StabilityMinTimeInWindow, Obj_StabilityMaxStabiTime, Sin_TemperatureOffset,"
                          " Sin_TemperatureGain, Sin_LowerErrorThreshold, Sin_UpperErrorThreshold, Sin_MaxTempChange,"
                          " Sin_NTCLowerPointTemperature, Sin_NTCLowerPointResistance, Sin_NTCMiddlePointTemperature,"
                          " Sin_NTCMiddlePointResistance, Sin_NTCUpperPointTemperature, Sin_NTCUpperPointResistance,"
                          " Sin_FixedTemperature, Exp_ObjMeasADCRs, Exp_ObjMeasADCCalibOffset, Exp_ObjMeasADCCalibGain,"
                          " Exp_SinMeasADCRv, Exp_SinMeasADCVps, Exp_SinMeasADCCalibOffset, Exp_SinMeasADCCalibGain,"
                          " Exp_ChangeButtonLowTemperature, Exp_ChangeButtonHighTemperature,"
                          " Exp_ChangeButtonStepSize, Exp_FanTargetTemp, Exp_FanTempKp, Exp_FanTempTi, Exp_FanTempTd," 
                          " Exp_FanSpeedMin, Exp_FanSpeedMax, Exp_FanSpeedKp, Exp_FanSpeedTi, Exp_FanSpeedTd,"
                          " Oth_LiveSetCurrent, Oth_LiveSetVoltage, Oth_ExternalActualObjectTemperature \n";

/*===============================================================================*/
/*                              PROTOTYPES                                       */
/*===============================================================================*/

char* GetField(char* line,int num);
char* CSVLine(FILE* fp);
/*===============================================================================*/
/*                              BODY                                             */
/*===============================================================================*/



int main(int argc, char** argv)
{
  


  /*Find ComPort number with $ls /dev */
  ComPort_Open(COMPORT_NUMBER,BAUD_RATE);
 


  /* Initialize Parameters */
  int32_t Address = 0;
  int32_t Inst = atoi(argv[1]);
 

  
 
  
  uint16_t* LParamNums = ParamNumLongInit();
  uint16_t* FParamNums = ParamNumFloatInit();
  uint32_t* LParamVals = ParamValLongInit();
  float*    FParamVals = ParamValFloatInit();



  /* If we're "setting", then the usage is ./Full set <filename> <time>
   * We'll only do this manually through ssh. 
   */

  if (!strcmp(argv[2], "set")){
      
      /* Grab the time from stdin */
      char* filename = argv[3];
      char* Month = argv[4];
      char* Day = argv[5];
      char* Year = argv[6];
      char* Hour = argv[7];
      char* Minute = argv[8];
      char* Second = argv[9];

      /* Find that line corresponding to that time in the CSV file */
      FILE* fp = fopen(filename, "r");
      char *line;
      while ((line = CSVLine(fp)) != NULL){
        int target = 1;
        if (strcmp(GetField(line,1), Month))
          target = 0;
        if (strcmp(GetField(line,2), Day))
          target = 0;
        if (strcmp(GetField(line,3), Year))
          target = 0;
        if (strcmp(GetField(line,4), Hour))
          target = 0;
        if (strcmp(GetField(line,5), Minute))
          target = 0;
        if (strcmp(GetField(line,6), Second))
          target = 0;
        if (target)
          break;
      }
      fclose(fp);

      /* Prepare parameter arrays with the information from that line */
      int i,j,k;
      
      for (i = 0; i < 39; i++)
        LParamVals[i] = atoi(GetField(line, i + 7));

      for (j = 0; j < 66; j++)
        sscanf(GetField(line, j + 46), "%f",&FParamVals[j] );


      /* Set those values to the Thermocontroller. */
      ParameterSetLong(Address, LParamNums, LParamVals);
      ParameterSetFloat(Address, FParamNums, FParamVals);

  }

   /* If we're "getting", then the usage is ./Full <filename> 
   * We'll do this automatically with boost asio string commands. 
   */
  else if (strcmp(argv[2], "set")) {

      char* _data_file = argv[2];
       /* Create <filename> if it doesn't already exist*/
      if (access(_data_file, F_OK) == -1){
        FILE *fp = fopen(_data_file, "ab+");
        fclose(fp);
      }
      /* If the file's empty, put the header at the top*/
      struct stat st;
      unsigned long long datasize = 1;
      if (stat(_data_file, &st) == 0)
         datasize = (unsigned long long)st.st_size;
      if (!datasize){
        FILE* fp2 = fopen(_data_file, "a");
        fputs(_csv_header,fp2);
        fclose(fp2);
       }


       /* Get the values from the Thermocontroller */
       ParameterSweepLong(Address, LParamNums, LParamVals);
       ParameterSweepFloat(Address, FParamNums, FParamVals);

       /* Save those values to the file */
       WriteToParamCSV(ParamString(LParamVals, FParamVals), _data_file);
  }
}

/* Returns the next line of a csv file a string */
char* CSVLine(FILE* fp){
  char* line = (char*)malloc(sizeof(char)*2400);
  char character;
  int i = 0;
  char end = 1;
  while((character = fgetc(fp)) != EOF){
      end = 0;
     if (character == '\n')
        break;
     line[i++] = character;
  }
  if (!end)
    return line;
  return NULL;
}


/* Parses a string into tokens, using the delimiter ',', and returns
 * the token of the number "num" */
char* GetField(char* line,int num)
{

	char character;
  char* token = (char*)malloc(sizeof(char)*20);


  /*
   * Indeces: i = index of line, j = index of token list, k = index of individual token string
   */
	int i = 0, j = 1, k = 0;
  while ((character = line[i++]) != '\0')
	{  


    /* If a delimiter is encountered, zero the token string index and erase the current token*/
     if (character == ','){
        if (j == num){
            break;
        }
        k = -1;
        free(token);
        token = (char*)malloc(sizeof(char)*20);
        j++;
     }
     else
        token[k] = character;
     k++;
	}
  return token;
}
