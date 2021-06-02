#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

int n;
int a[10000];
int count = 0;
int i = 0;
sem_t semaphoreee;

void *push()
{
    while (1)
    {
        if (count < n)
        {
            a[i] = rand() % (n-1);
            count++;
            i++;
            printf("[PUSH] ====> Total elements in array *a* are %d \n", count);
        }
        sem_post(&semaphoreee);
    }
}

void *pop()
{
    int temp, j;
    while (1)
    {
        sem_wait(&semaphoreee);
        if (count == 0)
        {
            printf("[*] There's nothing in array *a* \n");
        }
        else
        {
            count--;
            temp = a[0];
            for(j = 0; j < n; j++)
            {
                a[j] = a[j+1];
            }
            if (count == 0)
            {
                printf("[POP] ====> Nothing in array *a* anymore \n");
            }
            else
            {
                printf("[POP] ====> Total elements in array *a* are %d \n", count);                
            }
        }
    }
}

void main()
{
    printf("Enter n: ");
    scanf("%d", &n);

    sem_init(&semaphoreee, 0, 0);
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, push, NULL);
    pthread_create(&thread2, NULL, pop, NULL);
    while(1);
}