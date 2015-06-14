#include <stdlib.h>
#include <stdio.h>

int getStrSize(char *ptr) {
	int size;
	size = 0;
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
	
	// goto last char
	while(*stext != '\0') {
		stext++;
	}
	stext--;

	for(i=0;i<textSize;i++) {
		reverse[i] = *stext;
		stext--;
	}
	return &reverse[0];
}

int main(int argc, char *argv[]) {
	printf("%s\n",reverse(argv[1]));
	return 0;
}
