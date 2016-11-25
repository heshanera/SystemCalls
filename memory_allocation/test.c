#include <stdio.h>
#include "mymalloc.h"


int main()
{		
	
	unsigned char * pointer;
	pointer = MyMalloc(1000);
	int i;
	for (i = 0; i<1000; i++)
	{
		*(pointer+i) = 97;
	}
	
	unsigned char * pointer2;
	pointer2 = MyMalloc(500);
	for (i = 0; i<500; i++)
	{
		*(pointer2+i) = 35;
	}
	
	unsigned char * pointer3;
	pointer3 = MyMalloc(500);
	for (i = 0; i<500; i++)
	{
		*(pointer3+i) = 35;
	}
	
	unsigned char * pointer4;
	pointer4 = MyMalloc(500);
	for (i = 0; i<500; i++)
	{
		*(pointer4+i) = 35;
	}
	
	
	MyFree(pointer);
	MyFree(pointer3);
	MyFree(pointer2);
	
	
	/*
	unsigned char * pointer3 = MyMalloc(2000);
	for (i = 0; i<2000; i++)
	{
		*(pointer3+i) = 66;
	}
	
	
	MyFree(pointer3);
	MyFree(pointer2);
	MyFree(pointer);
	
	
	unsigned char * pointer4 = MyMalloc(2000);
	for (i = 0; i<2000; i++)
	{
		*(pointer4+i) = 55;
	}
	*/
	unsigned char * pointer5 = MyMalloc(5000);
	for (i = 0; i<5000; i++)
	{
		*(pointer5+i) = 44;
	}
	
	unsigned char * pointer6 = MyMalloc(10000);
	for (i = 0; i<10000; i++)
	{
		*(pointer6+i) = 33;
	}
	MyFree(pointer4);
	
	
	unsigned char * pointer7 = MyMalloc(4500);
	for (i = 0; i<100; i++)
	{
		*(pointer7+i) = 77;
	}
	
	MyFree(pointer6);
	
	
	for (i = -4; i<24996; i+=10)
	{
		printf("%d	%d	%d	%d	%d	%d	%d	%d	%d	%d\n",*(pointer+i),*(pointer+i+1),*(pointer+i+2),*(pointer+i+3),*(pointer+i+4),*(pointer+i+5),*(pointer+i+6),*(pointer+i+7),*(pointer+i+8),*(pointer+i+9));
	}
	
	
	printf("\n\n *****************************************\n\n");
	
	
	printf("%d	<--	filled size \n",getIntValueIn4Bytes(pointer-4+24996));
	printf("%d	<--	variable 4 \n",getIntValueIn4Bytes(pointer-4+24992));
	printf("%d	<--	variable 3 \n",getIntValueIn4Bytes(pointer-4+24988));
	printf("%d	<--	variable 2 \n",getIntValueIn4Bytes(pointer-4+24984));
	printf("%d	<--	variable 1 \n",getIntValueIn4Bytes(pointer-4+24980));
	printf("%d	<--	available slots  \n",getIntValueIn4Bytes(pointer-4+24976));
	printf("%d	<--	unallocated size in largest slot\n",getIntValueIn4Bytes(pointer-4+24972));
	printf("%d	<--	pointer to unallocated area of the largest slot \n",getIntValueIn4Bytes(pointer-4+24968));
	
	int slots = getIntValueIn4Bytes(pointer-4+24976);
	
	for(i = 1; i < slots; i++)
	{
		printf("%d	<--	size of the slot %d\n",getIntValueIn4Bytes(pointer-4+24964-(8*(i-1))),i+1);
		printf("%d	<--	pointer to the slot %d\n",getIntValueIn4Bytes(pointer-4+24960-(8*(i-1))),i+1);
		
	}

	return 0;
}
