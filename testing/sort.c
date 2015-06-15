#include <stdlib.h>
#include <stdio.h>

void bubblesort(int *numbers) {
	int i,j;
	
	for(i=0;i<sizeof(numbers)-1;i++) {
		for(j=0;j<sizeof(numbers)-i-1;j++) {
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
	int numbers[100];
	
	for(i=0;i<sizeof(numbers);i++) {
		numbers[i] = rand() % 500;
	}
	
	bubblesort(numbers);

	for(i=0;i<sizeof(numbers);i++) {
		printf("%c",numbers[i]);
	}
	printf("\n");
	
	exit(0);
}