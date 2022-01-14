#include<stdio.h>
#include<stdlib.h>
#include<sched.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int err_chk(int call_value, const char* msg)
{
    if(call_value<0)
    {
        perror(msg);
        exit(EXIT_FAILURE);
    }
    else
    {
        return call_value;
    }
}


int main()
{
    printf("Enter PID:\n");
    pid_t input_pid;
    scanf("%d", &input_pid);
    int policy = sched_getscheduler(input_pid);
    err_chk(policy, "Error getting policy!");
    printf("Current Policy for pid %d: ", input_pid);
    switch (policy)
    {
        case SCHED_FIFO:
            printf("SCHED_FIFO");
            break;
        case SCHED_OTHER:
            printf("SCHED_OTHER");
            break;
        case SCHED_RR:
            printf("SCHED_RR");
            break;
        // case SCHED_BATCH:
        //     printf("SCHED_BATCH");
        //     break;
        // case SCHED_IDLE:
        //     printf("SCHED_IDLE");
        //     break;
        // case SCHED_DEADLINE:
        //     printf("SCHED_DEADLINE");
        //     break
        default:
            break;
    }
    struct sched_param prio;
    
    err_chk(sched_getparam(input_pid, &prio), "Error getting priority!");
    printf("\n");
    printf("Current priority: %d\n", prio.sched_priority);

    prio.sched_priority++;
    printf("Changing current priority to SCHED_FIFO...\n");
    err_chk(sched_setscheduler(input_pid, SCHED_FIFO, &prio), "Error changing policy!");

}