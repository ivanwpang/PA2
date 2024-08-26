#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>  
#include <stdlib.h>  
#include <sys/wait.h> 
#include <string.h> 
#include <time.h> 
#include <signal.h>
#include <sys/time.h>

/************************************************************************************************ 
		These DEFINE statements represent the workload size of each task and 
		the time quantum values for Round Robin scheduling for each task.
*************************************************************************************************/

#define WORKLOAD1 100000
#define WORKLOAD2 50000
#define WORKLOAD3 25000
#define WORKLOAD4 10000

// #define WORKLOAD1 100000
// #define WORKLOAD2 100000
// #define WORKLOAD3 100000
// #define WORKLOAD4 100000

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
    struct timeval start_time1, start_time2, start_time3, start_time4;
    struct timeval end_time1, end_time2, end_time3, end_time4;

	pid1 = fork();
    //gettimeofday(&start_time1, NULL);

	if (pid1 == 0){

		myfunction(WORKLOAD1);

		exit(0);
	}
	kill(pid1, SIGSTOP);
	gettimeofday(&start_time1, NULL);

	pid2 = fork();
    //gettimeofday(&start_time2, NULL);

	if (pid2 == 0){
        
		myfunction(WORKLOAD2);

		exit(0);
	}
	kill(pid2, SIGSTOP);
	gettimeofday(&start_time2, NULL);

	pid3 = fork();
    //gettimeofday(&start_time3, NULL);

	if (pid3 == 0){
        
		myfunction(WORKLOAD3);

		exit(0);
	}
	kill(pid3, SIGSTOP);
	gettimeofday(&start_time3, NULL);

	pid4 = fork();
    //gettimeofday(&start_time4, NULL);

	if (pid4 == 0){

		myfunction(WORKLOAD4);

		exit(0);
	}
	kill(pid4, SIGSTOP);
	gettimeofday(&start_time4, NULL);

	/************************************************************************************************ 
		At this point, all  newly-created child processes are stopped, and ready for scheduling.
	*************************************************************************************************/



	/************************************************************************************************
		- Scheduling code starts here
		- Below is a sample schedule. (which scheduling algorithm is this?)
		- For the assignment purposes, you have to replace this part with the other scheduling methods 
		to be implemented.
	************************************************************************************************/

    running1 = 1;
    running2 = 1;
    running3 = 1;
    running4 = 1;

if (running1 > 0) {
    // gettimeofday(&start_time1, NULL);
    kill(pid1, SIGCONT);
    waitpid(pid1, &running1, 0); // Wait for the process to finish
    gettimeofday(&end_time1, NULL);
}

if (running2 > 0) {
    // gettimeofday(&start_time2, NULL);
    kill(pid2, SIGCONT);
    waitpid(pid2, &running2, 0); // Wait for the process to finish
    gettimeofday(&end_time2, NULL);
}

if (running3 > 0) {
    // gettimeofday(&start_time3, NULL);
    kill(pid3, SIGCONT);
    waitpid(pid3, &running3, 0); // Wait for the process to finish
    gettimeofday(&end_time3, NULL);
}

if (running4 > 0) {
    // gettimeofday(&start_time4, NULL);
    kill(pid4, SIGCONT);
    waitpid(pid4, &running4, 0); // Wait for the process to finish
    gettimeofday(&end_time4, NULL);
}

    double response_time1 = (double)(end_time1.tv_sec - start_time1.tv_sec) + (double)(end_time1.tv_usec - start_time1.tv_usec) / 1000000.0;
    double response_time2 = (double)(end_time2.tv_sec - start_time2.tv_sec) + (double)(end_time2.tv_usec - start_time2.tv_usec) / 1000000.0;
    double response_time3 = (double)(end_time3.tv_sec - start_time3.tv_sec) + (double)(end_time3.tv_usec - start_time3.tv_usec) / 1000000.0;
    double response_time4 = (double)(end_time4.tv_sec - start_time4.tv_sec) + (double)(end_time4.tv_usec - start_time4.tv_usec) / 1000000.0;

    // Calculate the average response time
    double average_response_time = (response_time1 + response_time2 + response_time3 + response_time4) / 4.0;

    //printf("First Come First Serve (FCFS)\n");
    printf("%.9f\n", response_time1);
    printf("%.9f\n", response_time2);
    printf("%.9f\n", response_time3);
    printf("%.9f\n", response_time4);
    printf("%.9f\n", average_response_time);

	/************************************************************************************************
		- Scheduling code ends here
	************************************************************************************************/

	return 0;
}