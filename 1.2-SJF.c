//cs159
#include <stdio.h>

#define MAX_PROCESS 10

typedef struct {
    int pid;
    int arr;
    int burst;
    int comp;
    int turn;
    int wait;
    int processed;
} Proc;

void sjf_np(Proc procs[], int n) {
    int curr_time = 0;
    int total_comp_time = 0;
    int total_wait_time = 0;
    int total_turnaround_time = 0;

    while (1) {
        int shortest_job = -1;
        int shortest_burst = 9999;

        for (int i = 0; i < n; i++) {
            if (procs[i].arr <= curr_time && procs[i].processed == 0) {
                if (procs[i].burst < shortest_burst) {
                    shortest_burst = procs[i].burst;
                    shortest_job = i;
                }
            }
        }

        if (shortest_job == -1) {
            break;
        }

        procs[shortest_job].comp = curr_time + procs[shortest_job].burst;
        procs[shortest_job].turn = procs[shortest_job].comp - procs[shortest_job].arr;
        procs[shortest_job].wait = procs[shortest_job].turn - procs[shortest_job].burst;
        if (procs[shortest_job].wait < 0)
            procs[shortest_job].wait = 0;

        total_comp_time += procs[shortest_job].comp;
        total_wait_time += procs[shortest_job].wait;
        total_turnaround_time += procs[shortest_job].turn;

        procs[shortest_job].processed = 1;
        curr_time = procs[shortest_job].comp;
    }
 
    double avg_turnaround_time = (double)total_turnaround_time / n;
    double avg_waiting_time = (double)total_wait_time / n;

    printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               procs[i].pid, procs[i].arr, procs[i].burst,
               procs[i].comp, procs[i].wait, procs[i].turn);
    }

    
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
}

int main() {
    int n;
    Proc procs[MAX_PROCESS];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        procs[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &procs[i].arr);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &procs[i].burst);
        procs[i].processed = 0;
    }

    sjf_np(procs, n);

    printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               procs[i].pid, procs[i].arr, procs[i].burst,
               procs[i].comp, procs[i].wait, procs[i].turn);
    }

    return 0;
}





///simplified

#include <stdio.h>

// Function to find the completion time, waiting time, and turnaround time for each process
void findCompletionTime(int processes[], int n, int bt[], int at[], int wt[], int tat[], int ct[]) {
    int currentTime = 0;
    int completion[n];
    float avgTAT = 0.0;
    float avgWT = 0.0;

    // Initialize the completion array with -1 indicating that no process is completed initially
    for (int i = 0; i < n; i++)
        completion[i] = -1;

    // Loop to find completion time for each process
    for (int i = 0; i < n; i++) {
        int minIndex = -1, minTime = 999999;

        // Find the process with the minimum burst time that is not yet completed and has arrived
        for (int j = 0; j < n; j++) {
            if (bt[j] < minTime && completion[j] == -1 && at[j] <= currentTime) {
                minIndex = j;
                minTime = bt[j];
            }
        }

        // If no process has arrived at the current time, increment the time
        if (minIndex == -1) {
            currentTime++;
            i--;
            continue;
        }

        // Calculate completion time for the selected process
        completion[minIndex] = currentTime + bt[minIndex];

        // Calculate waiting time and turnaround time for the selected process
        wt[minIndex] = currentTime - at[minIndex];
        tat[minIndex] = wt[minIndex] + bt[minIndex];
        avgTAT += tat[minIndex];
        avgWT += wt[minIndex];

        // Update the current time to the completion time of the selected process
        currentTime = completion[minIndex];
    }

    // Print the results
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        ct[i] = completion[i];
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

    // Input arrival time and burst time for each process
    printf("Enter the arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Arrival time and Burst time for process %d: ", i + 1);
        scanf("%d%d", &arrival_time[i], &burst_time[i]);
        processes[i] = i + 1;
    }

    int wt[n], tat[n], ct[n];

    // Call the function to find completion time, waiting time, and turnaround time
    printf("\nSJF Scheduling:\n");
    findCompletionTime(processes, n, burst_time, arrival_time, wt, tat, ct);

    return 0;
}
