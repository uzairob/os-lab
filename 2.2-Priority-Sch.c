//cs159
#include <stdio.h>

#define MAX_PROC 10

struct Proc {
    int pid, at, bt, pri, ct, tat, wt, rt, exec;
};

void prio_non_preemptive(struct Proc proc[], int n) {
    int curr_time = 0, total_ct = 0;

    while (1) {
        int high_prio = 9999, high_prio_idx = -1;

       
        for (int i = 0; i < n; i++) {
            if (proc[i].at <= curr_time && proc[i].exec == 0) {
                if (proc[i].pri < high_prio) {
                    high_prio = proc[i].pri;
                    high_prio_idx = i;
                }
            }
        }

       
        if (high_prio_idx == -1) {
            break;
        }

        
        proc[high_prio_idx].ct = curr_time + proc[high_prio_idx].bt;
        proc[high_prio_idx].tat = proc[high_prio_idx].ct - proc[high_prio_idx].at;
        proc[high_prio_idx].wt = proc[high_prio_idx].tat - proc[high_prio_idx].bt;
        proc[high_prio_idx].rt = curr_time - proc[high_prio_idx].at;
        if (proc[high_prio_idx].wt < 0)
            proc[high_prio_idx].wt = 0;
        proc[high_prio_idx].exec = 1;
        total_ct = proc[high_prio_idx].ct;
        curr_time = total_ct;
    }
}

int main() {
    int n;
    struct Proc proc[MAX_PROC];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

   
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &proc[i].at);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &proc[i].bt);
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &proc[i].pri);
        proc[i].exec = 0;
    }

    prio_non_preemptive(proc, n);

    
    printf("PID\tAT\tBT\tPri\tCT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               proc[i].pid, proc[i].at, proc[i].bt, proc[i].pri,
               proc[i].ct, proc[i].wt, proc[i].tat, proc[i].rt);
    }

    return 0;
}


//preemptive

#include <stdio.h>
#include <limits.h>

void findCompletionTimePreemptive(int processes[], int n, int bt[], int at[], int pri[], int wt[], int tat[], int ct[], int rt[]) {
    int remaining_bt[n];
    int response[n];
    for (int i = 0; i < n; i++) {
        remaining_bt[i] = bt[i]; // Initialize remaining burst times
        response[i] = -1; // Initialize response times to -1 (indicating not started yet)
    }

    int complete = 0, currentTime = 0, minm = INT_MAX;
    int shortest = 0, finishTime;
    int check = 0;
    float avgWT = 0, avgTAT = 0, avgRT = 0;

    while (complete != n) {
        int maxPriority = INT_MAX;
        for (int j = 0; j < n; j++) {
            if ((at[j] <= currentTime) && (pri[j] < maxPriority) && remaining_bt[j] > 0) {
                maxPriority = pri[j];
                shortest = j;
                check = 1;
            }
        }

        if (check == 0) {
            currentTime++;
            continue;
        }

        if (response[shortest] == -1) {
            response[shortest] = currentTime - at[shortest];
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
        avgRT += response[i];
    }

    printf("Process\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\tCompletion Time\tResponse Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], at[i], bt[i], pri[i], wt[i], tat[i], ct[i], response[i]);
    }
    printf("Average turn around time = %.2f\n", avgTAT / n);
    printf("Average waiting time = %.2f\n", avgWT / n);
    printf("Average response time = %.2f\n", avgRT / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], burst_time[n], arrival_time[n], priority[n];

    printf("Enter the arrival time, burst time, and priority for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d%d%d", &arrival_time[i], &burst_time[i], &priority[i]);
        processes[i] = i + 1;
    }

    int wt[n], tat[n], ct[n], rt[n];

    printf("\nPreemptive Priority Scheduling:\n");
    findCompletionTimePreemptive(processes, n, burst_time, arrival_time, priority, wt, tat, ct, rt);

    return 0;
}
