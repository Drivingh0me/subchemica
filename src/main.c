#include "subchemica.h"

int main(int argc, char **argv)
{
    /* Add atf, alloc to free */
    int status;
    nucfSystemInfo sysInfo;

    status = nucf_startup(&sysInfo);
    if (status) {
        /* Last point to apeal error. Return as fatal */
        nucf_err(status);
    }

    status = nucf_run_app(argc, argv, sysInfo);
    if (status) {
        nucf_err(status);
    }

    status = nucf_shutdown(&sysInfo);
    if (status) {
        nucf_err(status);
    }

    return 0;
}
