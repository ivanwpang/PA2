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

#define QUANTUM1 5000
#define QUANTUM2 5000
#define QUANTUM3 5000
#define QUANTUM4 5000

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

	struct timeval startTime1, endTime1;
    struct timeval startTime2, endTime2;
    struct timeval startTime3, endTime3;
    struct timeval startTime4, endTime4;
	double time1,time2,time3,time4;

	pid1 = fork();
    gettimeofday(&startTime1, NULL);

	if (pid1 == 0){

		myfunction(WORKLOAD1);

		exit(0);
	}
	kill(pid1, SIGSTOP);

	pid2 = fork();
	gettimeofday(&startTime2, NULL);

	if (pid2 == 0){

		myfunction(WORKLOAD2);

		exit(0);
	}
	kill(pid2, SIGSTOP);

	pid3 = fork();
	gettimeofday(&startTime3, NULL);

	if (pid3 == 0){

		myfunction(WORKLOAD3);

		exit(0);
	}
	kill(pid3, SIGSTOP);

	pid4 = fork();
	gettimeofday(&startTime4, NULL);

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

	running1 = 1;
	running2 = 1;
	running3 = 1;
	running4 = 1;


	while (running1 > 0 || running2 > 0 || running3 > 0 || running4 > 0)
	{
		if (running1 > 0){
			gettimeofday(&endTime1, NULL);
			kill(pid1, SIGCONT);
			usleep(QUANTUM1);
			kill(pid1, SIGSTOP);
		}
		if (running2 > 0){
			gettimeofday(&endTime2, NULL);
			kill(pid2, SIGCONT);
			usleep(QUANTUM2);
			kill(pid2, SIGSTOP);
		}
		if (running3 > 0){
			gettimeofday(&endTime3, NULL);
			kill(pid3, SIGCONT);
			usleep(QUANTUM3);
			kill(pid3, SIGSTOP);
		}
		if (running4 > 0){
			gettimeofday(&endTime4, NULL);
			kill(pid4, SIGCONT);
			usleep(QUANTUM4);
			kill(pid4, SIGSTOP);
		}
		waitpid(pid1, &running1, WNOHANG);
		waitpid(pid2, &running2, WNOHANG);
		waitpid(pid3, &running3, WNOHANG);
		waitpid(pid4, &running4, WNOHANG);
		
	}

	/************************************************************************************************
		- Scheduling code ends here
	************************************************************************************************/

	time1 = (endTime1.tv_sec - startTime1.tv_sec) + (endTime1.tv_usec - startTime1.tv_usec) / 1000000.0;
    time2 = (endTime2.tv_sec - startTime2.tv_sec) + (endTime2.tv_usec - startTime2.tv_usec) / 1000000.0;
    time3 = (endTime3.tv_sec - startTime3.tv_sec) + (endTime3.tv_usec - startTime3.tv_usec) / 1000000.0;
    time4 = (endTime4.tv_sec - startTime4.tv_sec) + (endTime4.tv_usec - startTime4.tv_usec) / 1000000.0;
	double avgResponse = (time1+time2+time3+time4)/4;

	printf("Time Quantum: %d\n", QUANTUM1);
	printf("response time for pid=1 is %.9f seconds\n", time1);
	printf("response time for pid=2 is %.9f seconds\n", time2);
	printf("response time for pid=3 is %.9f seconds\n", time3);
	printf("response time for pid=4 is %.9f seconds\n", time4);
	printf("%.9f\n", avgResponse);

	return 0;
}