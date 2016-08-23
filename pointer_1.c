// shows how to use a pointer to pointer.
// veriosn : 1.0
// Author : Srinivas Kodali

main(){
	int *ptr;
	int **ptrtoptr;
	int x,p;
	p=9;
	ptr=&p;
	ptrtoptr=&ptr;
	(**ptrtoptr)++;
	printf(" value of **ptrtoptr = %d\n",**ptrtoptr);
//output is - value of **ptrtoptr = 10
	printf( "ptrtoptr = %x\n",ptrtoptr);
//output is - ptrtoptr = bfcce010
	ptrtoptr++;
	printf( "ptrtoptr = %x\n",ptrtoptr);
//output is - ptrtoptr = bfcce014
	ptrtoptr--;
	printf(" ptr = %x\n",ptr);
//output is - ptr = bfcce014
	(*ptrtoptr) ++;
	printf(" ptr = %x\n",ptr);
//output is - ptr = bfcce018
	(*ptrtoptr) --;
	x=**ptrtoptr;
	/* Value will be incremented not the pointer
	If **ptroptr++ - pointer will be incremented first follwed by retreiving the value in it*/
	printf( "ptrtoptr = %x  x=%d\n",ptrtoptr,x);
//output is - ptrtoptr = bfcce010  x=10
	x=++**ptrtoptr;
// never use the constructs like above .
	printf( "ptrtoptr = %x  x=%d\n",ptrtoptr,x);
//output is - ptrtoptr = bfcce010  x=11


}
