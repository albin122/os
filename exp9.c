#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, f;

    printf("Enter length of reference string: ");
    scanf("%d", &n);

    printf("Enter number of frames (1-7): ");
    scanf("%d", &f);

    int pages[100], frames[10];

    printf("Enter %d page numbers (0-9):\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("\n");
    int fifoFaults = 0, index = 0;
    for (int i = 0; i < f; i++) frames[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < f; j++)
            if (frames[j] == pages[i]) found = 1;

        if (!found) {
            frames[index] = pages[i];
            index = (index + 1) % f;
            fifoFaults++;
        }
    }

    int lruFaults = 0, time[10], counter = 0;
    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                time[j] = ++counter;
                found = 1;
            }
        }

        if (!found) {
            int min = 0;
            for (int j = 1; j < f; j++)
                if (time[j] < time[min]) min = j;

            frames[min] = pages[i];
            time[min] = ++counter;
            lruFaults++;
        }
    }

    int optFaults = 0;
    for (int i = 0; i < f; i++) frames[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < f; j++)
            if (frames[j] == pages[i]) found = 1;

        if (!found) {
            int pos = -1, farthest = i + 1;

            for (int j = 0; j < f; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frames[j] == pages[k]) {
                        if (k > farthest) {
                            farthest = k;
                            pos = j;
                        }
                        break;
                    }
                }
                if (k == n) {
                    pos = j;
                    break;
                }
            }

            if (pos == -1) pos = 0;

            frames[pos] = pages[i];
            optFaults++;
        }
    }

    printf("FIFO Page Faults = %d\n", fifoFaults);
    printf("LRU Page Faults = %d\n", lruFaults);
    printf("Optimal Page Faults = %d\n", optFaults);

    return 0;
}
