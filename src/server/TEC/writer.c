#include <stdio.h>
#include <string.h>
#include <time.h>
#include "writer.h"

#define QUERY_SIZE 500
#define PARAM_SIZE 1000

const char* _path_to_writes = "/root/Test1/History.csv";

const char* _path_to_param_writes = "/root/Test1/Params.csv";

/*TSV format: month  day  year  hour  minute  second  ObjectTemp*/
const char* _query_fmt ="%d,%d,%d,%d,%d,%d,%f,%f,%f,%f,%f,%f,%f, %li,%li\n";

const char* _param_fmt = "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,"
                          "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,"
                          "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,"
                          "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,"
                          "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,"
                          "%f,%f,%f,%f,%f,%f\n";
char* QueryString(float obj_temp, float sink_temp, float target_temp,
		  float baseplate_temp, float out_current, float out_voltage,
		  float in_voltage, long error, long temp_stable){
     char buf[QUERY_SIZE];
     memset(buf, 0, QUERY_SIZE);
     struct tm * TimeInfo;
     time_t rawtime;
     time(&rawtime);
     TimeInfo = localtime(&rawtime);
     snprintf(buf, QUERY_SIZE, _query_fmt,
	               TimeInfo -> tm_mon + 1,
	               TimeInfo -> tm_mday,
	               TimeInfo -> tm_year + 1900,
	               TimeInfo -> tm_hour,
	               TimeInfo -> tm_min,
	               TimeInfo -> tm_sec,
	               obj_temp,
	               sink_temp,
	               target_temp,
	               baseplate_temp,
	               out_current,
	               out_voltage,
	               in_voltage,
	               error,
	               temp_stable
	                            );
     return strdup(buf);
}

char* TestString(float obj_temp, float sink_temp, float target_temp, float out_current, float out_voltage){
	char buf[QUERY_SIZE];
	snprintf(buf, QUERY_SIZE, "%f,%f,%f,%f,%f", obj_temp, sink_temp, target_temp, out_current, out_voltage);
	return strdup(buf);
}


char* ParamString(uint32_t* long_vals, float* float_vals)
{
    char buf[PARAM_SIZE];
    memset(buf,0,PARAM_SIZE);
    struct tm * TimeInfo;
    time_t rawtime;
    time(&rawtime);
    TimeInfo = localtime(&rawtime);
    snprintf(buf, PARAM_SIZE, _param_fmt, 
    	                     TimeInfo -> tm_mon + 1,
    	                     TimeInfo -> tm_mday,
    	                     TimeInfo -> tm_year + 1900,
    	                     TimeInfo -> tm_hour, 
    	                     TimeInfo -> tm_min, 
    	                     TimeInfo -> tm_sec,
    	                     long_vals[0],
    	                     long_vals[1],
    	                     long_vals[2],
    	                     long_vals[3],
    	                     long_vals[4],
    	                     long_vals[5],
    	                     long_vals[6],
    	                     long_vals[7],
    	                     long_vals[8],
    	                     long_vals[9],
    	                     long_vals[10],
    	                     long_vals[11],
    	                     long_vals[12],
    	                     long_vals[13],
    	                     long_vals[14],
    	                     long_vals[15],
    	                     long_vals[16],
    	                     long_vals[17],
    	                     long_vals[18],
    	                     long_vals[19],
    	                     long_vals[20],
    	                     long_vals[21],
    	                     long_vals[22],
    	                     long_vals[23],
    	                     long_vals[24],
    	                     long_vals[25],
    	                     long_vals[26],
    	                     long_vals[27],
    	                     long_vals[28],
    	                     long_vals[29],
    	                     long_vals[30],
    	                     long_vals[31],
    	                     long_vals[32],
    	                     long_vals[33],
    	                     long_vals[34],
    	                     long_vals[35],
    	                     long_vals[36],
    	                     long_vals[37],
    	                     long_vals[38],
    	                     float_vals[0], 
    	                     float_vals[1],
    	                     float_vals[2],
    	                     float_vals[3],
    	                     float_vals[4],
    	                     float_vals[5],
    	                     float_vals[6],
    	                     float_vals[7],
    	                     float_vals[8],
    	                     float_vals[9],
    	                     float_vals[10],
    	                     float_vals[11],
    	                     float_vals[12],
    	                     float_vals[13],
    	                     float_vals[14],
    	                     float_vals[15],
    	                     float_vals[16],
    	                     float_vals[17],
    	                     float_vals[18],
    	                     float_vals[19],
    	                     float_vals[20],
    	                     float_vals[21],
    	                     float_vals[22],
    	                     float_vals[23],
    	                     float_vals[24],
    	                     float_vals[25],
    	                     float_vals[26],
    	                     float_vals[27],
    	                     float_vals[28],
    	                     float_vals[29],
    	                     float_vals[30],
    	                     float_vals[31],
    	                     float_vals[32],
    	                     float_vals[33],
    	                     float_vals[34],
    	                     float_vals[35],
    	                     float_vals[36],
    	                     float_vals[37],
    	                     float_vals[38],
    	                     float_vals[39],
    	                     float_vals[40],
    	                     float_vals[41],
    	                     float_vals[42],
    	                     float_vals[43],
    	                     float_vals[44],
    	                     float_vals[45],
    	                     float_vals[46],
    	                     float_vals[47],
    	                     float_vals[48],
    	                     float_vals[49],
    	                     float_vals[50],
    	                     float_vals[51],
    	                     float_vals[52],
    	                     float_vals[53],
    	                     float_vals[54],
    	                     float_vals[55],
    	                     float_vals[56],
    	                     float_vals[57],
    	                     float_vals[58],
    	                     float_vals[59],
    	                     float_vals[60],
    	                     float_vals[61],
    	                     float_vals[62],
    	                     float_vals[63],
    	                     float_vals[64],
    	                     float_vals[65],
    	                     float_vals[66]);
    return strdup(buf);
}
void WriteToCSV(char* str, char* filename){
  FILE *fp = fopen(filename, "a+");
  fputs(str, fp);
  fclose(fp);
}

void WritetoTestCSV(char* str, char* filename){
  FILE*fp = fopen(filename, "w+");
  fputs(str,fp);
  fclose(fp);
}
void WriteToParamCSV(char* str, char* filename){
  FILE *fp = fopen(filename, "a+");
  fputs(str,fp);
  fclose(fp);
}

