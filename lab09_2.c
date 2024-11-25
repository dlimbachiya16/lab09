#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int counter = 0;
pthread_mutex_t lock;
pthread_cond_t is_one, is_two, is_three;

void * routine_even(void * arg)
{
    pthread_mutex_lock(&lock);
    // event: counter is zero (happens first)
    if (counter == 0) {
        printf("zero\n");
        counter ++;
	pthread_cond_signal(&is_one);
    }

    // event: counter is two
    while (counter != 2) {
       pthread_cond_wait(&is_two, &lock);
    }
    printf("two\n");
    counter += 1;
    pthread_cond_signal(&is_three);
    pthread_mutex_unlock(&lock);
    return NULL;
}


void * routine_odd(void * arg)
{
    pthread_mutex_lock(&lock);
    // event: counter is one
    while (counter != 1) {
        pthread_cond_wait(&is_one, &lock);
    }
    printf("one\n");
    counter += 1;
    pthread_cond_signal(&is_two);

    // event: counter is three
    while (counter != 3) {
        pthread_cond_wait(&is_three, &lock);
    }
    printf("three\n");

    pthread_mutex_unlock(&lock);
    return NULL;
}


int main(void)
{
    pthread_t even, odd;

    pthread_create(&even, NULL, routine_even, NULL);
    pthread_create(&odd, NULL, routine_odd, NULL);

    pthread_join(even, NULL);
    pthread_join(odd, NULL);

    printf("Finished\n");

    return 0;
}
