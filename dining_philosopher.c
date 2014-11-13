#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

#define N 5
#define left (i % N)
#define right ((N + i - 1) % N)

sem_t s[N];
pthread_t p[N];

void eat(int i)
{
    printf("Philosopher %d is eating.\n", i + 1);
    sleep(1);
}
void think(int i)
{
    printf("Philosopher %d is thinking.\n", i + 1);
    sleep(1);
}

void philo(int i)
{
    do
    {
        think(i);
        sem_wait(&s[left]);
        sem_wait(&s[right]);
        eat(i);
        sem_post(&s[left]);
        sem_post(&s[right]);
    } while(1);
}

int main()
{
    int i;

    for(i = 0; i < N; i++)
        sem_init(&s[i], 0, 1);

    for(i = 0; i < N; i++)
        pthread_create(&p[i], NULL, (void *) &philo, (void *) i);

    do
    {
        sleep(1);
    }while(1);

    for(i = 0; i < N; i++)
        sem_destroy(&s[i]);

    return 0;
}
