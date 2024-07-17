#include <stdio.h>
#include <stdlib.h>

#define BufferSize 10

int buffer[BufferSize];
int in = 0, out = 0;
int empty = BufferSize, full = 0, mutex = 1;

int maxP, maxC;

void wait(int *S)
{
    while (*S <= 0);
    (*S)--;
}

void signal(int *S)
{
    (*S)++;
}

void producer()
{
    int pItems = 0;
    while (pItems < maxP)
    {
        int item = rand() % 100;  // Producing a random item
        wait(&empty);   // Wait if the buffer is full
        wait(&mutex);   // Enter critical section

        buffer[in] = item;   // Add the item to the buffer
        printf("Producer produced item %d at %d\n", item, in);
        in = (in + 1) % BufferSize;

        signal(&mutex);   // Exit critical section
        signal(&full);    // Signal that buffer is not empty

        pItems++;
    }
}

void consumer()
{
    int cItems = 0;
    while (cItems < maxC)
    {
        wait(&full);    // Wait if the buffer is empty
        wait(&mutex);   // Enter critical section

        int item = buffer[out];   // Remove the item from the buffer
        printf("Consumer consumed item %d from %d\n", item, out);
        out = (out + 1) % BufferSize;

        signal(&mutex);   // Exit critical section
        signal(&empty);   // Signal that buffer is not full

        cItems++;
    }
}

int main()
{
    int numPs, numCs;
    printf("Enter number of producers: ");
    scanf("%d", &numPs);
    printf("Enter number of consumers: ");
    scanf("%d", &numCs);

    printf("Enter maximum items each producer can produce: ");
    scanf("%d", &maxP);
    printf("Enter maximum items each consumer can consume: ");
    scanf("%d", &maxC);

    // Simulating producers
    for (int i = 0; i < numPs; i++)
    {
        producer();
    }

    // Simulating consumers
    for (int i = 0; i < numCs; i++)
    {
        consumer();
    }

    return 0;
}

