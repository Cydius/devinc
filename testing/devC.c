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

// trying to reverse text of pointer
char *reverse(char *stext) {
	int textSize = getStrSize(stext);
	int i;
	char reverse[textSize];
	char *ptrReturn;

	// goto last char
	while(*stext != '\0') {
		stext++;
	}
	stext--;
	
	// fill array with chars from pointer
	for(i=0;i<textSize;i++) {
		reverse[i] = *stext;
		stext--;
	}
	ptrReturn = reverse;
	return ptrReturn;
}

int main(int argc, char *argv[]) {
	printf("%s\n",reverse(argv[1]));
	return 0;
}
