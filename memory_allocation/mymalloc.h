#include <stdio.h>

char memory[500];

/*
 * memory[499] stores the currenty filled size of the array
 * memory[498] size of the largest memory that can be allocated
 * memory[497] stores the pointer to the largest unallocated memory in the array
 * memory[496], memory[495], memory[494] stores variables
 * 
 * memory[493] stores number of bytes allocated for the memory management starting from the memory[492]
 * from memory[492] - memory[492-memory[493]] stores memory management info 
 * 
 */ 


char * MyMalloc(int size)
{
	
	if ( memory[499] == 0 )
	{
		memory[498] = (char)100;
	}
	
	
	/**
	 * storing the size of the allocated memory at the start of the allocated array
	 */ 
	memory[(int)memory[497]] = size;
	
	/**
	 * increasing the filled size of the array
	 */
	memory[499] += (size+1);
	
	/**
	 * increasing the pointer that points to the first unallocated memory in the array
	 */ 
	memory[497] += (size+1);
	
	/**
	 * setting the unallocated area pointer to the slot having largest memory
	 */
	
	
	/**
	 * returning the pointer
	 */ 
	return (memory + ( memory[497] - size));	
}

int MyFree(char *a)
{
	int result = 1;
	
	/**
	 * decreasing the allocated size of the array 
	 */ 
	memory[499] -= (*(a-1) + 1);
	
	
	/**
	 * adding info of the freed area to the array
	 */ 
	memory[492 - (int)memory[493]] = *(a-1)+1;
	memory[491 - (int)memory[493]] = (a-1-memory); 
	memory[493] += 2; 
	
	/**
	 * checking whether the unallocated ares can be mereged 
	 */
	
	for (memory[496] = memory[493]-2; memory[496] > 0; memory[496]-=2)
	{
		printf("%ld***\n",(a-1-memory)+ *(a-1));
		printf("%d\n\n",( memory[493 - memory[496]]));
		
		/**
		 * checking the start pointer of the freed memory location with the end point of currently free memory spaces
		 */ 
		if ((a-1-memory) == ( memory[493 - memory[496]] + memory[494 - memory[496]])) {
			
			memory[494 - memory[496]] += *(a-1)+1; 
			memory[493] -= 2;
			//printf("test\n");
			break;	
		
		/**
		 * checking the end pointer of the freed memory location with the start point of currently free memory spaces
		 */
		} else if ( ( (a-1-memory)+ *(a-1)+1 ) == memory[493 - memory[496]] ) {	 
			
			memory[494 - memory[496]] += *(a-1)+1; 
			memory[493 - memory[496]] = (a-1-memory);
			memory[493] -= 2;
			printf("test2\n");
			break;
		}
		
		//printf("test");
	}
	 
	 
	 
	/**
	 * setting the unallocated area pointer to the slot having largest memory
	 */  
	for (memory[496] = memory[493]; memory[496] > 0; memory[496]-=2)
	{
		if ( memory[494 - memory[496]] > memory[498] )
		{
			memory[495] = memory[498];
			memory[494] = memory[497];	
			
			memory[498] = memory[494 - memory[496]];
			memory[497] = memory[493 - memory[496]];
			
			memory[494 - memory[496]] = memory[498];
			memory[493 - memory[496]] = memory[497];
			
			memory[495] = memory[493 - memory[496]];	
		}	
		//printf("test");
	} 
	
	
	
	return result;
}
