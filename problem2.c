#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// compiled with command: 	gcc -o p1 main.c -lm -lpthread


typedef enum { false, true } bool; 

struct threadData{
	int num;
	bool * myArray;
};


void* primeCheck(void * data);
void* primeReverse(void * data);



int main(int argc, char *argv[]) {
  
  int n;
  printf("Enter a number N, so we can calculate Primes less than N\n");
  scanf("%d",&n);
	
  int i;

	bool *A = malloc((n + 1) * sizeof(*A));
	for (i = 0; i < n+1; i++) 
		A[i] = true; 			

	struct threadData cont;
	cont.num = n;				
	cont.myArray = A; 	

	pthread_t tid;


	pthread_create(&tid, NULL, primeCheck, (void *) &cont); 

	pthread_join(tid, NULL); 			
	printf("Primes less than n:\n");

	for ( i = 2; i <= n; i++) {
		if (A[i] == true) 			
			printf("%d\n", i);
	}


	pthread_create(&tid, NULL, primeReverse, (void *) &cont); 


	pthread_join(tid, NULL); 			

	printf("\n");

	free(A);
	return 0;
}


void* primeCheck(void * data) {	

	struct threadData *information = (struct threadData *) data; 

	int num = information->num; 
  int i,j;
  
	for (i = 2; i <= num; i++) { 
		if (information->myArray[i] == true) {
			for (j = i*i; j <= num; j += i)
				information->myArray[j] = false;
		}
	}

	pthread_exit(NULL); 
}

void* primeReverse(void * data) {

	printf("\nPrime Reversable Numbers:\n");
  int i,j; 
	struct threadData *information = (struct threadData *) data; 

	int num = information->num; 
	int reversedDigits = 0;
	
	for ( i = 2; i <= num; i++) {	
		if (information->myArray[i] == true) {	
			reversedDigits = digRev(i);
			if (information->myArray[reversedDigits] == true) 
				printf("%d\n", i);
		}
	}

	pthread_exit(NULL); 
}

int digRev(int num) {
    int rev_num = 0;
    while(num > 0)
    {
        rev_num = rev_num*10 + num%10;
        num = num/10;
    }
    return rev_num;
}
