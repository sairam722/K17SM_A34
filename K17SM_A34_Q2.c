#include<stdio.h>
int main()
{
int i,p[10]={1,2,3,4,5,6,7,8,9,10},min,k=1,b_time=0;
int burst[10],temp,j,arr[10],waiting[10],taround[10],ta=0,sum=0;
float wavg=0,tavg=0,tsum=0,wsum=0;

 
for(i=0;i<4;i++)
{

printf("Enter the arrival time of %d process :",i+1);
scanf(" %d",&arr[i]);
printf("Enter the burst time of %d process :",i+1);
scanf(" %d",&burst[i]);
}
 
/*Sorting According to Arrival Time*/
 
for(i=0;i<4;i++)
{
for(j=0;j<4;j++)
{
if(arr[i]<arr[j])
{
temp=p[j];
p[j]=p[i];
p[i]=temp;

temp=arr[j];
arr[j]=arr[i];
arr[i]=temp;

temp=burst[j];
burst[j]=burst[i];
burst[i]=temp;
}
}
}
 
/*Arranging the table according to Burst time,
Execution time and Arrival Time
Arrival time <= Execution time
*/
 
for(j=0;j<4;j++)
{
b_time=b_time+burst[j];
min=burst[k];
for(i=k;i<4;i++)
{
if (b_time>=arr[i] && burst[i]<min)
{
temp=p[k];
p[k]=p[i];
p[i]=temp;

temp=arr[k];
arr[k]=arr[i];
arr[i]=temp;

temp=burst[k];
burst[k]=burst[i];
burst[i]=temp;
}
}
k++;
}
waiting[0]=0;
for(i=1;i<4;i++)
{
sum=sum+burst[i-1];
waiting[i]=sum-arr[i];
wsum=wsum+waiting[i];
}
 
wavg=(wsum/4);
for(i=0;i<4;i++)
{
ta=ta+burst[i];
taround[i]=ta-arr[i];
tsum=tsum+taround[i];
}
 
tavg=(tsum/4);
 

printf("\n RESULT:-");
printf("\nProcess\t Burst\t Arrival\t Waiting\t Turn-around" );
for(i=0;i<4;i++)
{
printf("\n p%d\t %d\t %d\t\t %d\t\t\t%d",p[i],burst[i],arr[i],waiting[i],taround[i]);
}
 
printf("\n\nAVERAGE WAITING TIME : %f",wavg);
printf("\nAVERAGE TURN AROUND TIME : %f",tavg);
return 0;
}
