#include<stdio.h>
#include<stdlib.h>
int main()
{
int queue[20],n,head,i,j,k,seek=0,max,diff,temp,q,queue1[20],queue2[20],
temp1=0,temp2=0;
float avg;
printf("Enter the max range of disk\n");
scanf("%d",&max);
printf("Enter the initial head position\n");
scanf("%d",&head);
printf("Enter the size of queue request\n");
scanf("%d",&n);
printf("Enter the queue of disk positions to be read\n");
for(i=1;i<=n;i++) {
scanf("%d",&temp);
if(temp>=head){
queue1[temp1]=temp;
temp1++;}
else{
queue2[temp2]=temp;
temp2++; }
}
for(i=0;i<temp1-1;i++) {
for(j=i+1;j<temp1;j++){
if(queue1[i]>queue1[j]){
temp=queue1[i];
queue1[i]=queue1[j];
queue1[j]=temp; } }
}
for(i=0;i<temp2-1;i++){
for(j=i+1;j<temp2;j++){
if(queue2[i]>queue2[j]){
temp=queue2[i];
queue2[i]=queue2[j];
queue2[j]=temp; }
}
}
for(i=1,j=0;j<temp1;i++,j++)
queue[i]=queue1[j];
queue[i]=max;
queue[i+1]=0;
for(i=temp1+3,j=0;j<temp2;i++,j++)
queue[i]=queue2[j];
queue[0]=head;
for(j=0;j<=n+1;j++){
diff=abs(queue[j+1]-queue[j]);
seek+=diff;
printf(" %d -> ",queue[j]);
}
printf("\n Total seek time is %d\n",seek);
avg=seek/(float)n;
printf("Average seek time is %f\n",avg);
return 0;
}

/*OUTPUT
Enter the max range of disk
199
Enter the initial head position
53
Enter the size of queue request
8
Enter the queue of disk positions to be read
98
183
37  
122
14
124
65
67
 53 ->  65 ->  67 ->  98 ->  122 ->  124 ->  183 ->  199 ->  0 ->  14 -> 
 Total seek time is 382
Average seek time is 47.750000
*/
