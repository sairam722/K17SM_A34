#include<stdio.h>
int n;//Total no of processes
/*Struct contains details of a process.
p_id=process id.
arrivaltime=arrival time.
bt=burst time.
wt=waiting time.
tat=turn arround time.
st=start time.
qn=tells us that to which queue it belongs.
*/
struct info
{
	int processid;
	int arrivaltime;
	int bursttime;
	int waitingtime;
	int turnaroundtime;
	int starttime;
	int ft;
};
struct info readyq[100];//ready queue,front,rear.
int rqr=-1,rqf=-1;
//renq() will add the process to readyq
void renq(struct info x)
{
if(rqr==100)
	{
		printf("over flow\n");
	}
	else if (rqf == -1 && rqr == -1)
	{
		rqf++;
		rqr++;
		readyq[rqr]=x;
	}
	else
	{
		rqr++;
		readyq[rqr]=x;
	}
}
//rdq() will remove process from readyq
void rdq()
{
if(rqr==rqf)
	{
		printf("Under Flow\n");
	}
	else
	{
		rqf++;
	}
}
//sort() will sort the queue according to arrival time and process id.
void sort(struct info *q[])
{
	struct info temp;
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(q[j]->arrivaltime>q[j+1]->arrivaltime)
			{
				temp=*q[j];
				*q[j]=*q[j+1];
				*q[j+1]=temp;
			}
			else if(q[j]->arrivaltime==q[j+1]->arrivaltime)
			{
				if(q[j]->processid>q[j+1]->processid)
				{
					temp=*q[j];
					*q[j]=*q[j+1];
					*q[j+1]=temp;
				}
			}
		}
	}
}
//updateq() will check for the processes arrived and adds them to readyq 
void updateq(struct info p[],int x)
{
	int j;
    for(j=0;j<n;j++)
    {
        if(p[j].arrivaltime==x)
        {
            renq(p[j]);
        }
    }
}
//lrtf() returns the index of process with longest burst time left.
int lrtf()
{
	int index;
	int j=rqf;
	while(j<=rqr)
	{
		if(readyq[j].bursttime!=0)
		{
			index=j;
			break;
		}
		else
			j++;
	}
	int i;
	for(i=rqf;i<=rqr;i++)
	{
		if(readyq[i].bursttime>readyq[index].bursttime&&readyq[i].bursttime!=0)
		{
			index=i;
		}
	}
	return index;
}
//WtTat will calculates and prints the wt and tat of each process and average of wt and average of tat.
void WtTat(int chart[],struct info p[],int tt)
{
	int pid;
    int swt=0;
    int stat=0;
    float avgwt,avgtat;
    int i;
	for(i=0;i<n;i++)
	{
		int l;
		pid=p[i].processid;
		int j;
		for(j=tt-1;j>=0;j--)
		{
			if(chart[j]==pid)
			{
				l=j+1;
				break;
			}
		}
		p[i].turnaroundtime=l-p[i].arrivaltime;
		p[i].waitingtime=p[i].turnaroundtime-p[i].bursttime;
	}
	printf("\n\n");
	for(i=0;i<n;i++)
	{
		printf("pid:%d\t",p[i].processid);
		printf("Waiting Time:%d\t",p[i].waitingtime);
		printf("Turn Around Time:%d\t",p[i].turnaroundtime);
		printf("\n\n");
	}
    for(i=0;i<n;i++)
    {
        swt=swt+p[i].waitingtime;
        stat=stat+p[i].turnaroundtime;
    }
    avgwt=swt/n;
    avgtat=stat/n;
	printf("Average Waiting Time:%f\t\tAverage Turn Arround Time:%f",avgwt,avgtat);
}
//gantt() will prepares the gant chart and prints.
void gantt(struct info p[])
{
	//calculating the size of gantt chart.
    int tt = 0,i,j;
    tt += p[0].arrivaltime + p[0].bursttime;
	for (i = 1; i < n; i++) 
	{
        if (tt < p[i].arrivaltime)
            tt = p[i].arrivaltime;
        
        tt += p[i].bursttime;
    }
    printf("Gantt Chart:\n");
	int chart[tt];
    for(j=0;j<tt;j++)
        chart[tt]=-1;
    for(j=0;j<n;j++)
    {
        if(p[j].arrivaltime==0)
        {
            renq(p[j]);
        }
    }
    int qt1=0;
    int qt2=0;
    int uh=1;
	//follows round robin with quantum 6 for first 24 seconds.
    for(j=0;j<24;j++)
    {
        chart[j]=readyq[rqf].processid;
        readyq[rqf].bursttime--;
        qt1++;
        updateq(p,j+1);
        if(readyq[rqf].bursttime==0)
        {
            rdq();
            qt1=0;
        }
        else if(qt1==6)
        {
            renq(readyq[rqf]);
            rdq();
            qt1=0;
        }
    }
	//follows Round Robin with quantum 10 for next 40 seconds.
    for(j=24;j<64;j++)
    {
        chart[j]=readyq[rqf].processid;
        readyq[rqf].bursttime--;
        qt2++;
        updateq(p,j+1);
        if(readyq[rqf].bursttime==0)
        {
            rdq();
            qt2=0;
        }
        else if(qt2==10)
        {
            renq(readyq[rqf]);
            rdq();
            qt2=0;
        }
    }
	//follows LRTF for the rest.
    for(j=64;j<tt;j++)
    {
        int lindex=lrtf();
        chart[j]=readyq[lindex].processid;
        readyq[lindex].bursttime--;
    }
	//printing the gantt chart
    for(i=0;i<tt;i++)
	{
		printf("%d\t",chart[i]);
	}
    WtTat(chart,p,tt);    //for printing Wt and Tat.
}
int main()
{
    printf("Enter the total number of processes\n");
    scanf("%d",&n);
    struct info p[n],pc[n],*pc1[n];
	int i;
    for(i=0;i<n;i++)
    {
    	printf("\nEnter the process id : ");
    	scanf("%d",&p[i].processid);
    	printf("\nEnter the arrival time : ");
    	scanf("%d",&p[i].arrivaltime);
    	printf("\nEnter the burst time : ");
    	scanf("%d",&p[i].bursttime);
    }
    for(i=0;i<n;i++)
	{
		pc[i]=p[i];
        pc1[i]=&pc[i];
	}
    sort(pc1);
    gantt(pc);
    return 0;
}
