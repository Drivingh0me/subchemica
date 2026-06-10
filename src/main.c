#include "app.h"
#include "error.h"

int main(int argc, char **argv)
{
    int status;
    SystemInfo sysInfo;

    status = app_startup(&sysInfo);
    if (status) {
        app_err(status, sysInfo.errorState);
    }

    status = run_app(argc, argv, &sysInfo);
    if (status) {
        app_err(status);
    }

    app_shutdown(&sysInfo);

    return 0;
}
