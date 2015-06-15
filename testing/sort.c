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
	int numbers[100];
	
	bubblesort(numbers);
	
	exit(0);
}