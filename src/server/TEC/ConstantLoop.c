#include <stdio.h>
#include <string.h>
#include <time.h>
#include "writer.h"
#include "PeriodicLoop.h"

#define ONESECOND 999999

void UpdateRealClock(tm ** info){
  time_t c;
  time(&c);
  *info = localtime(&c);
}

void WritePeriodically(int period, tm * info, float f){
  UpdateRealClock(&info);
  int seconds = info -> tm_sec;

  /* Wait until the next multiple of <period> seconds */
  if (seconds % period)
    usleep(period - (seconds & period))*ONESSECOND);
  WriteToCSV(QueryString(f));
  printf("Writing at %s\n", asctime(info);

	 /* Wait another <period> seconds*/
	 usleep(period*ONESECOND);
}
