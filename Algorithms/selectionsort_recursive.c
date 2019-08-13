#include <stdio.h>
#include <stdbool.h>

bool selectionsort_recursive(int *A, int val, int start, int end)
{

	int median;
	median = (start+end)/2;
	if (start == end)
		return false;
	if(A[median] == val)
		return true;
	else if( A[median] < val)
		return selectionsort_recursive(A, val, median+1, end);
	else if (A[median] > val)
		return selectionsort_recursive(A, val, start, median-1);
	
return false;
}

int main() {

	int A[]= {34,12,56,24,87,23,4,98,76,58,47,25,17,49,9,90,99};
	int i=0;
	selectionsort_recursive(A,val,0,10);
	printf("Sorted array as follows:\n");
	for (i=0; i<17; i++)
		printf("%d\t",A[i]);
	printf("\n");
}
