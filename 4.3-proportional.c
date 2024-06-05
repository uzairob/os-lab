//cs159
#include<stdio.h>
#include<stdlib.h>

// Function to sort processes by burst time
void sort_by_burst(int proc[], int burst[], int tickets[], int remaining[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (burst[j] > burst[j + 1]) {
                // Swap process IDs
                int temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;

                // Swap burst times
                temp = burst[j];
                burst[j] = burst[j + 1];
                burst[j + 1] = temp;

                // Swap tickets
                temp = tickets[j];
                tickets[j] = tickets[j + 1];
                tickets[j + 1] = temp;

                // Swap remaining burst times
                temp = remaining[j];
                remaining[j] = remaining[j + 1];
                remaining[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int proc[n], burst[n], tickets[n], remaining[n];
    int total_tickets = 0;

    printf("Enter the CPU burst times and number of tickets for each process:\n");
    for (int i = 0; i < n; i++) {
        proc[i] = i + 1;  // Process IDs
        printf("Process %d burst time: ", i + 1);
        scanf("%d", &burst[i]);
        printf("Process %d tickets: ", i + 1);
        scanf("%d", &tickets[i]);
        remaining[i] = burst[i];
        total_tickets += tickets[i];
    }

    sort_by_burst(proc, burst, tickets, remaining, n);

    printf("\nProportional Share Scheduling (Lottery Scheduling):\n");
    printf("PID\t Burst\tTickets\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t %d\t %d\n", proc[i], burst[i], tickets[i]);
    }

    int time = 0;
    while (1) {
        int active_processes = 0;
        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0) {
                active_processes++;
            }
        }

        if (active_processes == 0) {
            break;
        }

        int winning_ticket = rand() % total_tickets;
        int cumulative_tickets = 0;
        int selected_process = -1;

        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0) {
                cumulative_tickets += tickets[i];
                if (winning_ticket < cumulative_tickets) {
                    selected_process = i;
                    break;
                }
            }
        }

        if (selected_process != -1) {
            printf("%dms: Process %d is running.\n", time, proc[selected_process]);
            remaining[selected_process]--;
        } else {
            printf("%dms: CPU is idle.\n", time);
        }

        time++;
    }

    printf("Scheduling completed.\n");

    return 0;
}

