#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/time.h>

/***********************************************************************************
*************
These DEFINE statements represent the workload size of each task and
the time quantum values for Round Robin scheduling for each task.
***********************************************************************************
**************/
// #define WORKLOAD1 100000
// #define WORKLOAD2 50000
// #define WORKLOAD3 25000
// #define WORKLOAD4 10000

#define WORKLOAD1 100000
#define WORKLOAD2 100000
#define WORKLOAD3 100000
#define WORKLOAD4 100000

#define QUANTUM1 100000
#define QUANTUM2 100000
#define QUANTUM3 100000
#define QUANTUM4 100000
/*
***********************************************************************************
*************
DO NOT CHANGE THE FUNCTION IMPLEMENTATION
***********************************************************************************
**************/
void myfunction(int param)
{
    int i = 2;
    int j, k;
    while (i < param)
    {
        k = i;
        for (j = 2; j <= k; j++)
        {
            if (k % j == 0)
            {
                k = k / j;
                j--;
                if (k == 1)
                {
                    break;
                }
            }
        }
        i++;
    }
}
/*
***********************************************************************************
*************/
int main(int argc, char const *argv[])
{
    
    pid_t pid1, pid2, pid3, pid4;
    int running1, running2, running3, running4;

    struct timeval rr_start_time1, rr_start_time2, rr_start_time3, rr_start_time4, fcfs_start_time1, fcfs_start_time2, fcfs_start_time3, fcfs_start_time4;
    // struct timeval rr_end_time1, rr_end_time2, rr_end_time3, rr_end_time4, fcfs_end_time1, fcfs_end_time2, fcfs_end_time3, fcfs_end_time4;

    pid1 = fork();

    if (pid1 == 0)
    {
        myfunction(WORKLOAD1);
        exit(0);
    }
    kill(pid1, SIGSTOP);
    gettimeofday(&rr_start_time1, NULL);
    pid2 = fork();

    if (pid2 == 0)
    {
        myfunction(WORKLOAD2);
        exit(0);
    }
    kill(pid2, SIGSTOP);
    gettimeofday(&rr_start_time2, NULL);
    pid3 = fork();

    if (pid3 == 0)
    {
        myfunction(WORKLOAD3);
        exit(0);
    }
    kill(pid3, SIGSTOP);
    gettimeofday(&rr_start_time3, NULL);
    pid4 = fork();

    if (pid4 == 0)
    {
        myfunction(WORKLOAD4);
        exit(0);
    }
    kill(pid4, SIGSTOP);
    gettimeofday(&rr_start_time4, NULL);
    /**********************************************************************************
    **************
    At this point, all newly-created child processes are stopped, and
    ready for scheduling.
    ***********************************************************************************
    **************/
    /**********************************************************************************
    **************
    - Scheduling code starts here
    - Below is a sample schedule. (which scheduling algorithm is this?)
    - For the assignment purposes, you have to replace this part with the
    other scheduling methods
    to be implemented.
    ***********************************************************************************
    *************/

    running1 = 1;
    running2 = 1;
    running3 = 1;
    running4 = 1;

    pid_t rr_array[4] = {pid1, pid2, pid3, pid4};
    pid_t ff_array[4] = {0, 0, 0, 0};
    int running_array[4] = {running1, running2, running3, running4};
    int left_running_array[4] = {0, 0, 0, 0};
    struct timeval rrEndTime[4];


    // round robin code

    for (int i = 0; i < 4; ++i)
    {
        if (rr_array[i] > 0)
        {
            // printf("proccess %d starts\n", i + 1);
            kill(rr_array[i], SIGCONT);
            usleep(QUANTUM1);
            kill(rr_array[i], SIGSTOP);
        
            waitpid(rr_array[i], &running_array[i], WNOHANG);
            if (running_array[i] > 0)
            {
                // printf("proccess %d not done moves to q2\n", i + 1);
                ff_array[i] = rr_array[i];
                left_running_array[i] = running_array[i];
            }
            gettimeofday(&rrEndTime[i], NULL);
        }
    }

    for (int j = 0; j < 4; ++j)
    {
        if (ff_array[j] > 0)
        {
            // printf("we are at the continouation of proccess %d\n", j + 1);
            kill(ff_array[j], SIGCONT);
            waitpid(ff_array[j], &left_running_array[j], 0);
            gettimeofday(&rrEndTime[j], NULL);
        }
    }

    double response_time1 = (double)(rrEndTime[0].tv_sec - rr_start_time1.tv_sec) + (double)(rrEndTime[0].tv_usec - rr_start_time1.tv_usec) / 1000000.0;
    double response_time2 = (double)(rrEndTime[1].tv_sec - rr_start_time2.tv_sec) + (double)(rrEndTime[1].tv_usec - rr_start_time2.tv_usec) / 1000000.0;
    double response_time3 = (double)(rrEndTime[2].tv_sec - rr_start_time3.tv_sec) + (double)(rrEndTime[2].tv_usec - rr_start_time3.tv_usec) / 1000000.0;
    double response_time4 = (double)(rrEndTime[3].tv_sec - rr_start_time4.tv_sec) + (double)(rrEndTime[3].tv_usec - rr_start_time4.tv_usec) / 1000000.0;
    double average_response_time = (response_time1 + response_time2+ response_time3 + response_time4) / 4.0;



    printf("%.9f\n", response_time1);
    printf("%.9f\n", response_time2);
    printf("%.9f\n", response_time3);
    printf("%.9f\n", response_time4);
    printf("%.9f\n", average_response_time);

    /**********************************************************************************
    **************
    - Scheduling code ends here
    ***********************************************************************************
    *************/
    return 0;
}