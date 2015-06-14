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

// testing area:
// trying to reverse text of pointer
void rever(char *stext) {
	//char *stext = "Das ist ein etwas laengerer Text! Bitte testen ob das funktioniert.";
	char *tmpStext;
	tmpStext = stext;
	int textSize = getStrSize(stext);
	char *reverse;
        reverse = (char *) malloc(textSize*(sizeof(char)));
	if(reverse == NULL) {
		printf("malloc failed\n");
	} else {
		printf("malloc OK!\n");
	}
	printf("size of text: %i\n",textSize);
	printf("value of text: %s\n",stext);
	printf("reserved space by malloc in byte: %lu\n\n", textSize*sizeof(char));

	while(*stext != '\0') {
		stext++;
	}
	stext--;
	printf("last char of text?: %c\n",*stext);	

	int i;
	for(i=0;i<textSize;i++) {
		*reverse = *stext;
		printf("run %i: value: %c -on %p\n",i,*reverse,reverse);
		reverse++;
		stext--;
	}
	reverse = reverse - textSize;
	printf("complete? : %s\n",reverse);
//	printf("last by arraysize %i\n",sizeof(reverse));

	while(*reverse != '\0') {
		printf("%c",*reverse);
		reverse++;
	}
	printf("\n");
}

/* Functions only above main */
int main(int argc, char *argv[]) {
	rever(argv[1]);
	return 0;
}
