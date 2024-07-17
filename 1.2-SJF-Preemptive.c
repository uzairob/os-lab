#include <stdio.h>
#include <limits.h>

void findCompletionTime(int processes[], int n, int bt[], int at[], int wt[], int tat[], int ct[]) {
    int remaining_bt[n];
    for (int i = 0; i < n; i++)
        remaining_bt[i] = bt[i];

    int complete = 0, currentTime = 0, minm = INT_MAX;
    int shortest = 0, finishTime;
    int check = 0;
    float avgWT = 0, avgTAT = 0;

    while (complete != n) {
        for (int j = 0; j < n; j++) {
            if ((at[j] <= currentTime) && (remaining_bt[j] < minm) && remaining_bt[j] > 0) {
                minm = remaining_bt[j];
                shortest = j;
                check = 1;
            }
        }

        if (check == 0) {
            currentTime++;
            continue;
        }

        remaining_bt[shortest]--;

        minm = remaining_bt[shortest];
        if (minm == 0)
            minm = INT_MAX;

        if (remaining_bt[shortest] == 0) {
            complete++;
            check = 0;

            finishTime = currentTime + 1;

            wt[shortest] = finishTime - bt[shortest] - at[shortest];
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        currentTime++;
    }

    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];

    for (int i = 0; i < n; i++) {
        ct[i] = at[i] + tat[i];
        avgWT += wt[i];
        avgTAT += tat[i];
    }

    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], at[i], bt[i], wt[i], tat[i], ct[i]);
    }
    printf("Average turn around time = %f\n", avgTAT / n);
    printf("Average waiting time = %f\n", avgWT / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n];
    int burst_time[n];
    int arrival_time[n];

    printf("Enter the arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Arrival time and Burst time for process %d: ", i + 1);
        scanf("%d%d", &arrival_time[i], &burst_time[i]);
        processes[i] = i + 1;
    }

    int wt[n], tat[n], ct[n];

    printf("\nSRTF Scheduling:\n");
    findCompletionTime(processes, n, burst_time, arrival_time, wt, tat, ct);

    return 0;
}

