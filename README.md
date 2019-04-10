# K17SM_A34
# OS_Project
# Q1: Ques. 2. Considering the arrival time and burst time requirement of the process the scheduler schedules the processes by #interrupting the processor after every 6 units of time and does consider the completion of the process in this iteration. The scheduler #than checks for the number of process waiting for the processor and allots the processor to the process but interrupting the processor #every 10 unit of time and considers the completion of the processes in this iteration. The scheduler checks the number of processes #waiting in the queue for the processor after the second iteration and gives the processor to the process which needs more time to #complete than the other processes to go in the terminated state.
#The inputs for the number of requirements, arrival time and burst time should be provided by the user.
#Consider the following units for reference.
#Process    Arrival time    Burst time
#P1   		 0    		20
#P2   		 5    		36
#P3    		13    		19
#P4    		26    		42
#Develop a scheduler which submits the processes to the processor in the defined scenario, and compute the scheduler performance by #providing the waiting time for process, turnaround time for process and average waiting time and turnaround time.

#Q2: .  Consider a scheduling approach which is non pre-emptive similar to shortest job next in nature. The priority of each job is #dependent on its estimated run time, and also the amount of time it has spent waiting. Jobs gain higher priority the longer they wait, #which prevents indefinite postponement. The jobs that have spent a long time waiting compete against those estimated to have short run #times. The priority can be computed as :
#Priority = 1+ Waiting time / Estimated run time
#Using the data given below compute the waiting time and turnaround time for each process and average waiting time and average turnaround #time.
#
#Process	Arrival time	Burst time
#P1	0	20
#P2	5	36
#P3	13	19
#P4	17	42
