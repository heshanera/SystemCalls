#include <stdio.h>

char memory[500];

char * MyMalloc(int size)
{
	
	//printf("%d",size);
	/**
	 * increasing the filled size
	 */
	memory[499] += size;
	
	/**
	 * increasing the pointer that points to the first unallocated
	 * memory in the array
	 */ 
	memory[498] += size;
	
	//printf("%d ******* \n",( memory[498] - size));
	
	*( memory + memory[498] ) = size;
	
	/**
	 * returning the pointer
	 */ 
	return (memory + ( memory[498] - size) + 1);
}
