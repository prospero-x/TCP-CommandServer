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
/*                              BODY                                             */
/*===============================================================================*/



int main(int argc, char** argv)
{

  char* _data_file = argv[1];


  /*ComPort_Open(ComPort number, ComPort Speed (baud rate))*/
  /*Find ComPort number with $ls /dev */
  ComPort_Open(COMPORT_NUMBER,BAUD_RATE);



 /* Initialize Parameters */
  int32_t Address = 0;
  int32_t Inst = 1;
  int32_t Inst2 = 2;
	
  /* Initialize Parameters*/

  MeParLongFields lFields;
  MeParFloatFields fFields;



  /* Initialize History.tsv if it doesn't already exist*/
  if (access(_data_file, F_OK) == -1){
    FILE *fp = fopen(_data_file, "ab+");
    fclose(fp);
  }


      // Get TEC Object Temperature//
      float obj_temp = 999999; //indicates an error
      float obj_temp1 = 999999; //indicates an error 
      if (MeCom_TEC_Mon_ObjectTemperature(Address, Inst, &fFields, MeGet)){
         obj_temp = fFields.Value;
     }

      if (MeCom_TEC_Mon_ObjectTemperature(Address, Inst2, &fFields, MeGet)){
         obj_temp1 = fFields.Value;
     }



     //Get Sink Temperature //
      float sink_temp = 999999; //indicates an error 
      float sink_temp1 = 999999;
     if (MeCom_TEC_Mon_SinkTemperature(Address, Inst, &fFields, MeGet)){
          sink_temp = fFields.Value;
      }

     if (MeCom_TEC_Mon_SinkTemperature(Address, Inst2, &fFields, MeGet)){
          sink_temp1 = fFields.Value;
      }


     //Get Target Temperature//
     float target_temp = 999999; //indicates an error
     float target_temp1 = 999999;
     if (MeCom_TEC_Mon_TargetObjectTemperature(Address, Inst, &fFields, MeGet)){
       target_temp = fFields.Value;
         }
   
     if (MeCom_TEC_Mon_TargetObjectTemperature(Address, Inst2, &fFields, MeGet)){
       target_temp1 = fFields.Value;
         }


     //Get Output Current//
     float out_current = 999999;
     float out_current1 = 999999;
     if (MeCom_TEC_Mon_ActualOutputCurrent(Address, Inst, &fFields, MeGet)){
       out_current = fFields.Value;
     }


    if (MeCom_TEC_Mon_ActualOutputCurrent(Address, Inst2, &fFields, MeGet)){
       out_current1 = fFields.Value;
     }

     //Get Output Voltage//
     float out_voltage = 999999;
     float out_voltage1 = 999999;
     if (MeCom_TEC_Mon_ActualOutputVoltage(Address, Inst, &fFields, MeGet)){
       out_voltage = fFields.Value;
     }

    if (MeCom_TEC_Mon_ActualOutputVoltage(Address, Inst2, &fFields, MeGet)){
       out_voltage1 = fFields.Value;
     }

      WritetoTestCSV(TestString(obj_temp,
           sink_temp,
           target_temp,
           out_current,
           out_voltage), argv[1]);

      WritetoTestCSV(TestString(obj_temp1,
           sink_temp1,
           target_temp1,
           out_current1,
           out_voltage1), argv[2]);

}


