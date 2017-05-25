#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "handler.h"
#include "interval.h"
#include "crontab.h"
#include "messages.h"
#include <unistd.h>
#include <string.h>
#include "reply.h"
#include "tec.h"
#include "util.h"
#include "ucirc_server.h"
#include <cstdlib>

typedef const char*(*handler_function)(ucirc_server_t *server, ucirc_message_t *message);

/* Night bit (Is UCIRC currently taking pictures?) */
const char *ucirc_handle_NT(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_NTQ(ucirc_server_t *server, ucirc_message_t *message);
/* Interval (in minutes) between pictures */
const char *ucirc_handle_INT(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_INTQ(ucirc_server_t *server, ucirc_message_t *message);


/* Full Set and Reset of the TEC */
const char *ucirc_handle_SET(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_RST(ucirc_server_t *server, ucirc_message_t *message);

/* Object Temperature */
const char *ucirc_handle_TMP1Q(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_TMP2Q(ucirc_server_t *server, ucirc_message_t *message);

/* Object Temperature Threshold */
const char *ucirc_handle_THRS1MNQ(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_THRS1MN(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_THRS1MXQ(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_THRS1MX(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_THRS2MNQ(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_THRS2MN(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_THRS2MXQ(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_THRS2MX(ucirc_server_t *server, ucirc_message_t *message);

/* Object Temperature Proximity Width */
const char *ucirc_handle_PWDTHQ(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_PWDTH(ucirc_server_t *server, ucirc_message_t *message);

/* Target Temperature */
const char *ucirc_handle_TARTMP1(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_TARTMP2(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_TARTMP1Q(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_TARTMP2Q(ucirc_server_t *server, ucirc_message_t *message);

/* Ramp Temperature */
const char *ucirc_handle_RTMP1Q(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_RTMP2Q(ucirc_server_t *server, ucirc_message_t *message);

/* Coarse Temperature */
const char *ucirc_handle_CTMPQ(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_CTMP(ucirc_server_t *server, ucirc_message_t *message);

/* Temperature is stable */
const char *ucirc_handle_TSBLEQ(ucirc_server_t *server, ucirc_message_t *message);

/* Current */
const char *ucirc_handle_CURR1Q(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_CURR2Q(ucirc_server_t *server, ucirc_message_t *message);

/* Current Limitation */
const char *ucirc_handle_MXCURR1Q(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_MXCURR1(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_MXCURR2Q(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_MXCURR2(ucirc_server_t *server, ucirc_message_t *message);

/* Voltage Limitation */
const char *ucirc_handle_MXVOLT1Q(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_MXVOLT1(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_MXVOLT2Q(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_MXVOLT2(ucirc_server_t *server, ucirc_message_t *message);

/* Voltage */
const char *ucirc_handle_VOLT1Q(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_VOLT2Q(ucirc_server_t *server, ucirc_message_t *message);

/* PID parameters */
const char *ucirc_handle_KPQ(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_KP(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_TIQ(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_TI(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_TDQ(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_TD(ucirc_server_t *server, ucirc_message_t *message);

/* Input Selection */
const char *ucirc_handle_INPS1Q(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_INPS1(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_INPS2Q(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_INPS2(ucirc_server_t *server, ucirc_message_t *message);


/* Output Stage Enable */
const char *ucirc_handle_OUTS1Q(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_OUTS1(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_OUT2Q(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_OUTS2(ucirc_server_t *server, ucirc_message_t *message);

/* Regularization Mode */
const char *ucirc_handle_REG1Q(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_REG1(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_REG2Q(ucirc_server_t *server, ucirc_message_t *message);
const char *ucirc_handle_REG2(ucirc_server_t *server, ucirc_message_t *message);

#define UCIRC_HANDLER_ENTRY(NAME) {#NAME, ucirc_handle_ ## NAME}

struct handler_entry
{
  const char *name;
  handler_function func;
};

struct handler_entry ucirc_handlers[] = {
    UCIRC_HANDLER_ENTRY(NT),
    UCIRC_HANDLER_ENTRY(NTQ),
    UCIRC_HANDLER_ENTRY(INT),
    UCIRC_HANDLER_ENTRY(INTQ),
    UCIRC_HANDLER_ENTRY(SET),
    UCIRC_HANDLER_ENTRY(RST),
    UCIRC_HANDLER_ENTRY(TMP1Q),
    UCIRC_HANDLER_ENTRY(TMP2Q),
    UCIRC_HANDLER_ENTRY(TARTMP1),
    UCIRC_HANDLER_ENTRY(TARTMP1Q),
    UCIRC_HANDLER_ENTRY(TARTMP2),
    UCIRC_HANDLER_ENTRY(TARTMP2Q),
    UCIRC_HANDLER_ENTRY(CURR1Q),
    UCIRC_HANDLER_ENTRY(CURR2Q),
    UCIRC_HANDLER_ENTRY(VOLT1Q),
    UCIRC_HANDLER_ENTRY(VOLT2Q),
    UCIRC_HANDLER_ENTRY(RTMP1Q),
    UCIRC_HANDLER_ENTRY(RTMP2Q),
    UCIRC_HANDLER_ENTRY(THRS1MNQ),
    UCIRC_HANDLER_ENTRY(THRS1MN),
    UCIRC_HANDLER_ENTRY(THRS1MXQ),
    UCIRC_HANDLER_ENTRY(THRS1MX),
    UCIRC_HANDLER_ENTRY(THRS2MNQ),
    UCIRC_HANDLER_ENTRY(THRS2MN),
    UCIRC_HANDLER_ENTRY(THRS2MXQ),
    UCIRC_HANDLER_ENTRY(THRS2MX),
    UCIRC_HANDLER_ENTRY(MXCURR1Q),
    UCIRC_HANDLER_ENTRY(MXCURR1),
    UCIRC_HANDLER_ENTRY(MXCURR2Q),
    UCIRC_HANDLER_ENTRY(MXCURR2),
    UCIRC_HANDLER_ENTRY(MXVOLT1Q),
    UCIRC_HANDLER_ENTRY(MXVOLT1),
    UCIRC_HANDLER_ENTRY(MXVOLT2Q),
    UCIRC_HANDLER_ENTRY(MXVOLT2),
    UCIRC_HANDLER_ENTRY(CTMPQ),
    UCIRC_HANDLER_ENTRY(CTMP),
    UCIRC_HANDLER_ENTRY(PWDTHQ),
    UCIRC_HANDLER_ENTRY(PWDTH),
    UCIRC_HANDLER_ENTRY(TSBLEQ),
    UCIRC_HANDLER_ENTRY(KPQ),
    UCIRC_HANDLER_ENTRY(KP),
    UCIRC_HANDLER_ENTRY(TIQ),
    UCIRC_HANDLER_ENTRY(TI),
    UCIRC_HANDLER_ENTRY(TDQ), 
    UCIRC_HANDLER_ENTRY(TD),
    UCIRC_HANDLER_ENTRY(INPS1Q),
    UCIRC_HANDLER_ENTRY(INPS1),
    UCIRC_HANDLER_ENTRY(INPS2Q),
    UCIRC_HANDLER_ENTRY(INPS2),
    UCIRC_HANDLER_ENTRY(OUTS1Q),
    UCIRC_HANDLER_ENTRY(OUTS1),
    UCIRC_HANDLER_ENTRY(OUT2Q),
    UCIRC_HANDLER_ENTRY(OUTS2),
    UCIRC_HANDLER_ENTRY(REG1Q),
    UCIRC_HANDLER_ENTRY(REG1),
    UCIRC_HANDLER_ENTRY(REG2Q),
    UCIRC_HANDLER_ENTRY(REG2),
};

const char *ucirc_handle(ucirc_server_t *server, ucirc_message_t *message)
{
    if (message->command == NULL)
        return NULL;
    int num_handlers = sizeof(ucirc_handlers) / sizeof(struct handler_entry);
    int i;
    for (i = 0; i < num_handlers; i++)
    {
        if (!strcmp(ucirc_handlers[i].name, message->command))
        {
            return ucirc_handlers[i].func(server, message);
        } 
    }
    return ERROR_RESPONSE;
}


/* Tell the camera that it's either night (1) or day (0) */
const char *ucirc_handle_NT(ucirc_server_t *server, ucirc_message_t *message)
{
    list_t params_list = message->params;
    if (list_size(&params_list) == 0)
	return ERROR_RESPONSE;    

    int night = atoi((char*)list_get_at(&params_list, 0));


    /* If the argment is 1, then st_t params_list = message->params;
174     float requested_temp = atof((const char *)list_get_at(&params_list, 0));
we need to populate the crontab file with the 
     *  apropriate signal */
    if (night)
        update_crontab(server->interval);
    else
        update_crontab(0);

    restart_cron();

    /* Update the Night bit in the server (for future queries) */
    server->night = night;

    if (night)
        send_singleton();

    /* Update the log indicator file, since we only want to copy 
     * log files to the DP-CPU during the night. */
    update_log_indicator_file(night);
   
    return MODIFY_SUCCESS_RESPONSE;
}


/* Query the Night bit. */
const char *ucirc_handle_NTQ(ucirc_server_t *server, ucirc_message_t *message)
{
    message->r_int = server->night;
    return INT_QUERY_RESPONSE;
}

/* Set the interval (in minutes) between pictures */
const char *ucirc_handle_INT(ucirc_server_t *server, ucirc_message_t *message)
{
    list_t params_list = message->params;
    if (list_size(&params_list) == 0)
        return ERROR_RESPONSE;
    int new_interval = atoi((char*)list_get_at(&params_list, 0));

    if (new_interval > 0 && new_interval <= MAX_INTERVAL)
    {
        server->interval = new_interval;
        set_interval_file(new_interval);
        if (server->night)
        {
            update_crontab(new_interval);
            restart_cron();
        }
        return MODIFY_SUCCESS_RESPONSE;
    }
    else
        return ERROR_RESPONSE;
}

/* Query the server's interval value */
const char *ucirc_handle_INTQ(ucirc_server_t *server, ucirc_message_t *message)
{
    message->r_int = server->interval;
    return INT_QUERY_RESPONSE;
const char *ucirc_handle_RTMP1Q(ucirc_server_t *server, ucirc_message_t *message);
}

const char *ucirc_handle_SET(ucirc_server_t *server, ucirc_message_t *message)
{
    /* If the file already exists, we need to delete it */
    if (access(GOOD_PARAMS_1, F_OK) != -1)
        remove(GOOD_PARAMS_1);
    if (access(GOOD_PARAMS_2, F_OK) != -1)
        remove(GOOD_PARAMS_2);

    /* files will be saved to /root/TEC/LargeParams/GoodState_<channel>.csv */
    char command1[COMMAND_SIZE], command2[COMMAND_SIZE];
    memset(command1, 0, COMMAND_SIZE);
    memset(command2, 0, COMMAND_SIZE);
    snprintf(command1, COMMAND_SIZE, "%s 1 %s",PARAM_PROGRAM, GOOD_PARAMS_1);
    snprintf(command2, COMMAND_SIZE, "%s 2 %s", PARAM_PROGRAM, GOOD_PARAMS_2);

    system(command1);
    system(command2);
   
    /* Now open the file and grab the date-time at which the parameters were written. */
    
    char *rv = (char*)malloc(sizeof(char)*TEC_SET_RESPONSE_SIZE);
    memset(rv, 0, TEC_SET_RESPONSE_SIZE);
    char *line, *test;
    FILE *fp = fopen(GOOD_PARAMS_1, "r");
    while ((test = CSVLine(fp)) != NULL)
        line = test;
    fclose(fp);
    int time_val;
    snprintf(rv, TEC_SET_RESPONSE_SIZE, "%d %d %d %d %d %d", atoi(GetField(line, 1)),
                                                             atoi(GetField(line, 2)), 
                                                             atoi(GetField(line, 3)), 
                                                             atoi(GetField(line, 4)), 
                                                             atoi(GetField(line, 5)), 
                                                             atoi(GetField(line, 6)));
    message->r_string = rv;
    return TEC_SET_RESPONSE;
}

const char *ucirc_handle_RST(ucirc_server_t *server, ucirc_message_t *message)
{
    list_t params_list = message->params;
    char *filename;
    int channel = atoi((char*)list_get_at(&params_list,0));
    if (channel == CHANNEL_ONE)
        filename = GOOD_PARAMS_1;
    else if (channel == CHANNEL_TWO)
        filename = GOOD_PARAMS_2;
    else if (channel == FULL_TEC_RESET_CHANNEL)
        if (tec_reset_device(ADDRESS))
            return MODIFY_SUCCESS_RESPONSE;
        else
            return ERROR_RESPONSE;
    else
        return ERROR_RESPONSE;

    /* Verify that the file exists before proceeding */
    if (access(filename, F_OK) == -1)
        return FILE_DOES_NOT_EXIST;

    char *test, *line = NULL;

    /* Get the appropriate line in the CSV file indicated by 
     *  the command */
    FILE *fp = fopen(filename, "r");
    while((test = CSVLine(fp)) != NULL)
        line = test;
    int month, day, year, hour, minute, second;
    month = atoi(GetField(line, 1));
    day = atoi(GetField(line, 2));
    year = atoi(GetField(line, 3)); 
    hour = atoi(GetField(line, 4)); 
    minute = atoi(GetField(line, 5));
    second = atoi(GetField(line, 6));

    /* Reset that channel */
    char command[COMMAND_SIZE];
    memset(command, 0, COMMAND_SIZE);
    snprintf(command, COMMAND_SIZE, "%s %d set %s %d %d %d %d %d %d", PARAM_PROGRAM,
                                                                      channel,
                                                                      filename,
                                                                      month,
                                                                      day,
                                                                      year,
                                                                      hour,
                                                                      minute,
                                                                      second);
    system(command);
    return MODIFY_SUCCESS_RESPONSE;
}

const char *ucirc_handle_RST_alt(ucirc_server_t *server, ucirc_message_t *message)
{
    
    list_t params_list = message->params;
    int channel = atoi((char*)list_get_at(&params_list,0));
    if (channel == FULL_TEC_RESET_CHANNEL)
    {
        if (tec_reset_device(ADDRESS))
            return MODIFY_SUCCESS_RESPONSE;
        else 
            return ERROR_RESPONSE;
    }

    char *filename = (char*)list_get_at(&params_list, 1);
    int month = atoi((char*)list_get_at(&params_list,2));
    int day = atoi((char*)list_get_at(&params_list,3));
    int year = atoi((char*)list_get_at(&params_list,4));
    int hour = atoi((char*)list_get_at(&params_list,5));
    int minute = atoi((char*)list_get_at(&params_list,6));
    int second = atoi((char*)list_get_at(&params_list,7));
    
    char full_file_path[FULL_PATH_SIZE];
    memset(full_file_path, 0, FULL_PATH_SIZE);
    snprintf(full_file_path, FULL_PATH_SIZE, "%s%s", LARGE_PARAM_PATH, filename);
    

    /* Verify that the file exists before proceeding */
    if (access(full_file_path, F_OK) == -1)
        return FILE_DOES_NOT_EXIST;

    char *test, *line = NULL;
    
    /* Get the appropriate line in the CSV file indicated by 
     *  the command */     
    FILE *fp = fopen(full_file_path, "r");
    while((test = CSVLine(fp)) != NULL)
    {
        if (atoi(GetField(test, 1)) != month)
           continue;
        else if (atoi(GetField(test, 2)) != day)
           continue;
        else if (atoi(GetField(test, 3)) != year)
           continue;
        else if (atoi(GetField(test, 4)) != hour)
           continue;
        else if (atoi(GetField(test, 5)) != minute)
           continue;
        else if (atoi(GetField(test, 6)) != second)
           continue;
        else
           line = test;
    }
    if (line == NULL)
        return TIME_DOES_NOT_EXIST;

    /* Reset that channel */
    char command[COMMAND_SIZE];
    memset(command, 0, COMMAND_SIZE);
    snprintf(command, COMMAND_SIZE, "%s %d set %s %d %d %d %d %d %d", PARAM_PROGRAM, 
                                                                      channel,
                                                                      full_file_path,
                                                                      month, 
                                                                      day, 
                                                                      year, 
                                                                      hour, 
                                                                      minute, 
                                                                      second);
    system(command);
    return MODIFY_SUCCESS_RESPONSE;
}

const char *ucirc_handle_TMP1Q(ucirc_server_t *server, ucirc_message_t *message)
{
    message->r_float = tec_get_float_val(PAR_ID_OBJECT_TEMP, CHANNEL_ONE);
    return FLOAT_QUERY_RESPONSE;
}

const char *ucirc_handle_TMP2Q(ucirc_server_t *server, ucirc_message_t *message)
{
    message->r_float = tec_get_float_val(PAR_ID_OBJECT_TEMP, CHANNEL_TWO);
    return FLOAT_QUERY_RESPONSE;
}

const char *ucirc_handle_TARTMP1(ucirc_server_t *server, ucirc_message_t *message)
{
    list_t params_list = message->params;
    if (list_size(&params_list) == 0)
        return ERROR_RESPONSE;
    float requested_temp = atof((const char *)list_get_at(&params_list, 0));
    if (temp_in_range(requested_temp) && 
        tec_set_float_val(requested_temp, PAR_ID_TARGET_TEMP, CHANNEL_ONE))
        return MODIFY_SUCCESS_RESPONSE;
    else
        return ERROR_RESPONSE;
}

const char *ucirc_handle_TARTMP2(ucirc_server_t *server, ucirc_message_t *message)
{
    list_t params_list = message->params;
    if (list_size(&params_list) == 0)
        return ERROR_RESPONSE;
    float requested_temp = atof((const char *)list_get_at(&params_list, 0));
    if (temp_in_range(requested_temp) && 
        tec_set_float_val(requested_temp, PAR_ID_TARGET_TEMP, CHANNEL_TWO))
        return MODIFY_SUCCESS_RESPONSE;
    else
        return ERROR_RESPONSE;
}

const char *ucirc_handle_TARTMP1Q(ucirc_server_t *server, ucirc_message_t *message)
{
    message->r_float = tec_get_float_val(PAR_ID_TARGET_TEMP, CHANNEL_ONE);
    return FLOAT_QUERY_RESPONSE;
}

const char *ucirc_handle_TARTMP2Q(ucirc_server_t *server, ucirc_message_t *message)
{
    message->r_float = tec_get_float_val(PAR_ID_TARGET_TEMP, CHANNEL_TWO);
    return FLOAT_QUERY_RESPONSE;
}

const char *ucirc_handle_CURR1Q(ucirc_server_t *server, ucirc_message_t *message)
{
    message->r_float = tec_get_float_val(PAR_ID_OUTPUT_CURRENT, CHANNEL_ONE);
    return FLOAT_QUERY_RESPONSE;
}

const char *ucirc_handle_CURR2Q(ucirc_server_t *server, ucirc_message_t *message)
{
    message->r_float = tec_get_float_val(PAR_ID_OUTPUT_CURRENT, CHANNEL_TWO);
    return FLOAT_QUERY_RESPONSE;
}

const char *ucirc_handle_VOLT1Q(ucirc_server_t *server, ucirc_message_t *message)
{
    message->r_float = tec_get_float_val(PAR_ID_OUTPUT_VOLTAGE, CHANNEL_ONE);
    return FLOAT_QUERY_RESPONSE;
}

const char *ucirc_handle_VOLT2Q(ucirc_server_t *server, ucirc_message_t *message)
{
    message->r_float = tec_get_float_val(PAR_ID_OUTPUT_VOLTAGE, CHANNEL_TWO);
    return FLOAT_QUERY_RESPONSE;
}

const char *ucirc_handle_RTMP1Q(ucirc_server_t *server, ucirc_message_t *message)
{
    message->r_float = tec_get_float_val(PAR_ID_RAMP_TEMP, CHANNEL_ONE);
    return FLOAT_QUERY_RESPONSE;
}

const char *ucirc_handle_RTMP2Q(ucirc_server_t *server, ucirc_message_t *message)
{
    message->r_float = tec_get_float_val(PAR_ID_RAMP_TEMP, CHANNEL_TWO);
    return FLOAT_QUERY_RESPONSE;
}

const char *ucirc_handle_THRS1MNQ(ucirc_server_t *server, ucirc_message_t *message)
{
    message->r_float = tec_get_float_val(PAR_ID_TEMP_MIN_THRESHOLD, CHANNEL_ONE);
    return FLOAT_QUERY_RESPONSE;
}

const char *ucirc_handle_THRS1MN(ucirc_server_t *server, ucirc_message_t *message)
{
    list_t params_list = message->params;
    if (list_size(&params_list) == 0)
        return ERROR_RESPONSE;
    float requested_val = atof((const char *)list_get_at(&params_list, 0));
    if (tec_set_float_val(requested_val, PAR_ID_TEMP_MIN_THRESHOLD, CHANNEL_ONE))
        return MODIFY_SUCCESS_RESPONSE;
    else
        return ERROR_RESPONSE;
}

const char *ucirc_handle_THRS1MXQ(ucirc_server_t *server, ucirc_message_t *message)
{
    message->r_float = tec_get_float_val(PAR_ID_TEMP_MAX_THRESHOLD, CHANNEL_ONE);
    return FLOAT_QUERY_RESPONSE;
}

const char *ucirc_handle_THRS1MX(ucirc_server_t *server, ucirc_message_t *message)
{
    list_t params_list = message->params;
    if (list_size(&params_list) == 0)
        return ERROR_RESPONSE;
    float requested_val = atof((const char *)list_get_at(&params_list, 0));
    if (tec_set_float_val(requested_val, PAR_ID_TEMP_MAX_THRESHOLD, CHANNEL_ONE))
        return MODIFY_SUCCESS_RESPONSE;
    else
        return ERROR_RESPONSE;
}

const char *ucirc_handle_THRS2MNQ(ucirc_server_t *server, ucirc_message_t *message)
{
    message->r_float = tec_get_float_val(PAR_ID_TEMP_MIN_THRESHOLD, CHANNEL_TWO);
    return FLOAT_QUERY_RESPONSE;
}

const char *ucirc_handle_THRS2MN(ucirc_server_t *server, ucirc_message_t *message)
{
    list_t params_list = message->params;
    if (list_size(&params_list) == 0)
        return ERROR_RESPONSE;
    float requested_val = atof((const char *)list_get_at(&params_list, 0));
    if (tec_set_float_val(requested_val, PAR_ID_TEMP_MIN_THRESHOLD, CHANNEL_TWO))
        return MODIFY_SUCCESS_RESPONSE;
    else
        return ERROR_RESPONSE;
}

const char *ucirc_handle_THRS2MXQ(ucirc_server_t *server, ucirc_message_t *message)
{
    message->r_float = tec_get_float_val(PAR_ID_TEMP_MAX_THRESHOLD, CHANNEL_TWO);
    return FLOAT_QUERY_RESPONSE;
}

const char *ucirc_handle_THRS2MX(ucirc_server_t *server, ucirc_message_t *message)
{
    list_t params_list = message->params;
    if (list_size(&params_list) == 0)
        return ERROR_RESPONSE;
    float requested_val = atof((const char *)list_get_at(&params_list, 0));
    if (tec_set_float_val(requested_val, PAR_ID_TEMP_MAX_THRESHOLD, CHANNEL_TWO))
        return MODIFY_SUCCESS_RESPONSE;
    else
        return ERROR_RESPONSE;
}

const char *ucirc_handle_MXCURR1Q(ucirc_server_t *server, ucirc_message_t *message)
{
    message->r_float = tec_get_float_val(PAR_ID_CURRENT_LIMIT, CHANNEL_ONE);
    return FLOAT_QUERY_RESPONSE;
}

const char *ucirc_handle_MXCURR1(ucirc_server_t *server, ucirc_message_t *message)
{
    list_t params_list = message->params;
    if (list_size(&params_list) == 0)
        return ERROR_RESPONSE;
    float requested_val = atof((const char *)list_get_at(&params_list, 0));
    printf("tec_set_float_val(%f, %d, %d)\n", requested_val, PAR_ID_CURRENT_LIMIT, CHANNEL_ONE);
    if (tec_set_float_val(requested_val, PAR_ID_CURRENT_LIMIT, CHANNEL_ONE))
        return MODIFY_SUCCESS_RESPONSE;
    else
        return ERROR_RESPONSE;
}

const char *ucirc_handle_MXCURR2Q(ucirc_server_t *server, ucirc_message_t *message)
{
    message->r_float = tec_get_float_val(PAR_ID_CURRENT_LIMIT, CHANNEL_TWO);
    return FLOAT_QUERY_RESPONSE;
}

const char *ucirc_handle_MXCURR2(ucirc_server_t *server, ucirc_message_t *message)
{
    list_t params_list = message->params;
    if (list_size(&params_list) == 0)
        return ERROR_RESPONSE;
    float requested_val = atof((const char *)list_get_at(&params_list, 0));
    if (tec_set_float_val(requested_val, PAR_ID_CURRENT_LIMIT, CHANNEL_TWO))
        return MODIFY_SUCCESS_RESPONSE;
    else
        return ERROR_RESPONSE;
}

const char *ucirc_handle_MXVOLT1Q(ucirc_server_t *server, ucirc_message_t *message)
{
    message->r_float = tec_get_float_val(PAR_ID_VOLTAGE_LIMIT, CHANNEL_ONE);
    return FLOAT_QUERY_RESPONSE;
}

const char *ucirc_handle_MXVOLT1(ucirc_server_t *server, ucirc_message_t *message)
{
    list_t params_list = message->params;
    if (list_size(&params_list) == 0)
        return ERROR_RESPONSE;
    float requested_val = atof((const char *)list_get_at(&params_list, 0));
    if (tec_set_float_val(requested_val, PAR_ID_VOLTAGE_LIMIT, CHANNEL_ONE))
        return MODIFY_SUCCESS_RESPONSE;
    else
        return ERROR_RESPONSE;
}

const char *ucirc_handle_MXVOLT2Q(ucirc_server_t *server, ucirc_message_t *message)
{
    message->r_float = tec_get_float_val(PAR_ID_VOLTAGE_LIMIT, CHANNEL_TWO);
    return FLOAT_QUERY_RESPONSE;
}

const char *ucirc_handle_MXVOLT2(ucirc_server_t *server, ucirc_message_t *message)
{
    list_t params_list = message->params;
    if (list_size(&params_list) == 0)
        return ERROR_RESPONSE;
    float requested_val = atof((const char *)list_get_at(&params_list, 0));
    if (tec_set_float_val(requested_val, PAR_ID_VOLTAGE_LIMIT, CHANNEL_TWO))
        return MODIFY_SUCCESS_RESPONSE;
    else
        return ERROR_RESPONSE;
}

const char *ucirc_handle_CTMPQ(ucirc_server_t *server, ucirc_message_t *message)
{
    message->r_float = tec_get_float_val(PAR_ID_COARSE_RAMP_TEMPERATURE, CHANNEL_ONE);
    return FLOAT_QUERY_RESPONSE;
}

const char *ucirc_handle_CTMP(ucirc_server_t *server, ucirc_message_t *message)
{
    list_t params_list = message->params;
    if (list_size(&params_list) == 0)
        return ERROR_RESPONSE;
    float requested_val = atof((const char *)list_get_at(&params_list, 0));
    if (tec_set_float_val(requested_val, PAR_ID_COARSE_RAMP_TEMPERATURE, CHANNEL_ONE))
        return MODIFY_SUCCESS_RESPONSE;
    else
        return ERROR_RESPONSE;
}

const char *ucirc_handle_PWDTHQ(ucirc_server_t *server, ucirc_message_t *message)
{
    message->r_float = tec_get_float_val(PAR_ID_TEMP_PROXIMITY_WIDTH, CHANNEL_ONE);
    return FLOAT_QUERY_RESPONSE;
}

const char *ucirc_handle_PWDTH(ucirc_server_t *server, ucirc_message_t *message)
{
    list_t params_list = message->params;
    if (list_size(&params_list) == 0)
        return ERROR_RESPONSE;
    float requested_val = atof((const char *)list_get_at(&params_list, 0));
    if (tec_set_float_val(requested_val, PAR_ID_TEMP_PROXIMITY_WIDTH, CHANNEL_ONE))
        return MODIFY_SUCCESS_RESPONSE;
    else
        return ERROR_RESPONSE;
}

const char *ucirc_handle_TSBLEQ(ucirc_server_t *server, ucirc_message_t *message)
{
    message->r_int = tec_get_int_val(PAR_ID_TEMP_IS_STABLE, CHANNEL_ONE);
    return INT_QUERY_RESPONSE;
}


const char *ucirc_handle_KPQ(ucirc_server_t *server, ucirc_message_t *message)
{
    message->r_float = tec_get_float_val(PAR_ID_PID_KP, CHANNEL_ONE);
    return FLOAT_QUERY_RESPONSE;
}

const char *ucirc_handle_KP(ucirc_server_t *server, ucirc_message_t *message)
{
    list_t params_list = message->params;
    if (list_size(&params_list) == 0)
        return ERROR_RESPONSE;
    float requested_val = atof((const char *)list_get_at(&params_list, 0));
    if (tec_set_float_val(requested_val, PAR_ID_PID_KP, CHANNEL_ONE))
        return MODIFY_SUCCESS_RESPONSE;
    else
        return ERROR_RESPONSE;
}

const char *ucirc_handle_TIQ(ucirc_server_t *server, ucirc_message_t *message)
{
    message->r_float = tec_get_float_val(PAR_ID_PID_TI, CHANNEL_ONE);
    return FLOAT_QUERY_RESPONSE;
}

const char *ucirc_handle_TI(ucirc_server_t *server, ucirc_message_t *message)
{
    list_t params_list = message->params;
    if (list_size(&params_list) == 0)
        return ERROR_RESPONSE;
    float requested_val = atof((const char *)list_get_at(&params_list, 0));
    if (tec_set_float_val(requested_val, PAR_ID_PID_TI, CHANNEL_ONE))
        return MODIFY_SUCCESS_RESPONSE;
    else
        return ERROR_RESPONSE;
}

const char *ucirc_handle_TDQ(ucirc_server_t *server, ucirc_message_t *message)
{
    message->r_float = tec_get_float_val(PAR_ID_PID_TD, CHANNEL_ONE);
    return FLOAT_QUERY_RESPONSE;
}

const char *ucirc_handle_TD(ucirc_server_t *server, ucirc_message_t *message)
{
    list_t params_list = message->params;
    if (list_size(&params_list) == 0)
        return ERROR_RESPONSE;
    float requested_val = atof((const char *)list_get_at(&params_list, 0));
    if (tec_set_float_val(requested_val, PAR_ID_PID_TD, CHANNEL_ONE))
        return MODIFY_SUCCESS_RESPONSE;
    else
        return ERROR_RESPONSE;
}

const char *ucirc_handle_INPS1Q(ucirc_server_t *server, ucirc_message_t *message)
{
     message->r_int = tec_get_int_val(PAR_ID_INPUT_SELECTION, CHANNEL_ONE);
    return INT_QUERY_RESPONSE;
}

const char *ucirc_handle_INPS1(ucirc_server_t *server, ucirc_message_t *message)
{
    list_t params_list = message->params;
    if (list_size(&params_list) == 0)
        return ERROR_RESPONSE;
    int requested_val = atoi((const char *)list_get_at(&params_list, 0));
    if (tec_set_int_val(requested_val, PAR_ID_INPUT_SELECTION, CHANNEL_ONE))
        return MODIFY_SUCCESS_RESPONSE;
    else
        return ERROR_RESPONSE;
}

const char *ucirc_handle_INPS2Q(ucirc_server_t *server, ucirc_message_t *message)
{
     message->r_int = tec_get_int_val(PAR_ID_INPUT_SELECTION, CHANNEL_TWO);
    return INT_QUERY_RESPONSE;
}

const char *ucirc_handle_INPS2(ucirc_server_t *server, ucirc_message_t *message)
{
    list_t params_list = message->params;
    if (list_size(&params_list) == 0)
        return ERROR_RESPONSE;
    int requested_val = atoi((const char *)list_get_at(&params_list, 0));
    if (tec_set_int_val(requested_val, PAR_ID_INPUT_SELECTION, CHANNEL_TWO))
        return MODIFY_SUCCESS_RESPONSE;
    else
        return ERROR_RESPONSE;
}

const char *ucirc_handle_OUTS1Q(ucirc_server_t *server, ucirc_message_t *message)
{
     message->r_int = tec_get_int_val(PAR_ID_OUTPUT_STAGE_ENABLE, CHANNEL_ONE);
    return INT_QUERY_RESPONSE;
}

const char *ucirc_handle_OUTS1(ucirc_server_t *server, ucirc_message_t *message)
{
    list_t params_list = message->params; 
    if (list_size(&params_list) == 0)
        return ERROR_RESPONSE;
    int requested_val = atoi((const char *)list_get_at(&params_list, 0));
    if (tec_set_int_val(requested_val, PAR_ID_OUTPUT_STAGE_ENABLE, CHANNEL_ONE))
        return MODIFY_SUCCESS_RESPONSE;
    else
        return ERROR_RESPONSE;
}

const char *ucirc_handle_OUT2Q(ucirc_server_t *server, ucirc_message_t *message)
{
     message->r_int = tec_get_int_val(PAR_ID_OUTPUT_STAGE_ENABLE, CHANNEL_TWO);
    return INT_QUERY_RESPONSE;
}

const char *ucirc_handle_OUTS2(ucirc_server_t *server, ucirc_message_t *message)
{
    list_t params_list = message->params;
    if (list_size(&params_list) == 0)
        return ERROR_RESPONSE;
    int requested_val = atoi((char *)list_get_at(&params_list, 0));
    if (tec_set_int_val(requested_val, PAR_ID_OUTPUT_STAGE_ENABLE, CHANNEL_TWO))
        return MODIFY_SUCCESS_RESPONSE;
    else
        return ERROR_RESPONSE;
}

const char *ucirc_handle_REG1Q(ucirc_server_t *server, ucirc_message_t *message)
{
     message->r_int = tec_get_int_val(PAR_ID_REGULATION_MODE, CHANNEL_ONE);
    return INT_QUERY_RESPONSE;
}

const char *ucirc_handle_REG1(ucirc_server_t *server, ucirc_message_t *message)
{
    list_t params_list = message->params;
    if (list_size(&params_list) == 0)
        return ERROR_RESPONSE;
    int requested_val = atoi((const char *)list_get_at(&params_list, 0));
    if (tec_set_int_val(requested_val, PAR_ID_REGULATION_MODE, CHANNEL_ONE))
        return MODIFY_SUCCESS_RESPONSE;
    else
        return ERROR_RESPONSE;
}

const char *ucirc_handle_REG2Q(ucirc_server_t *server, ucirc_message_t *message)
{
     message->r_int = tec_get_int_val(PAR_ID_REGULATION_MODE, CHANNEL_TWO);
    return INT_QUERY_RESPONSE;
}

const char *ucirc_handle_REG2(ucirc_server_t *server, ucirc_message_t *message)
{
    list_t params_list = message->params;
    if (list_size(&params_list) == 0)
        return ERROR_RESPONSE;
    int requested_val = atoi((const char *)list_get_at(&params_list, 0));
    if (tec_set_int_val(requested_val, PAR_ID_REGULATION_MODE, CHANNEL_TWO))
        return MODIFY_SUCCESS_RESPONSE;
    else
        return ERROR_RESPONSE;
}
