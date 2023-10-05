#include<stdio.h>
void print(int frameno,int frame[]){
int j;
for(j=0;j<frameno;j++)
printf("%d\t",frame[j]);printf("\n"); }
int main(){
int i,j,k,n,page[50],frameno,frame[10],move=0,flag,count=0,count1[10]={0},
repindex,leastcount;
printf("Enter the number of pages\n");scanf("%d",&n);
printf("Enter the page reference numbers\n");
for(i=0;i<n;i++)
scanf("%d",&page[i]);
printf("Enter the number of frames\n");scanf("%d",&frameno);
for(i=0;i<frameno;i++)
frame[i]=-1;
printf("Page reference string\tFrames\n");
for(i=0;i<n;i++)
{
printf("%d\t\t\t",page[i]);flag=0;
for(j=0;j<frameno;j++){
if(page[i]==frame[j]){
flag=1;count1[j]++;
printf("No replacement\n");break; }}
if(flag==0&&count<frameno){
frame[move]=page[i];
count1[move]=1;
move=(move+1)%frameno;
count++;
print(frameno,frame);}
else if(flag==0){
repindex=0;
leastcount=count1[0];
for(j=1;j<frameno;j++){
if(count1[j]<leastcount){
repindex=j;
leastcount=count1[j];
}
}
frame[repindex]=page[i];
count1[repindex]=1;count++;print(frameno,frame);
}}
printf("Number of page faults is %d\n",count);
return 0;}

/*OUTPUT
Enter the number of pages
15
Enter the page reference numbers
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2
Enter the number of frames
3
Page reference string	Frames
7			7	-1	-1	
0			7	0	-1	
1			7	0	1	
2			2	0	1	
0			No replacement
3			3	0	1	
0			No replacement
4			4	0	1	
2			2	0	1	
3			3	0	1	
0			No replacement
3			No replacement
2			3	0	2	
1			3	0	1	
2			3	0	2	
Number of page faults is 11
*/
