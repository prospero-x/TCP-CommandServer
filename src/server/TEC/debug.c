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
#include <math.h>
#include <sys/stat.h>


#define WAITTIME 60
#define HOURSWAIT 0.00139
#define ONESECOND 999999
#define COMPORT_NUMBER 0
#define BAUD_RATE 57600

int main(int argc, char** argv)
{


  /*ComPort_Open(ComPort number, ComPort Speed (baud rate))*/
  /*Find ComPort number with $ls /dev */
  ComPort_Open(COMPORT_NUMBER,BAUD_RATE);


  /* Initialize Parameters */
  int32_t Address = 0;
  int32_t Inst = atoi(argv[1]);


  MeParLongFields lFields;
  MeParFloatFields fFields;
   printf("TEC CHANNEL %d\n", Inst);
   printf("OBJECT TEMP   SINK TEMP     TARGET TEMP  BP TEMP       CURRENT        VOUT         VIN    ERROR #  TEMP-IS-STABLE\n");

    while(1)
    {
     // Get TEC Object Temperature//
      float obj_temp = NAN; //indicates an error
     
      if (MeCom_TEC_Mon_ObjectTemperature(Address, Inst, &fFields, MeGet)){
        // printf("object temp good\n");
         obj_temp = fFields.Value;
     }


     //Get Sink Temperature //
      float sink_temp = NAN; //indicates an error 
     if (MeCom_TEC_Mon_SinkTemperature(Address, Inst, &fFields, MeGet)){
          //printf("sink_temp good\n");
          sink_temp = fFields.Value;
      }


     //Get Target Temperature//
     
     float target_temp = NAN; //indicates an error
     if (MeCom_TEC_Mon_TargetObjectTemperature(Address, Inst, &fFields, MeGet)){
       //printf("target temp good \n");
       target_temp = fFields.Value;
         }


     //Get Baseplate Temperature//
     float baseplate_temp = NAN; //indicates an error
     if (Inst == 1){
     if (MeCom_TEC_Mon_BasePlateTemperature(Address, Inst, &fFields, MeGet)){
       //printf("baseplate temp good\n");
       baseplate_temp = fFields.Value;

     }}
     //Get Output Current//
     float out_current = NAN;
     if (MeCom_TEC_Mon_ActualOutputCurrent(Address, Inst, &fFields, MeGet)){
       out_current = fFields.Value;
       //printf("out current good\n");
     }

	
	
         //Get Output Voltage//
     float out_voltage = NAN;
     if (MeCom_TEC_Mon_ActualOutputVoltage(Address, Inst, &fFields, MeGet)){
       out_voltage = fFields.Value;
       //printf("out voltage good\n");
     }

     //Get Input Voltage//
     float in_voltage = NAN;
     if (Inst == 1){
     if (MeCom_TEC_Mon_DriverInputVoltage(Address,Inst,&fFields,MeGet)){
       in_voltage = fFields.Value;
       //printf("in voltage good\n");
     }}

     //Get Error Number//
     long error = NAN;
     if (Inst == 1){
     if (MeCom_TEC_Mon_ErrorNumber(Address,Inst, &lFields, MeGet)){
       error = lFields.Value;
       //printf("error good\n");
     }}

     //Get Temperature is Stable//
     long temp_stable = NAN;
     if (MeCom_TEC_Mon_TemperatureIsStable(Address, Inst, &lFields, MeGet)){
       temp_stable = lFields.Value;
       //printf("temp_stable good\n");
     }
  
     printf("%f    %f     %f    %f     %f    %f    %f   %li        %li\n", obj_temp, sink_temp, target_temp, baseplate_temp, out_current, out_voltage, in_voltage, error, temp_stable);

     usleep(1000000);
     }
}
