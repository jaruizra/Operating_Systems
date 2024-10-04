#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int n = 10;
int sum = 0;
float sum_2 = 0;
float average = 0;

void *mysum(void *arg) {
  printf("INITIALLY THE SUM VARIABLE = %d\n", sum);
  for (int i = 1; i < n; i++) {
    sleep(3);
    sum = sum + i;
    ;
    printf("SUM LOOP %d: WHEN WE ADD %d, SUM is %d\n ", i, i, sum);
  }
  printf("THREAD #1 FUNCTION HAS ENDED HERE !!!!! \n \n \n");
   pthread_exit(0); // Thread terminate after finishing 
}

void *myaverage(void *arg) {
  printf(" Initially the variable average = %f \n", average);
  for (int i = 1; i < n; i++) {
    sleep(5);
    sum_2 = sum_2 + i;
    average = sum_2 / i;
    printf("Average loop %d: The average from 1 to %d is : %f\n", i, i, average);
  }
  printf("Thread #2 function has ended here !!!!! \n");
   pthread_exit(0); // Thread terminate after finishing 
}

int main() {

  pthread_t tid1, tid2; // creating thread IDs for thread1 and thread2

  pthread_create(&tid1, NULL, mysum,
                 NULL); // creating thread1 which runs mysum task.

  pthread_create(&tid2, NULL, myaverage,
                 NULL); // creating thread2 which runs myaverage task.

  pthread_join(tid1, NULL); 

  pthread_join(tid2, NULL);

  return 0;
}