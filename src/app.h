#ifndef APP_H
#define APP_H

typedef struct {
    char liteRun; /* If system is weak, do a lite run */
    int memAvail; /* Max memory available in KB, MAX 64 GB */
} SystemInfo;

void app_err(int errno);
int app_startup(SystemInfo *sysInfo);
int run_app(int argc, char **argv, SystemInfo *sysInfo);
void app_shutdown(SystemInfo *sysInfo);

#endif /* APP_H */
