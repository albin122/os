#include <stdio.h>
#include <stdlib.h>

int n, head, req[100], dir;

void sort(int arr[], int n) {
    for(int i = 0; i < n - 1; i++)
        for(int j = i + 1; j < n; j++)
            if(arr[i] > arr[j]) { int t = arr[i]; arr[i] = arr[j]; arr[j] = t; }
}

void SSTF() {
    int visited[100] = {0}, total = 0, pos = head;
    printf("\nSeek Sequence: %d", pos);

    for(int i = 0; i < n; i++) {
        int min = 9999, index = -1;
        for(int j = 0; j < n; j++)
            if(!visited[j] && abs(pos - req[j]) < min) { min = abs(pos - req[j]); index = j; }
        visited[index] = 1;
        total += min;
        pos = req[index];
        printf(" -> %d", pos);
    }
    printf("\nTotal Seek Time = %d\n", total);
}

void LOOK() {
    int left[100], right[100], l = 0, r = 0, total = 0, pos = head;
    for(int i = 0; i < n; i++) {
        if(req[i] < head)
            left[l++] = req[i];
        else
            right[r++] = req[i];
    }
    sort(left, l); sort(right, r);

    printf("\nSeek Sequence: %d", pos);
    if(dir == 2) {
        for(int i = 0; i < r; i++) { total += abs(pos - right[i]); pos = right[i]; printf(" -> %d", pos); }
        for(int i = l - 1; i >= 0; i--) { total += abs(pos - left[i]); pos = left[i]; printf(" -> %d", pos); }
    } else {
        for(int i = l - 1; i >= 0; i--) { total += abs(pos - left[i]); pos = left[i]; printf(" -> %d", pos); }
        for(int i = 0; i < r; i++) { total += abs(pos - right[i]); pos = right[i]; printf(" -> %d", pos); }
    }
    printf("\nTotal Seek Time = %d\n", total);
}

void CSCAN() {
    int left[100], right[100], l = 0, r = 0, total = 0, pos = head, disk_size = 200;
    for(int i = 0; i < n; i++) {
        if(req[i] < head)
            left[l++] = req[i];
        else
            right[r++] = req[i];
    }
    sort(left, l); sort(right, r);

    printf("\nSeek Sequence: %d", pos);
    if(dir == 2) {
        for(int i = 0; i < r; i++) { total += abs(pos - right[i]); pos = right[i]; printf(" -> %d", pos); }
        total += abs(pos - (disk_size - 1)); pos = disk_size - 1;
        total += abs(pos - 0); pos = 0; printf(" -> %d", pos);
        for(int i = 0; i < l; i++) { total += abs(pos - left[i]); pos = left[i]; printf(" -> %d", pos); }
    } else {
        for(int i = l - 1; i >= 0; i--) { total += abs(pos - left[i]); pos = left[i]; printf(" -> %d", pos); }
        total += abs(pos - 0); pos = 0;
        total += abs(pos - (disk_size - 1)); pos = disk_size - 1; printf(" -> %d", pos);
        for(int i = r - 1; i >= 0; i--) { total += abs(pos - right[i]); pos = right[i]; printf(" -> %d", pos); }
    }
    printf("\nTotal Seek Time = %d\n", total);
}

int main(void) {
    printf("Enter number of requests: "); scanf("%d", &n);
    printf("Enter request sequence:\n"); for(int i = 0; i < n; i++) scanf("%d", &req[i]);
    printf("Enter initial head position: "); scanf("%d", &head);
    printf("Enter direction (1 = Left, 2 = Right): "); scanf("%d", &dir);

    int choice;
    while(1) {
        printf("\n--- Disk Scheduling ---\n1. SSTF\n2. LOOK\n3. C-SCAN\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);
        if(choice == 4) break;
        else if(choice == 1) SSTF();
        else if(choice == 2) LOOK();
        else if(choice == 3) CSCAN();
        else printf("Invalid choice!\n");
    }

    return 0;
}
