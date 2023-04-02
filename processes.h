#ifndef __PROCESSES_H__
#define __PROCESSES_H__

#include <sys/sysctl.h>

typedef struct kinfo_proc kinfo_proc;
typedef struct proc_taskinfo proc_taskinfo;

typedef struct proc_info
{
    pid_t   p_pid;      /* process pid */
    pid_t   p_ppid;     /* process parent pid */
    char *  p_cmd;      /* process cmd */
    char *  p_name;     /* process name */
    int     p_threads;    /* threas count */
} proc_info;

int GetBSDProcessList(kinfo_proc **procList, size_t *procCount);

/* simplify process info */
void GetSimpleProcInfo(kinfo_proc *proc, proc_info *info);

#endif
