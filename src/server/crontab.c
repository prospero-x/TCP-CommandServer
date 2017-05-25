#include <unistd.h>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>

static char *crontab = "/var/spool/cron/crontabs/root";
static char *exec_file = "/root/bin/daq_ucirc.sh";

/* returns 0 if crontab is empty, 1 otherwise */
int check_crontab()
{
	struct stat st;
	stat(crontab, &st);
	return st.st_size ? 1 : 0; 
}

/* Updates the crontab to make the file run every INTERVAL minutes */
void update_crontab(int interval)
{
	/* Nonzero interval means we want to set the crontab to a meaningful value */
	if (interval > 0)
	{
	/* Set the first argument to match the most recent camera capture interval
         * stored in the server */
	    char minute_arg[7];
	    if (interval == 1)
	        sprintf(minute_arg, "\"*");
	    else
	        sprintf(minute_arg, "\"*/%d", interval);

	    /* Modify the crontab file */
	    char command[100];
	    sprintf(command, "echo %s * * * * %s\" > %s", minute_arg,
	    											  exec_file,
	    											  crontab);
	    system(command);
	}

	else
		system("> /var/spool/cron/crontabs/root");
}

void restart_cron()
{
	 system("sudo service cron restart");
}
