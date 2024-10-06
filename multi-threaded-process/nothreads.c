#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int n = 10;
int sum = 0;
float sum_2 = 0;
float average = 0;

void mysum() {
  printf("Initially Sum variable = %d\n", sum);
  for (int i = 1; i < n; i++) {
    sleep(1);
    sum = sum + i;
    ;
    printf("Loop %d: When we add %d, sum is %d\n ", i, i, sum);
  }
  printf("The sum function has ended here !!!!! \n \n \n");
}

void myaverage() {
  printf("Initially the variable average = %f \n", average);
  for (int i = 1; i < n; i++) {
    sleep(1);
    sum_2 = sum_2 + i;
    average = sum_2 / i;
    printf("Loop %d: The average from 1 to %d is : %f\n", i, i, average);
  }
  printf("The Average function has ended here !!!!! \n");
}

int main() {
  mysum();
  myaverage();

  return 0;
}