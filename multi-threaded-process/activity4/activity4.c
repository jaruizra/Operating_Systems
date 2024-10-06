#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thread1(void *arg) {
    // print message
    printf("I am child1 thread \n");

    pthread_exit(0); // Thread terminate after finishing
}

void *thread2(void *arg) {
    // print message
    printf("I am child2 thread \n");

    pthread_exit(0); // Thread terminate after finishing
}
int main (int argc, char * argv[]) {

    // variables
    int n = 2;

    // loop for 2 times
    for (int i = 0; i < n; i++ ) {
        // print message
        printf("I am a parent thread \n");
    }
    
    // create pthreads
    // thrad ID
    pthread_t tid1, tid2;

    // loop 3 times fork() another thread, Print: I am child1 thread
    pthread_create(&tid1, NULL, thread1, NULL);
    // loop 3 times fork() another thread, Print: I am child1 thread
    pthread_create(&tid2, NULL, thread2, NULL);

    // join the parents
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    // father exits
    exit(0);
}