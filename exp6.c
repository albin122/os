#include <stdio.h>
#include <limits.h>

struct process {
    int pid;
    int at;   // Arrival Time
    int bt;   // Burst Time
    int rt;   // Remaining Time (for RR)
    int pr;   // Priority
    int ct;   // Completion Time
    int wt;   // Waiting Time
    int tat;  // Turnaround Time
};

// Function Declarations
void fcfs(int n, struct process p[]);
void sjf(int n, struct process p[]);
void priority_non_preemptive(int n, struct process p[]);
void round_robin(int n, struct process p[], int quantum);

//////////////////////////////////////////////////////
// FCFS Scheduling
//////////////////////////////////////////////////////
void fcfs(int n, struct process p[]) {
    int current_time = 0;
    float total_wt = 0.0;

    // Sort by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                struct process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (current_time < p[i].at)
            current_time = p[i].at;

        p[i].ct = current_time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        current_time = p[i].ct;
        total_wt += p[i].wt;
    }

    printf("\nFCFS Scheduling:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }
    printf("Average Waiting Time = %.2f\n", total_wt / n);
}

//////////////////////////////////////////////////////
// Non-Preemptive SJF
//////////////////////////////////////////////////////
void sjf(int n, struct process p[]) {
    int current_time = 0, completed = 0;
    float total_wt = 0.0;
    int visited[10] = {0};

    while (completed < n) {
        int min_bt = INT_MAX;
        int selected = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && p[i].at <= current_time && p[i].bt < min_bt) {
                min_bt = p[i].bt;
                selected = i;
            }
        }

        if (selected == -1) {
            current_time++;
            continue;
        }

        p[selected].ct = current_time + p[selected].bt;
        p[selected].tat = p[selected].ct - p[selected].at;
        p[selected].wt = p[selected].tat - p[selected].bt;

        total_wt += p[selected].wt;
        current_time = p[selected].ct;
        visited[selected] = 1;
        completed++;
    }

    printf("\nSJF Scheduling (Non-Preemptive):\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("Average Waiting Time = %.2f\n", total_wt / n);
}

//////////////////////////////////////////////////////
// Non-Preemptive Priority
//////////////////////////////////////////////////////
void priority_non_preemptive(int n, struct process p[]) {
    int current_time = 0, completed = 0;
    float total_wt = 0.0;
    int visited[10] = {0};

    while (completed < n) {
        int max_pr = -1;
        int selected = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && p[i].at <= current_time && p[i].pr > max_pr) {
                max_pr = p[i].pr;
                selected = i;
            }
        }

        if (selected == -1) {
            current_time++;
            continue;
        }

        p[selected].ct = current_time + p[selected].bt;
        p[selected].tat = p[selected].ct - p[selected].at;
        p[selected].wt = p[selected].tat - p[selected].bt;

        total_wt += p[selected].wt;
        current_time = p[selected].ct;
        visited[selected] = 1;
        completed++;
    }

    printf("\nNon-Preemptive Priority Scheduling:\n");
    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("Average Waiting Time = %.2f\n", total_wt / n);
}

//////////////////////////////////////////////////////
// Round Robin
//////////////////////////////////////////////////////
void round_robin(int n, struct process p[], int quantum) {
    int t = 0, completed = 0;
    float total_wt = 0.0;

    for (int i = 0; i < n; i++)
        p[i].rt = p[i].bt;

    while (completed < n) {
        int idle = 1;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= t && p[i].rt > 0) {
                idle = 0;

                if (p[i].rt > quantum) {
                    t += quantum;
                    p[i].rt -= quantum;
                } else {
                    t += p[i].rt;
                    p[i].rt = 0;

                    p[i].ct = t;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;

                    total_wt += p[i].wt;
                    completed++;
                }
            }
        }

        if (idle)
            t++;
    }

    printf("\nRound Robin Scheduling (Quantum = %d):\n", quantum);
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("Average Waiting Time = %.2f\n", total_wt / n);
}

//////////////////////////////////////////////////////
// Main Function
//////////////////////////////////////////////////////
int main() {
    int n, choice, quantum = 3;
    struct process p[10], p_copy[10];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("Enter arrival time of P%d: ", p[i].pid);
        scanf("%d", &p[i].at);

        printf("Enter burst time of P%d: ", p[i].pid);
        scanf("%d", &p[i].bt);

        printf("Enter priority of P%d: ", p[i].pid);
        scanf("%d", &p[i].pr);
    }

    while (1) {
        for (int i = 0; i < n; i++)
            p_copy[i] = p[i];

        printf("\n--- Scheduling Menu ---\n");
        printf("1. FCFS\n2. SJF\n3. Non-Preemptive Priority\n4. Round Robin\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: fcfs(n, p_copy); break;
            case 2: sjf(n, p_copy); break;
            case 3: priority_non_preemptive(n, p_copy); break;
            case 4: round_robin(n, p_copy, quantum); break;
            case 5: return 0;
            default: printf("Invalid choice!\n");
        }
    }
}
