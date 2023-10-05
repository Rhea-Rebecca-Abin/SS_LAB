#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 20

struct sjf {
    int pid,
    atime,
    btime,
    ctime,
    ttime,
    wtime,
    temp_btime;
};

int main() {
    int n, i, t, count = 0, tottime = 0, totwtime = 0;
    printf("Enter the number of processes:");
    scanf("%d", &n);
    struct sjf p[n];
    printf("\nEnter arrival and burst time:\n");

    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        scanf("%d %d", &p[i].atime, &p[i].btime);
        p[i].temp_btime = p[i].btime;
    }

    for (t = 0; count != n;) {
        int shortest_job = -1;
        for (i = 0; i < n; i++) {
            if (p[i].atime <= t && p[i].btime > 0) {
                if (shortest_job == -1 || p[i].btime < p[shortest_job].btime) {
                    shortest_job = i;
                }
            }
        }

        if (shortest_job == -1) {
            t++;
            continue;
        }

        t += p[shortest_job].temp_btime;
        p[shortest_job].ctime = t;
        p[shortest_job].ttime = t - p[shortest_job].atime;
        p[shortest_job].wtime = p[shortest_job].ttime - p[shortest_job].temp_btime;

        p[shortest_job].btime = 0;
        tottime += p[shortest_job].ttime;
        totwtime += p[shortest_job].wtime;
        count++;
    }

    printf("\nPID\tArrival time\tBurst time\tWaiting time\tTurnaround Time");
    for (i = 0; i < n; i++) {
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].atime, p[i].temp_btime, p[i].wtime, p[i].ttime);
    }

    printf("\nTotal waiting time: %d", totwtime);
    printf("\nAverage waiting time: %f", (float)totwtime / n);
    printf("\nTotal turnaround time: %d", tottime);
    printf("\nAverage turnaround time: %f\n", (float)tottime / n);

    return 0;
}
