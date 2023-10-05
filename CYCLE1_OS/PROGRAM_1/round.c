#include <stdio.h>
int q[100],front=-1,rear=-1;
struct process
{int id,at,tt,bt,wt,rt,ct,status;
}p[20];
void enqueue(int j)
{ if(front==-1 && rear==-1)
 front++;
 rear++;
 q[rear] = j;
}
int dequeue()
{ if(front == -1)
 return -1;
 int item;
 item = q[front];
 if(front == rear)
 { front = -1;
 rear = -1; }
 else
 {front++;}
 return(item);}
void main()
{ int n,quantum,time=0,completed=0,current=0,i,dequeuedItem=-1,qExpire=0;
 float avwt=0,avtt=0;
 printf("Enter the number of processes : ");
 scanf("%d",&n);
 printf("\nEnter the AT and BT :\n");
 for(i=0;i<n;i++) //Input process details
 {
 p[i].id = i+1; p[i].status = 0;
 scanf("%d",&p[i].at);
 scanf("%d",&p[i].bt);
 p[i].rt = p[i].bt;
 }
 printf("\nEnter time quantum : ");
 scanf("%d",&quantum);
 //Waiting for first process to arrive
 while(time != p[0].at){
 time++;
 }
 enqueue(0);
 p[0].status = 1;

 while(completed<n){
 if(dequeuedItem == -1)
 {
 dequeuedItem = dequeue();
 }
 time++;
 //Loop to check for new process
 for(i=0; i<n ; i++){
 if(p[i].status == 0 && p[i].at <= time){
 enqueue(i);
 p[i].status = 1; 
 }
 }
 if(dequeuedItem !=-1){
     //1
       if(qExpire != quantum && p[dequeuedItem].rt > 0){
          p[dequeuedItem].rt--;
          qExpire++;}
       
       //2.              
       if(p[dequeuedItem].rt == 0){
              p[dequeuedItem].ct = time;
              p[dequeuedItem].tt = p[dequeuedItem].ct - p[dequeuedItem].at;
            p[dequeuedItem].wt = p[dequeuedItem].tt - p[dequeuedItem].bt;
               completed++;
           avwt += p[dequeuedItem].wt;
             avtt += p[dequeuedItem].tt;
         dequeuedItem = -1;
           qExpire = 0;
                    }
       else if(qExpire == quantum ){
          enqueue(dequeuedItem);
       dequeuedItem = -1;
              qExpire = 0;}
 }
 }
 printf("\nPROCESS ID\tARRIVAL TIME (ms)\tBURST TIME (ms)\t\tCOMPLETION TIME(ms)\tWAITING TIME (ms)\tTURNAROUND TIME (ms)\n\n");
for(i=0;i<n;i++)
{printf("%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n",p[i].id,p[i].at,p[i].bt,p[i].ct,p[i].wt,p[i].tt);
 }
 printf("\n\nAverage Waiting Time : %f",(avwt/n));
 printf("\nAverage Turn Around Time : %f\n",(avtt/n));
} 
