#include<stdio.h>
#include<stdlib.h>

struct fcfs
 { 
  int pid;
  int btime;
  int wtime;
  int ctime;
  int ttime;
  int atime;
  };

void main(){  
int n,i,j,k;
int tottime=0;
int totwtime=0;
int count=0;
printf("Enter no of processes:");
scanf("%d",&n);

struct fcfs p[n];

for(int i=0;i<n;i++){
     p[i].pid=i+1;
     printf("Enter burst time , arrival time  of process %d:      ",p[i].pid);
     scanf("%d%d",&p[i].btime,&p[i].atime);}
     
     
     for(i=0;i<n;i++){
           for(j=0;j<n-i-1;j++){
                  if(p[j].atime>p[j+1].atime){
                          int s= p[j].pid;
                          int b=p[j].btime;
                          int a=p[j].atime;
                          p[j].pid=p[j+1].pid;
                          p[j].btime=p[j+1].btime;
                          p[j].atime=p[j+1].atime;
                          p[j+1].pid=s;
                          p[j+1].btime=b;
                          p[j+1].atime=a;}}}
     
     
int time=p[0].atime;

         
         
p[0].wtime=time;
p[0].ctime=p[0].atime+p[0].btime;
p[0].ttime=p[0].ctime-p[0].atime;
p[0].wtime=p[0].ttime-p[0].btime;
tottime+=p[0].ttime;
//totwtime+=p[0].wtime;
for(int i=1;i<n;i++){
    p[i].ctime=p[i-1].ctime+p[i].btime;

    p[i].ttime=p[i].ctime-p[i].atime;

   p[i].wtime=p[i].ttime-p[i].btime;
     tottime+=p[i].ttime;
     //totwtime+=p[i].wtime;
                
                }
for(i=0;i<n;i++){
      totwtime+=p[i].wtime;
      printf("\nTotal wait time %d",totwtime);
 }             
printf("PID\tBurst time\tArrival\tCompletion time\tWaiting time\tTurnaround Time");
for (int i=0;i<n;i++){
      printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].pid,p[i].btime,p[i].atime,p[i].ctime,p[i].wtime,p[i].ttime);
      
      }

printf("\nTotal waiting time %d",totwtime);
printf("\nAverage waiting time %f",(float)totwtime/n);
printf("\nTotal turnaround time %d",tottime);
printf("\nAverage turnaround time %f",(float)tottime/n);


}

