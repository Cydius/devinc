#include <stdlib.h>
#include <stdio.h>

int getStrSize(char *ptr) {
	int size = 0;
	while(*ptr != '\0') {
		ptr++;
		size++;
	}
	return size;
}

// was shit!

int main(int argc, char *argv[]) {
	printf("%s\n",reverse(argv[1]));
	return 0;
}
