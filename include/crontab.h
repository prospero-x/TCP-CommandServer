#ifndef CRONTAB_H
#define CRONTAB_H

int check_crontab();
void update_crontab(int interval);
void restart_cron();

#endif /* CRONTAB_H */