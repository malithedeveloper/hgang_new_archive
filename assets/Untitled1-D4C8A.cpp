#include <stdio.h>

int main(void) {
	int aa = 10;
	h:
		switch(aa) {
			case 1:
				printf("this is case 1 \n");
				break;
			case 2:
				printf("this is case 2 \n");
				aa = aa - 1;
				goto h;
			default:
				aa = aa - 1;
				goto h;
	}
	return 0;
}