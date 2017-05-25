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
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

/*===============================================================================*/
/*                             MACROS                                            */
/*===============================================================================*/
#define WAITTIME 5
#define ONESECOND 999999
#define COMPORT_NUMBER 0
#define BAUD_RATE 57600
#define COMMAND_SIZE 4096
#define INTERVAL 5

int main()
{
  printf("Hello!\n");
  

  usleep(1000000*2);
  ComPort_Open(COMPORT_NUMBER,BAUD_RATE);
  int32_t Address = 0;


  MeParLongFields lFields;
  MeParFloatFields fFields;

  MeCom_ParValuel(Address, 2000, 1, &lFields, MeGet);
  printf("2000 for Channel 1: %d\n", lFields.Value);

  MeCom_ParValuel(Address, 2000, 2, &lFields, MeGet);
  printf("2000  for Channel 2: %d\n", lFields.Value);

  MeCom_ParValuel(Address, 2010, 1, &lFields, MeGet);
  printf("2010 for Channel 1: %d\n", lFields.Value);

  MeCom_ParValuel(Address, 2010, 2, &lFields, MeGet);
  printf("2010 for Channel 2 %d\n", lFields.Value);

  MeCom_ParValuel(Address, 2040, 1, &lFields, MeGet);
  printf("2040 for Channel 1: %d\n", lFields.Value);

  MeCom_ParValuel(Address, 3020, 1, &lFields, MeGet);
  printf("3020 for Channel 1: %d\n", lFields.Value);

  MeCom_ParValuel(Address, 3020, 2, &lFields, MeGet);
  printf("3020  for Channel 2 %d\n", lFields.Value);

  MeCom_ParValuef(Address, 4010, 1, &fFields, MeGet);
  printf("4010 for Channel 1: %f\n", fFields.Value);

  MeCom_ParValuef(Address, 4010, 2, &fFields, MeGet);
  printf("4010, for Channel 2: %f\n", fFields.Value);

  MeCom_ParValuef(Address, 4011, 1, &fFields, MeGet);
  printf("4011 for Channel 1: %f\n", fFields.Value);

  MeCom_ParValuef(Address, 4011, 2, &fFields, MeGet);
  printf("4011 for Channel 2; %f\n", fFields.Value);
}





