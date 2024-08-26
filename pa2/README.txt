In this programming assignment, we made different scheduling algorithms and compared them. 
The schedules made are shown below:

FCFS.c : First Come First Serve

    
Edit #define WORKLOAD 1 - 4 to your desired workload
Run cmd "gcc FCFS.c -o FCFS" to compile the c file
Now run cmd "./FCFS" to run the code
Output is formatted by these lines:
1: Process 1's response time
2: Process 2's response time
3: Process 3's response time
4: Process 4's response time
5: Average response time


RR.c : Round Robin

    
Edit #define WORKLOAD 1 - 4 to your desired workload
Edit #define QUANTUM 1 - 4 to your desired Quantum
Run cmd "gcc RR.c -o RR" to compile the c file
Now run cmd "./RR" to run the code
Output is formatted by these lines:
1: Process 1's response time
2: Process 2's response time
3: Process 3's response time
4: Process 4's response time
5: Average response time

SJF.c : Shortest Job First

    
Edit #define WORKLOAD 1 - 4 to your desired workload
Run cmd "gcc SJF.c -o SFJ" to compile the c file
Now run cmd "./SJF" to run the code
Output is formatted by these lines:
1: Process 1's response time
2: Process 2's response time
3: Process 3's response time
4: Process 4's response time
5: Average response time

MLFQ_v3.c : Multi-Level Feedback Queue

    
Edit #define WORKLOAD 1 - 4 to your desired workload
Edit #define QUANTUM 1 - 4 to your desired Quantum
Run cmd "gcc MLFQ_v3.c -o MLFQ" to compile the c file
Now run cmd "./MLFQ" to run the code
Output is formatted by these lines:
1: Process 1's response time
2: Process 2's response time
3: Process 3's response time
4: Process 4's response time
5: Average response time

python script files below: 

script.py : Python script to run the c file 30 amount of times


edit num_runs to however many times you want to run the c file. 
num_runs = 30 by default as that is usually the standard for minimum sample size in statistics
Edit line 12 to which compiled c file you want to run. By default it is on FCFS.
run cmd "python3 script.py" to run the script.