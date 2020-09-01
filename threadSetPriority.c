#include <pthread.h>
#include <sched.h>

pthread_attr_t tattr;
pthread_t tid;
int ret;
int newprio = 20;
sched_param param;

/* initialized with default attributes */
ret = pthread_attr_init (&tattr);

/* safe to get existing scheduling param */
ret = pthread_attr_getschedparam (&tattr, &param);

/* set the priority; others are unchanged */
param.sched_priority = newprio;

/* setting the new scheduling param */
ret = pthread_attr_setschedparam (&tattr, &param);

/* with new priority specified */
ret = pthread_create (&tid, &tattr, func, arg);

Advance Level >>>>> Set Priority
Prioriyt level Linux 1 and 99.
       int sched_setscheduler(pid_t pid, int policy,
                              const struct sched_param *param);
       SCHED_OTHER   the standard round-robin time-sharing policy;
       SCHED_BATCH   for "batch" style execution of processes; and
       SCHED_IDLE    for running very low priority background jobs.
for special time-critical applications that need precise control over the way in which runnable threads are selected for execution
      Real time policy: SCHED_FIFO    SCHED_RR      
