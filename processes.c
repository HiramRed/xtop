#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <libproc.h>
#include "processes.h"
#include "str.h"

int
GetBSDProcessList(kinfo_proc **procList, size_t *procCount)
{
    int                 err;        /* errno */
    kinfo_proc *        result;     /* result procList */
    bool                done;       /* is done */
    /* Management Information Base */
    static const int    mib[] = { CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0 };
    // Declaring mib as const requires us to cast it when passing it to
    // sysctl because the prototype doesn't include the const modifier.
    size_t              length;

    assert(procList != NULL);
    assert(*procList == NULL);
    assert(procCount != NULL);

    *procCount = 0;

    result = NULL;
    done = false;
    do {
        assert(result == NULL);

        // Call sysctl with a NULL buffer.

        length = 0;
        err = sysctl((int *)mib, (sizeof(mib) / sizeof(*mib)) - 1,
                NULL, &length,
                NULL, 0);
        if (err == -1) {
            err = errno;
        }

        // Allocate an appropriately sized buffer based on the results
        // from the previous call.

        if (err == 0) {
            result = malloc(length);
            if (result == NULL) {
                err = ENOMEM;
            }
        }

        // Call sysctl again with the new buffer.  If we get an ENOMEM
        // error, toss away our buffer and start again.

        if (err == 0) {
            err = sysctl( (int *) mib, (sizeof(mib) / sizeof(*mib)) - 1,
                    result, &length,
                    NULL, 0);
            if (err == -1) {
                err = errno;
            }
            if (err == 0) {
                done = true;
            } else if (err == ENOMEM) {
                assert(result != NULL);
                free(result);
                result = NULL;
                err = 0;
            }
        }
    } while (err == 0 && ! done);

    // Clean up and establish post conditions.

    if (err != 0 && result != NULL) {
        free(result);
        result = NULL;
    }
    *procList = result;
    if (err == 0) {
        *procCount = length / sizeof(kinfo_proc);
    }

    assert( (err == 0) == (*procList != NULL) );

    return err;
}

void
GetSimpleProcInfo(kinfo_proc *proc, proc_info *info)
{
    assert(proc != NULL);
    assert(info != NULL);

    int         last_slash;
    int         len;
    static char fullname[PROC_PIDPATHINFO_MAXSIZE];

    info->p_pid  =  proc->kp_proc.p_pid;
    info->p_ppid = proc->kp_eproc.e_ppid;
    /* get full path of the process and its length */
    len = proc_pidpath(info->p_pid, fullname, sizeof(fullname));
    info->p_cmd = str_slice(fullname, 0, len);

    if (len <= 0) {
        info->p_name = EMPTY_STR;
    } else {
        last_slash = str_last_index_of(fullname, '/') + 1;
        info->p_name = str_slice(fullname, last_slash, len - last_slash);
    }
    
    proc_taskinfo pti;
    /* get proc_taskinfo info, including its thread counts */
    if (sizeof(pti) == proc_pidinfo(info->p_pid, PROC_PIDTASKINFO, 0, &pti, sizeof(pti))) {
        info->p_threads = pti.pti_threadnum;
    } else {
        info->p_threads = 0;
    }
}
