#include <stdio.h>
#include <stdlib.h>
int main()
{
	int *ptr = NULL;
	int i;
	ptr = malloc(4 * sizeof(int));
	ptr[0] = 1;
	ptr[1] = 3;
	ptr[2] = 4;
	ptr[3] = 6;
	for (i = 0; i < 4; i++) {
		printf("value at index [%d] is %d \n", i, ptr[i]);
	}

	printf("after changing the array size\n");
	ptr = realloc(ptr, 10 * sizeof(int));
	for (i = 4; i < 10; i++) {
		ptr[i] = i * i;
	}
	for (i = 0; i < 10; i++) {
		printf("value at index [%d] is %d \n", i, ptr[i]);
	}
}
