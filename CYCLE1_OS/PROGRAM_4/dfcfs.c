#include <stdio.h>
#include <math.h>

int size = 8;

void FCFS(int arr[],int head)
{
	int seek_count = 0;
	int cur_track, distance;

	for(int i=0;i<size;i++)
	{
		cur_track = arr[i];
	
		// calculate absolute distance
		distance = fabs(head - cur_track);
	
		// increase the total count
		seek_count += distance;
	
		// accessed track is now new head
		head = cur_track;
	}

	printf("Total number of seek operations: %d\n",seek_count);
	
	// Seek sequence would be the same
	// as request array sequence
	printf("Seek Sequence is\n");

	for (int i = 0; i < size; i++) {
		printf("%d\n",arr[i]);
	}
}

//Driver code
int main()
{
	// request array
	int n,i,head;
	printf("\nEnter no of requests:");
	scanf("%d",&n);
	int arr[n];
	printf("\nEnter requests:");
	
	for(i=0;i<n;i++){
	     scanf("%d",&arr[i]);
	     }
	printf("\nEnter head position :");
	scanf("%d",&head);
	
	
	
	FCFS(arr,head);

	return 0;
}

/*OUTPUT
Enter no of requests:8

Enter requests:98
183
37
122
14
124
65
67

Enter head position :53
Total number of seek operations: 640
Seek Sequence is
98
183
37
122
14
124
65
67
*/
