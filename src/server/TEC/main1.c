
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



const char* _csv_header = "Month,Day,Year,Hour,Minute,Second,ObjectTemp,SinkTemp,TargetObjectTemp,BaseplateTemp,ActualOutputCurrent, ActualOutputVoltage,DriverInputVoltage, ErrorNumber,TemperatureIsStable\n";

/*===============================================================================*/
/*                              BODY                                             */
/*===============================================================================*/



int main(int argc, char** argv)
{

  char* _data_file = argv[2];


  /*ComPort_Open(ComPort number, ComPort Speed (baud rate))*/
  /*Find ComPort number with $ls /dev */
  ComPort_Open(COMPORT_NUMBER,BAUD_RATE);
 


  /* Initialize Parameters */
  int32_t Address = 0;
  int32_t Inst = atoi(argv[1]);
 

  
  /* Initialize History.tsv if it doesn't already exist*/
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
  

  
  MeParLongFields lFields;
  MeParFloatFields fFields;


  
  
  struct tm * TimeInfo;
  
      // Get TEC Object Temperature//
      float obj_temp = 999999; //indicates an error
      if (MeCom_TEC_Mon_ObjectTemperature(Address, Inst, &fFields, MeGet)){
         obj_temp = fFields.Value;
     }
         
     
     //Get Sink Temperature //
      float sink_temp = 999999; //indicates an error 
     if (MeCom_TEC_Mon_SinkTemperature(Address, Inst, &fFields, MeGet)){
          sink_temp = fFields.Value;
      }
     

     //Get Target Temperature//
     float target_temp = 999999; //indicates an error
     if (MeCom_TEC_Mon_TargetObjectTemperature(Address, Inst, &fFields, MeGet)){
       target_temp = fFields.Value;
   	 }

     
     //Get Baseplate Temperature//
     float baseplate_temp = 999999; //indicates an error
     if (MeCom_TEC_Mon_BasePlateTemperature(Address, Inst, &fFields, MeGet)){
       baseplate_temp = fFields.Value;

     }
     //Get Output Current//
     float out_current = 999999;
     if (MeCom_TEC_Mon_ActualOutputCurrent(Address, Inst, &fFields, MeGet)){
       out_current = fFields.Value;
     }

     //Get Output Voltage//
     float out_voltage = 999999;
     if (MeCom_TEC_Mon_ActualOutputVoltage(Address, Inst, &fFields, MeGet)){
       out_voltage = fFields.Value;
     }

     //Get Input Voltage//
     float in_voltage = 999999;
     if (MeCom_TEC_Mon_DriverInputVoltage(Address,Inst,&fFields,MeGet)){
       in_voltage = fFields.Value;
     }

     //Get Error Number//
     long error = 999999;
     if (MeCom_TEC_Mon_ErrorNumber(Address,Inst, &lFields, MeGet)){
       error = lFields.Value;
     }

     //Get Temperature is Stable//
     long temp_stable = 999999;
     if (MeCom_TEC_Mon_TemperatureIsStable(Address, Inst, &lFields, MeGet)){
       temp_stable = lFields.Value;
     }


    
      WriteToCSV(QueryString(obj_temp,
           sink_temp,
           target_temp,
           baseplate_temp,
           out_current,
           out_voltage,
           in_voltage,
           error,
           temp_stable), argv[2]);
}
