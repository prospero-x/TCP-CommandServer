#ifndef PLOOP_H
#define PLOOP_H

typedef struct tm tm;

void UpdateRealClocl(tm ** info);

void WritePeriodically(int period, tm*info, float obj_temp,
		                            float sink_temp,
		                            float target_temp,
		                            float baseplate_temp,
		                            float out_current,
		                            float out_voltage,
		                            float in_voltage,
		                            long error,
		                            long temp_stable);

void WriteEveryFewHours(int period, tm* info, uint32_t* long_vals, float* float_vals);

#endif 
