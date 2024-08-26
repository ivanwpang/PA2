#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>
/************************************************************************************************
        These DEFINE statements represent the workload size of each task and
        the time quantum values for Round Robin scheduling for each task.
*************************************************************************************************/
#define WORKLOAD1 100000
#define WORKLOAD2 100000
#define WORKLOAD3 100000
#define WORKLOAD4 100000

#define QUANTUM1 1000
#define QUANTUM2 1000
#define QUANTUM3 1000
#define QUANTUM4 1000
/************************************************************************************************
                    DO NOT CHANGE THE FUNCTION IMPLEMENTATION
*************************************************************************************************/
void myfunction(int param){
    int i = 2;
    int j, k;
    while(i < param){
        k = i;
        for (j = 2; j <= k; j++)
        {
            if (k % j == 0){
                k = k/j;
                j--;
                if (k == 1){
                    break;
                }
            }
        }
        i++;
    }
}
/************************************************************************************************/
int main(int argc, char const *argv[])
{
    pid_t pid1, pid2, pid3, pid4;
    int running1, running2, running3, running4;
    pid1 = fork();
    if (pid1 == 0){
        myfunction(WORKLOAD1);
        exit(0);
    }
    kill(pid1, SIGSTOP);
    pid2 = fork();
    if (pid2 == 0){
        myfunction(WORKLOAD2);
        exit(0);
    }
    kill(pid2, SIGSTOP);
    pid3 = fork();
    if (pid3 == 0){
        myfunction(WORKLOAD3);
        exit(0);
    }
    kill(pid3, SIGSTOP);
    pid4 = fork();
    if (pid4 == 0){
        myfunction(WORKLOAD4);
        exit(0);
    }
    kill(pid4, SIGSTOP);
    /************************************************************************************************
        At this point, all  newly-created child processes are stopped, and ready for scheduling.
    *************************************************************************************************/
    /************************************************************************************************
        - Scheduling code starts here
        - Below is a sample schedule. (which scheduling algorithm is this?)
        - For the assignment purposes, you have to replace this part with the other scheduling methods
        to be implemented.
    ************************************************************************************************/
    //struct timeval start_time, end_time;
    struct timeval start_time[4] = {0,0,0,0};
    struct timeval end_time[4] = {0,0,0,0};
 
    
    //struct Timer time_array[4];
    int cpu_burst_times[] = {WORKLOAD1, WORKLOAD2, WORKLOAD3, WORKLOAD4};
    int running[] = {1,1,1,1};
    //int waiting_time[4];
    //int turnaround_time[4];
    pid_t runningpids[] = {pid1,pid2,pid3,pid4};
    int temp;
 
    
   
    
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 3; ++j) {
            if(cpu_burst_times[j]>cpu_burst_times[j+1]) {
                temp = cpu_burst_times[j];
                cpu_burst_times[j] = cpu_burst_times[j+1];
                cpu_burst_times[j+1] = temp;
                
                temp = runningpids[j];
                runningpids[j] = runningpids[j+1];
                runningpids[j+1] = temp;
            
            }
        }
    }
    
    for(int k = 0; k < 4;++k) {
        gettimeofday(&start_time[k], NULL);
    }
    
    double response_time[4] = {0,0,0,0};
    double average_time [4] = {0,0,0,0};
    double total_average=0;

    //all processes started here
   


    for(int h = 0; h < 4; h++) {
        kill(runningpids[h], SIGCONT);
        waitpid(runningpids[h], &running[h], 0);
        //kill(runningpids[h], SIGSTOP);
        gettimeofday(&end_time[h], NULL);
        //printf("%.6f",end_time[h]);
        response_time[h] = (double) (end_time[h].tv_sec - start_time[h].tv_sec) +
                                 (double)(end_time[h].tv_usec - start_time[h].tv_usec) / 1e6;
        //average_time[h] +=response_time[h];
        printf("%.6f\n", response_time[h]);
        //printf("burst time %d  pid %d\n",cpu_burst_times[h],runningpids[h]);
    }
    
    double values = 0;

    for(int d = 0; d < 4; d++) {
        values+=response_time[d];
    }
    //printf("%.6f\n",total_average);
        
    total_average = (double) values/4.00;
    
    printf("%.6f\n", total_average);

        
        
    
    
    /************************************************************************************************
        - Scheduling code ends here
    ************************************************************************************************/
    return 0;
}
