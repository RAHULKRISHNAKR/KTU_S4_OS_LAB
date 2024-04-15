/*1. Initialization:

The code defines constants for the number of philosophers (N), their states (THINKING, HUNGRY, EATING), and helper macros for accessing left and right philosophers (LEFT and RIGHT).
It declares arrays for philosopher states (state) and philosopher IDs (phil).
A mutex semaphore (mutex) is used for mutual exclusion when accessing shared resources (states) and individual semaphores (S) are created for each philosopher to signal them when it's their turn to eat.
The philosopher function is designed to run as a separate thread for each philosopher.
2. Philosopher Thread Function (philosopher):

This function runs in a loop indefinitely for each philosopher thread.
Inside the loop:
A short delay (sleep(1)) simulates thinking time.
The philosopher calls take_fork to attempt picking up chopsticks.
Another short delay (sleep(0)) simulates eating time.
The philosopher calls put_fork to put down the chopsticks.
3. Taking Forks (take_fork function):

The philosopher acquires the mutex semaphore (sem_wait(&mutex)) to ensure exclusive access to shared resources (states).
It sets its state to HUNGRY indicating it needs chopsticks.
It attempts to eat by calling test(phnum).
It releases the mutex semaphore (sem_post(&mutex)) allowing other philosophers to access shared resources.
If test doesn't allow eating immediately, the philosopher waits on its own semaphore (sem_wait(&S[phnum])) to be signaled by another philosopher.
Another short delay (sleep(1)) simulates additional waiting time.
4. Testing to Eat (test function):

This function checks if the philosopher can eat based on its neighbors' states.
If the philosopher is hungry (state[phnum] == HUNGRY) and both left and right neighbors are not eating (state[LEFT] != EATING and state[RIGHT] != EATING), it sets its state to EATING and signals its own semaphore (sem_post(&S[phnum]) in case it was waiting earlier. This essentially allows the philosopher to proceed with eating.
5. Putting Forks Down (put_fork function):

The philosopher acquires the mutex semaphore (sem_wait(&mutex)) for exclusive access.
It sets its state to THINKING indicating it's done eating.
It calls test for both left and right neighbors (test(LEFT) and test(RIGHT)) to check if they can now eat since chopsticks are available.
It releases the mutex semaphore (sem_post(&mutex)) allowing other philosophers to access shared resources.
6. Main Function:

It initializes the semaphores (mutex and S).
It creates a thread for each philosopher using pthread_create.
It waits for all threads to finish using pthread_join.*/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % N
#define RIGHT (phnum + 1) % N

int state[N];
int phil[N] = { 0, 1, 2, 3, 4 };

sem_t mutex;
sem_t S[N];

void test(int phnum)
{
	if (state[phnum] == HUNGRY
		&& state[LEFT] != EATING
		&& state[RIGHT] != EATING) {
		// state that eating
		state[phnum] = EATING;

		sleep(2);

		printf("Philosopher %d takes fork %d and %d\n",
					phnum + 1, LEFT + 1, phnum + 1);

		printf("Philosopher %d is Eating\n", phnum + 1);

		// sem_post(&S[phnum]) has no effect
		// during takefork
		// used to wake up hungry philosophers
		// during putfork
		sem_post(&S[phnum]);
	}
}

// take up chopsticks
void take_fork(int phnum)
{

	sem_wait(&mutex);

	// state that hungry
	state[phnum] = HUNGRY;

	printf("Philosopher %d is Hungry\n", phnum + 1);

	// eat if neighbours are not eating
	test(phnum);

	sem_post(&mutex);

	// if unable to eat wait to be signalled
	sem_wait(&S[phnum]);

	sleep(1);
}

// put down chopsticks
void put_fork(int phnum)
{

	sem_wait(&mutex);

	// state that thinking
	state[phnum] = THINKING;

	printf("Philosopher %d putting fork %d and %d down\n",
		phnum + 1, LEFT + 1, phnum + 1);
	printf("Philosopher %d is thinking\n", phnum + 1);

	test(LEFT);
	test(RIGHT);

	sem_post(&mutex);
}

void* philosopher(void* num)
{

	while (1) {

		int* i = num;

		sleep(1);

		take_fork(*i);

		sleep(0);

		put_fork(*i);
	}
}

int main()
{

	int i;
	pthread_t thread_id[N];

	// initialize the semaphores
	sem_init(&mutex, 0, 1);

	for (i = 0; i < N; i++)

		sem_init(&S[i], 0, 0);

	for (i = 0; i < N; i++) {

		// create philosopher processes
		pthread_create(&thread_id[i], NULL,
					philosopher, &phil[i]);

		printf("Philosopher %d is thinking\n", i + 1);
	}

	for (i = 0; i < N; i++)

		pthread_join(thread_id[i], NULL);
}
