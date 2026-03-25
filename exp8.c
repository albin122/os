#include <stdio.h>

int main() {
    int P, R;

    // Input number of processes and resources
    printf("Enter number of processes: ");
    scanf("%d", &P);

    printf("Enter number of resources: ");
    scanf("%d", &R);

    int allocation[P][R], max[P][R], need[P][R];
    int available[R], work[R];
    int finish[P], safeSeq[P];

    int i, j, k, count = 0;

    // Input Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < P; i++) {
        for(j = 0; j < R; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input Max Matrix
    printf("\nEnter Max Matrix:\n");
    for(i = 0; i < P; i++) {
        for(j = 0; j < R; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input Available Resources
    printf("\nEnter Available Resources:\n");
    for(i = 0; i < R; i++) {
        scanf("%d", &available[i]);
    }

    // Calculate Need Matrix
    for(i = 0; i < P; i++) {
        for(j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Initialize finish = 0
    for(i = 0; i < P; i++) {
        finish[i] = 0;
    }

    // Copy available to work
    for(i = 0; i < R; i++) {
        work[i] = available[i];
    }

    // Banker's Algorithm
    while(count < P) {
        int found = 0;

        for(i = 0; i < P; i++) {
            if(finish[i] == 0) {

                for(j = 0; j < R; j++) {
                    if(need[i][j] > work[j])
                        break;
                }

                // If all needs can be satisfied
                if(j == R) {
                    for(k = 0; k < R; k++) {
                        work[k] += allocation[i][k];
                    }

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0) {
            printf("\nSystem is NOT in a safe state.\n");
            return 0;
        }
    }

    // Output Safe Sequence
    printf("\nSystem is in a SAFE state.\n");
    printf("Safe sequence: ");

    for(i = 0; i < P; i++) {
        printf("P%d ", safeSeq[i]);
    }

    printf("\n");

    return 0;
}
