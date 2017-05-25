
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




/*===============================================================================*/
/*                             STRUCTS                                          */
/*===============================================================================*/

typedef struct {
	long type; 
	char mtext[COMMAND_SIZE];
} message_buf;

/*===============================================================================*/
/*                           PROTOTYPES                                             */
/*===============================================================================*/

//void* MessageCenter(void*);

/*===============================================================================*/
/*                              BODY                                             */
/*===============================================================================*/



int main(int argc, char** argv)
{
 
ComPort_Open(COMPORT_NUMBER,BAUD_RATE);
  int32_t Address = 0;


  char type = argv[1][0];
  printf("the type is %c\n", type);

  /* Initialize Parameters */
  int32_t Inst = atoi(argv[2]);


  uint16_t ParId = atoi(argv[3]);


  if (type == 'f'){
        MeParFloatFields Fields;
	sscanf(argv[4], "%f", &Fields.Value);
        MeCom_ParValuef(Address, ParId, Inst, &Fields, MeSet);
  }
  else if (type == 'i'){
        MeParLongFields Fields;
	Fields.Value = atoi(argv[4]);
        MeCom_ParValuef(Address, ParId, Inst, &Fields, MeSet);
  }
}
