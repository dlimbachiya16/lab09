#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void * routine_hello(void * arg)
{
    printf("Hello\n");
    return NULL;
}


int main(int argc, char * argv[])
{
    if (argc != 2) {
        printf("You must specify the number of threads!\n");
        exit(1);
    }

    int n = atoi(argv[1]);

    pthread_t tids[n];

    // TODO: launch n threads with each executing f
    for (int i = 0 ; i < n ; i++) {
	    if(pthread_create(&tids[i], NULL, routine_hello, NULL) != 0){
		    perror("Failed");
		    exit(1);
	    }
    }

    // TODO: use join to wait for all the threads
    for (int i = 0 ; i < n ; i++) {
	    if(pthread_join(tids[i], NULL) != 0){
		    perror("Failed");
		    exit(1);
	    }
    }

    printf("Finished\n");

    return 0;
}
