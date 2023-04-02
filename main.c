#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include "processes.h"

static
void
print_kproc_info(proc_info *pinfo)
{
    /* print simple process info */
    printf("pid: %d\n", pinfo->p_pid);
    printf("parent pid: %d\n", pinfo->p_ppid);
    printf("process name: %s\n", pinfo->p_name);
    printf("cmd: %s\n", pinfo->p_cmd);
    printf("threads: %d\n", pinfo->p_threads);
}

static
void
print_kprocs(kinfo_proc *procs, size_t procCount)
{
    assert( procs != NULL );

    for (size_t i = 0; i < procCount; i++) {
        proc_info pinfo;
        GetSimpleProcInfo(&procs[i], &pinfo);   /* simplify process info */
        print_kproc_info(&pinfo);
        puts("");
    }
    printf("total: %ld\n", procCount);
}

static
void
simulate_activity_monitor()
{
    int             err;
    size_t          procCount = 0;
    kinfo_proc **   procList;
    kinfo_proc *    pinfo;

    procList = (kinfo_proc **)malloc(sizeof(kinfo_proc *));
    assert(procList != NULL);

    err = GetBSDProcessList(procList, &procCount);
    if (err == ENOMEM) {
        printf("out of memory!");
    } else {
        print_kprocs(*procList, procCount);
    }

    free(*procList);
    free(procList);
}

int main(int argc, char *argv[])
{
    simulate_activity_monitor();
    return 0;
}
