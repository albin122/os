#include <stdio.h>

#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0;

// Simulated semaphores
int mutex = 1;
int empty = SIZE;
int full = 0;

// wait (P)
void wait(int *s) {
    while (*s <= 0); // busy wait
    (*s)--;
}

// signal (V)
void signal(int *s) {
    (*s)++;
}

// Producer
void producer(int item) {
    wait(&empty);
    wait(&mutex);

    buffer[in] = item;
    printf("Produced: %d at position %d\n", item, in);
    in = (in + 1) % SIZE;

    signal(&mutex);
    signal(&full);
}

// Consumer
void consumer() {
    wait(&full);
    wait(&mutex);

    int item = buffer[out];
    printf("Consumed: %d from position %d\n", item, out);
    out = (out + 1) % SIZE;

    signal(&mutex);
    signal(&empty);
}

int main() {
    // Simulated sequence
    producer(1);
    producer(2);
    consumer();
    producer(3);
    consumer();
    consumer();

    return 0;
}
