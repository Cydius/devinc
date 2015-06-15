#include <stdlib.h>
#include <stdio.h>

void bubblesort(int numbers[], int ncount) {
	int i,j;
	for(i=0;i<ncount-1;i++) {
		for(j=0;j<ncount-i-1;j++) {
			if(numbers[i]>numbers[j+1]) {
				int tmp = numbers[j];
				numbers[j] = numbers[j+1];
				numbers[j+1] = tmp;
			}
		}
	}
}

int main() {
	int i;
	int numbers[10] = {32, 70, 49, 65, 12, 9, 89, 55, 44, 33};

	// working sizeof array
	int arlength = sizeof(numbers)/sizeof(int);
	printf("array length is: %i\n",arlength);

	// add random numbers to array
	time_t t;
	srand((unsigned) time(&t));	
	for(i=0;i<sizeof(numbers);i++) {
		numbers[i] = rand() % 50;
	}
	printf("unsorted array\n");
	for(i=0;i<10;i++) {
                printf("%i ",numbers[i]);
        }
	
	printf("\nsorted array\n");
	bubblesort(numbers,arlength);
	for(i=0;i<10;i++) {
		printf("%i ",numbers[i]);
	}
	printf("\n");
	
	exit(0);
}
