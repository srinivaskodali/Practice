#include <stdio.h>
#include <stdbool.h>

bool binarysearch_recursive(int *A, int val, int start, int end)
{

	int median;
	median = (start+end)/2;
	if (start == end)
		return false;
	if(A[median] == val)
		return true;
	else if( A[median] < val)
		return binarysearch_recursive(A, val, median+1, end);
	else if (A[median] > val)
		return binarysearch_recursive(A, val, start, median-1);
	
return false;
}

int main() {

	int A[]= {1,12,23,34,45,56,67,78,89,90,99};
	int val=0;
	printf("Enter value smaller than 100 to search in an array A\n");
	scanf("%d",&val);

	if(binarysearch_recursive(A,val,0,10) == true)
		printf("Value %d found in array A\n", val);
	else
		printf("Value %d not found in array A\n", val);
}
