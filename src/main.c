#include "app.h"

int main(int argc, char **argv)
{
    /* Add atf, alloc to free to nucf_err pass*/
    int status;
    SystemInfo sysInfo;

    status = app_startup(&sysInfo);
    if (status) {
        app_err(status);
    }

    status = run_app(argc, argv, &sysInfo);
    if (status) {
        app_err(status);
    }

    app_shutdown(sysInfo);

    return 0;
}
