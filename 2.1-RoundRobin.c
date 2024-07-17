//cs159
#include <stdio.h>

#define MAX_PROC 10

void rr(int arr[], int bur[], int n, int tquan) {
    int rem[MAX_PROC];
    int comp[MAX_PROC] = {0};
    int turn[MAX_PROC] = {0};
    int wait[MAX_PROC] = {0};
    int curr = 0;
    int remain = n;
    float total_tat = 0, total_wt = 0;
    int completed = 0;

    for (int i = 0; i < n; i++) {
        rem[i] = bur[i];
    }

    while (completed < n) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (rem[i] > 0 && arr[i] <= curr) {
                done = 0;
                int exe_time = (rem[i] > tquan) ? tquan : rem[i];

                curr += exe_time;
                rem[i] -= exe_time;

                if (rem[i] == 0) {
                    completed++;
                    comp[i] = curr;
                    turn[i] = comp[i] - arr[i];
                    wait[i] = turn[i] - bur[i];

                    total_tat += turn[i];
                    total_wt += wait[i];
                }
            }
        }
        if (done) {
            curr++;
        }
    }

    printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               i + 1, arr[i], bur[i],
               comp[i], wait[i], turn[i]);
    }

    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);
}

int main() {
    int n;
    int arr[MAX_PROC];
    int bur[MAX_PROC];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &arr[i]);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &bur[i]);
    }

    printf("Enter value of Time Quantum: ");
    int tquan;
    scanf("%d", &tquan);

    rr(arr, bur, n, tquan);

    return 0;
}




















//simplified 

#include <stdio.h>
#include <limits.h>

void findCompletionTime(int processes[], int n, int bt[], int at[], int wt[], int tat[], int ct[], int rt[], int quantum) {
    int remaining_bt[n];
    int response[n];
    for (int i = 0; i < n; i++) {
        remaining_bt[i] = bt[i]; // Initialize remaining burst times
        response[i] = -1; // Initialize response times to -1 (indicating not started yet)
    }

    int complete = 0, currentTime = 0, t;
    float avgWT = 0, avgTAT = 0, avgRT = 0;

    while (complete != n) {
        int done = 1;

        for (int i = 0; i < n; i++) {
            if (remaining_bt[i] > 0) {
                done = 0; // There is a pending process

                if (response[i] == -1) {
                    response[i] = currentTime - at[i]; // Calculate response time for the first execution
                }

                if (remaining_bt[i] > quantum) {
                    currentTime += quantum;
                    remaining_bt[i] -= quantum;
                } else {
                    currentTime += remaining_bt[i];
                    wt[i] = currentTime - bt[i] - at[i];
                    remaining_bt[i] = 0;
                    complete++;
                    tat[i] = bt[i] + wt[i];
                    ct[i] = currentTime; // Completion time
                }
            }
        }

        if (done == 1) {
            break;
        }
    }

    // Calculate response time
    for (int i = 0; i < n; i++) {
        rt[i] = response[i];
        avgRT += rt[i];
    }

    // Calculate average WT and TAT
    for (int i = 0; i < n; i++) {
        avgWT += wt[i];
        avgTAT += tat[i];
    }

    // Print results
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\tResponse Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], at[i], bt[i], wt[i], tat[i], ct[i], rt[i]);
    }
    printf("Average turn around time = %.2f\n", avgTAT / n);
    printf("Average waiting time = %.2f\n", avgWT / n);
    printf("Average response time = %.2f\n", avgRT / n);
}

int main() {
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], burst_time[n], arrival_time[n];

    printf("Enter the arrival and burst times for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d%d", &arrival_time[i], &burst_time[i]);
        processes[i] = i + 1;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    int wt[n], tat[n], ct[n], rt[n];

    printf("\nRound Robin Scheduling:\n");
    findCompletionTime(processes, n, burst_time, arrival_time, wt, tat, ct, rt, quantum);

    return 0;
}
