#include <stdio.h>
#define MAX 20
#define Q 3

int main() {
    int n, i, j, t;
    int pid[MAX], at[MAX], bt[MAX], pr[MAX];
    int ct[MAX], tat[MAX], wt[MAX], rt[MAX];
    float avg;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input
    for (i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("\nProcess %d\n", pid[i]);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        printf("Priority: ");
        scanf("%d", &pr[i]);
    }

    // Sort by Arrival Time (Important for FCFS)
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (at[i] > at[j]) {
                int temp;
                temp = at[i]; at[i] = at[j]; at[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                temp = pr[i]; pr[i] = pr[j]; pr[j] = temp;
                temp = pid[i]; pid[i] = pid[j]; pid[j] = temp;
            }
        }
    }

    // ---------------- FCFS ----------------
    t = 0; avg = 0;
    printf("\n===== FCFS Scheduling =====\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    for (i = 0; i < n; i++) {
        if (t < at[i])
            t = at[i];

        ct[i] = t + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avg += wt[i];
        t = ct[i];

        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    float fcfs_avg = avg / n;
    printf("Average Waiting Time (FCFS) = %.2f\n", fcfs_avg);


    // ---------------- SJF (Non-Preemptive) ----------------
    int done[MAX] = {0}, count = 0;
    t = 0; avg = 0;

    printf("\n===== SJF (Non-Preemptive) =====\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    while (count < n) {
        int idx = -1, min = 9999;

        for (i = 0; i < n; i++) {
            if (!done[i] && at[i] <= t && bt[i] < min) {
                min = bt[i];
                idx = i;
            }
        }

        if (idx == -1) {
            t++; // CPU idle
        } else {
            ct[idx] = t + bt[idx];
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            avg += wt[idx];

            t = ct[idx];
            done[idx] = 1;
            count++;
        }
    }

    for (i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);

    float sjf_avg = avg / n;
    printf("Average Waiting Time (SJF) = %.2f\n", sjf_avg);


    // ---------------- Priority (Non-Preemptive) ----------------
    for (i = 0; i < n; i++) done[i] = 0;
    count = 0; t = 0; avg = 0;

    printf("\n===== Priority (Non-Preemptive) =====\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    while (count < n) {
        int idx = -1, high = -1;

        for (i = 0; i < n; i++) {
            if (!done[i] && at[i] <= t && pr[i] > high) {
                high = pr[i];
                idx = i;
            }
        }

        if (idx == -1) {
            t++; // CPU idle
        } else {
            ct[idx] = t + bt[idx];
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            avg += wt[idx];

            t = ct[idx];
            done[idx] = 1;
            count++;
        }
    }

    for (i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);

    float priority_avg = avg / n;
    printf("Average Waiting Time (Priority) = %.2f\n", priority_avg);


    // ---------------- Round Robin ----------------
    for (i = 0; i < n; i++)
        rt[i] = bt[i];

    t = 0; count = 0; avg = 0;

    printf("\n===== Round Robin (Quantum = 3) =====\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    while (count < n) {
        int idle = 1;

        for (i = 0; i < n; i++) {
            if (rt[i] > 0 && at[i] <= t) {
                idle = 0;

                if (rt[i] > Q) {
                    t += Q;
                    rt[i] -= Q;
                } else {
                    t += rt[i];
                    ct[i] = t;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];
                    avg += wt[i];
                    rt[i] = 0;
                    count++;
                }
            }
        }

        if (idle)
            t++;
    }

    for (i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);

    float rr_avg = avg / n;
    printf("Average Waiting Time (RR) = %.2f\n", rr_avg);


    // --------- Find Minimum ---------
    float min_avg = fcfs_avg;
    char *alg = "FCFS";

    if (sjf_avg < min_avg) {
        min_avg = sjf_avg;
        alg = "SJF (Non-Preemptive)";
    }
    if (priority_avg < min_avg) {
        min_avg = priority_avg;
        alg = "Priority (Non-Preemptive)";
    }
    if (rr_avg < min_avg) {
        min_avg = rr_avg;
        alg = "Round Robin (Q=3)";
    }

    printf("\nAlgorithm with Minimum Average Waiting Time: %s (%.2f)\n",
           alg, min_avg);

    return 0;
}
