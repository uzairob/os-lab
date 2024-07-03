#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_PHILOSOPHERS 10  
#define MAX_CHOPSTICKS MAX_PHILOSOPHERS

void dine(int phil_position);
pthread_t philosophers[MAX_PHILOSOPHERS];
pthread_mutex_t chopsticks[MAX_CHOPSTICKS];

int main() {
    int num_total_philosophers, num_hungry_philosophers, i, status;
    int philosopher_positions[MAX_PHILOSOPHERS];

    
    printf("Enter the total number of philosophers (maximum %d): ", MAX_PHILOSOPHERS);
    scanf("%d", &num_total_philosophers);

    if (num_total_philosophers < 2 || num_total_philosophers > MAX_PHILOSOPHERS) {
        printf("Invalid number of philosophers. Must be between 2 and %d.\n", MAX_PHILOSOPHERS);
        return 1;
    }

    
    printf("Enter the number of philosophers who are hungry (maximum %d): ", num_total_philosophers);
    scanf("%d", &num_hungry_philosophers);

    if (num_hungry_philosophers < 2 || num_hungry_philosophers > num_total_philosophers) {
        printf("Invalid number of hungry philosophers. Must be between 2 and %d.\n", num_total_philosophers);
        return 1;
    }

    
    printf("Enter positions of %d hungry philosophers (1 to %d):\n", num_hungry_philosophers, num_total_philosophers);
    for (i = 0; i < num_hungry_philosophers; i++) {
        scanf("%d", &philosopher_positions[i]);
        if (philosopher_positions[i] < 1 || philosopher_positions[i] > num_total_philosophers) {
            printf("Invalid position for philosopher %d. Positions must be between 1 and %d.\n", i + 1, num_total_philosophers);
            return 1;
        }
    }

  
    for (i = 0; i < num_total_philosophers; i++) {
        status = pthread_mutex_init(&chopsticks[i], NULL);
        if (status != 0) {
            fprintf(stderr, "Error initializing mutex for chopstick %d\n", i);
            exit(1);
        }
    }

    
    for (i = 0; i < num_hungry_philosophers; i++) {
        status = pthread_create(&philosophers[i], NULL, (void *)&dine, (void *)(intptr_t)philosopher_positions[i]);
        if (status != 0) {
            fprintf(stderr, "Error creating thread for philosopher %d\n", i + 1);
            exit(1);
        }
    }

    
    for (i = 0; i < num_hungry_philosophers; i++) {
        status = pthread_join(philosophers[i], NULL);
        if (status != 0) {
            fprintf(stderr, "Error joining thread for philosopher %d\n", i + 1);
            exit(1);
        }
    }

   
    for (i = 0; i < num_total_philosophers; i++) {
        status = pthread_mutex_destroy(&chopsticks[i]);
        if (status != 0) {
            fprintf(stderr, "Error destroying mutex for chopstick %d\n", i);
            exit(1);
        }
    }

    return 0;
}

void dine(int phil_position) {
    printf("\nPhilosopher %d is thinking\n", phil_position);

  
    pthread_mutex_lock(&chopsticks[phil_position - 1]);

    
    pthread_mutex_lock(&chopsticks[phil_position % MAX_CHOPSTICKS]);

    
    printf("Philosopher %d is eating\n", phil_position);
    sleep(3); 
    
    pthread_mutex_unlock(&chopsticks[phil_position - 1]);

  
    pthread_mutex_unlock(&chopsticks[phil_position % MAX_CHOPSTICKS]);

    
    printf("Philosopher %d finished eating\n", phil_position);
}

