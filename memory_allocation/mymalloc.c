#include <stdio.h>
#include "mymalloc.h"

/*
 * last 4bytes store the allocated memory size [24996 - 24999]
 * 16bytes use to store variables [24980 - 24995]
 * 1byte to store number of free memory slots [24976 - 24979] 
 * bytes from [24972 -] to start, are used to store free memory slots
 * 																						
 * first 4bytes before the pointer of allocated memory are used to store the size
 * 
 */ 


unsigned char * MyMalloc(int size)
{
	
	/**
	 * Inializing the memory array if it is empty
	 */ 
	if ( getIntValueIn4Bytes(memory+24996) == 0 )
	{
		storeIn4Bytes(memory+24976,1);
		// 24968 <-- pointer
		// 24972 <-- size
		storeIn4Bytes(memory+24968,0);
		storeIn4Bytes(memory+24972,24970);
	}	
	
	/**
	 * checking if there is enough memory
	 */ 
	if ( getIntValueIn4Bytes(memory+24972) > size )
	{
		/**
		 * storing the size of the allocated memory at the start of the allocated array
		 */ 
		storeIn4Bytes(memory+getIntValueIn4Bytes(memory+24968),size);
		
		/**
		 * increasing the filled size of the array
		 */
		addAndStoreIn4Bytes(memory+24996,(size+4)); 
		
		/**
		 * reducing the size of the unallocated memory of the slot
		 */ 
		subAndStoreIn4Bytes(memory+24972, (size+4));
		
		/**
		 * increasing the pointer that points to the first unallocated memory in the array
		 */ 
		addAndStoreIn4Bytes(memory+24968,(size+4));
		
		/**
		 * setting the unallocated area pointer to the slot having largest memory
		 */  
		storeIn4Bytes(memory+24992,getIntValueIn4Bytes(memory+24976)); 
		for (; getIntValueIn4Bytes(memory+24992) > 0; subAndStoreIn4Bytes(memory+24992,1))
		{
			if ( getIntValueIn4Bytes(memory+24976-4*(getIntValueIn4Bytes(memory+24992)*2-1)) > getIntValueIn4Bytes(memory+24972))
			{
				storeIn4Bytes(memory+24988,getIntValueIn4Bytes(memory+24972));
				storeIn4Bytes(memory+24984,getIntValueIn4Bytes(memory+24968));
				
				storeIn4Bytes(memory+24972,getIntValueIn4Bytes(memory+24976-4*(getIntValueIn4Bytes(memory+24992)*2-1)));
				storeIn4Bytes(memory+24968,getIntValueIn4Bytes(memory+24976-4*(getIntValueIn4Bytes(memory+24992)*2)));
				
				storeIn4Bytes(memory+24976-4*(getIntValueIn4Bytes(memory+24992)*2-1), getIntValueIn4Bytes(memory+24988));
				storeIn4Bytes(memory+24976-4*(getIntValueIn4Bytes(memory+24992)*2),getIntValueIn4Bytes(memory+24984));	
				
				printf("test\n\n");		
			}
		}
		
		/**
		 * returns the pointer of the allcated memory
		 */ 
		return (memory + ( getIntValueIn4Bytes(memory+24968) - size));
		
	} else {
		return NULL;	
	}
}

int MyFree(unsigned char *pointer)
{	
	if ( getIntValueIn4Bytes(pointer-4) != 0)
	{
		/**
		 * decreasing the allocated size of the array 
		 */ 
		subAndStoreIn4Bytes( memory+24996, getIntValueIn4Bytes(pointer-4)+4 );  

		/**
		 * checking whether the unallocated areas can be mereged 
		 */
		*(memory+24980) = 0;	// unallocated memory slot merge flag 
		storeIn4Bytes(memory+24992,getIntValueIn4Bytes(memory+24976)); 
		for (; getIntValueIn4Bytes(memory+24992) > 0; subAndStoreIn4Bytes(memory+24992,1))
		{
			/**
			 * checking the start pointer of the freed memory location with the end point of currently free memory spaces
			 */ 
			if ( (pointer-4-memory) == (	(	getIntValueIn4Bytes(memory+24976-4*(getIntValueIn4Bytes(memory+24992)*2)) ) + 
											(	getIntValueIn4Bytes(memory+24976-4*(getIntValueIn4Bytes(memory+24992)*2-1))))) 
			{
				addAndStoreIn4Bytes(memory+24976-(4*getIntValueIn4Bytes(memory+24992)) - 4, getIntValueIn4Bytes(pointer-4)+4);
				*(memory+24980) = 1;	// new unallocated slot is merged
				
				/**
				 * checking the end pointer of the freed memory location with the start point of currently free memory spaces
				 */ 
				storeIn4Bytes(memory+24988,getIntValueIn4Bytes(memory+24976)); 
				for (; getIntValueIn4Bytes(memory+24988) > 0; subAndStoreIn4Bytes(memory+24988,1))
				{
					if ( ((pointer-memory)+getIntValueIn4Bytes(pointer-4) ) == 
						(getIntValueIn4Bytes(memory+24976-4*(getIntValueIn4Bytes(memory+24988)*2)))  )
					{
						addAndStoreIn4Bytes(memory+24976-(4*getIntValueIn4Bytes(memory+24992)) - 4,
											(getIntValueIn4Bytes(memory+24976-4*(getIntValueIn4Bytes(memory+24988)*2-1))));
											
						storeIn4Bytes((memory+24976-4*(getIntValueIn4Bytes(memory+24988)*2)), (getIntValueIn4Bytes(memory+24976-4*(getIntValueIn4Bytes(memory+24976)*2))));
						storeIn4Bytes((memory+24976-4*(getIntValueIn4Bytes(memory+24988)*2-1)),(getIntValueIn4Bytes(memory+24976-4*(getIntValueIn4Bytes(memory+24976)*2-1))));				
						
						subAndStoreIn4Bytes((memory+24976),1);
						
						break;
					}	
						
				}					
				break;	
			
			/**
			 * checking the end pointer of the freed memory location with the start point of currently free memory spaces
			 */ 
			} else if ( ((pointer-memory)+getIntValueIn4Bytes(pointer-4) ) == 
						(getIntValueIn4Bytes(memory+24976-4*(getIntValueIn4Bytes(memory+24992)*2)))  ) {	 
				
				storeIn4Bytes((memory+24976-4*(getIntValueIn4Bytes(memory+24992)*2)),pointer-memory-4 );
				addAndStoreIn4Bytes((memory+24976-4*(getIntValueIn4Bytes(memory+24992)*2-1)),getIntValueIn4Bytes(pointer-4)+4 );

				*(memory+24980) = 1;	// new unallocated slot is merged
				
				/**
				 * checking the start pointer of the freed memory location with the end point of currently free memory spaces
				 */ 
				storeIn4Bytes(memory+24988,getIntValueIn4Bytes(memory+24976)); 
				for (; getIntValueIn4Bytes(memory+24988) > 0; subAndStoreIn4Bytes(memory+24988,1))
				{
					if ( (pointer-4-memory) == 	((getIntValueIn4Bytes(memory+24976-4*(getIntValueIn4Bytes(memory+24988)*2)) ) + 
												(getIntValueIn4Bytes(memory+24976-4*(getIntValueIn4Bytes(memory+24988)*2-1)))) ) 
					{
						addAndStoreIn4Bytes(memory+24976-4*(getIntValueIn4Bytes(memory+24992)*2-1),(getIntValueIn4Bytes(memory+24976-4*(getIntValueIn4Bytes(memory+24988)*2-1))) );
						
						storeIn4Bytes( (memory+24976-4*(getIntValueIn4Bytes(memory+24988)*2)) , getIntValueIn4Bytes(memory+24976-4*(getIntValueIn4Bytes(memory+24988)*2)) );
						storeIn4Bytes( (memory+24976-4*(getIntValueIn4Bytes(memory+24988)*2-1)) , (getIntValueIn4Bytes(memory+24976-4*(getIntValueIn4Bytes(memory+24976)*2-1))) );				
						
						printf("%d\n\n",getIntValueIn4Bytes(memory+24976-4*(getIntValueIn4Bytes(memory+24988)*2-1)));
						//printf("%d",*(memory+24976-4*(getIntValueIn4Bytes(memory+24988)*2-1)));
						
						subAndStoreIn4Bytes((memory+24976),1);
						
						break;
					}	
						
				}		
				
				break;
			}
			
		} 
		
		/**
		 * adding info of the new unallocated area to the array if it cannot be merged
		 */ 
		if  (*(memory+24980) == 0)	// if new unallocated slot is not merged
		{
			addAndStoreIn4Bytes(memory+24976,1);
			
			/**
			 * allocating 8 bytes from the main array to store info about new slot
			 */
			subAndStoreIn4Bytes(memory+24972,8);

			storeIn4Bytes( memory+24976-(4*(getIntValueIn4Bytes(memory+24976)*2-1)) ,( getIntValueIn4Bytes(pointer-4)+4 ));
			storeIn4Bytes( memory+24976-(4*getIntValueIn4Bytes(memory+24976)*2), pointer-4-memory);
		}	

		/**
		 * setting the unallocated area pointer to the slot having largest memory
		 */  
		storeIn4Bytes(memory+24992,getIntValueIn4Bytes(memory+24976)); 
		for (; getIntValueIn4Bytes(memory+24992) > 0; subAndStoreIn4Bytes(memory+24992,1))
		{
			if ( getIntValueIn4Bytes(memory+24976-4*(getIntValueIn4Bytes(memory+24992)*2-1)) > getIntValueIn4Bytes(memory+24972))
			{
				storeIn4Bytes(memory+24988,getIntValueIn4Bytes(memory+24972));
				storeIn4Bytes(memory+24984,getIntValueIn4Bytes(memory+24968));
				
				storeIn4Bytes(memory+24972,getIntValueIn4Bytes(memory+24976-4*(getIntValueIn4Bytes(memory+24992)*2-1)));
				storeIn4Bytes(memory+24968,getIntValueIn4Bytes(memory+24976-4*(getIntValueIn4Bytes(memory+24992)*2)));
				
				storeIn4Bytes(memory+24976-4*(getIntValueIn4Bytes(memory+24992)*2-1), getIntValueIn4Bytes(memory+24988));
				storeIn4Bytes(memory+24976-4*(getIntValueIn4Bytes(memory+24992)*2),getIntValueIn4Bytes(memory+24984));	
				
				printf("test\n\n");		
			}
		} 

		// changing the size indicater of the freed slot into 0
		storeIn4Bytes(pointer-4,0);

		return 1;
		
	} else {
		
		printf("free memory location\n");
		return 0;	
	}	
}


int storeIn4Bytes(unsigned char *pointer, int val)
{
	*(pointer) = (val >> 24) & 0xFF;
	*(pointer+1) = (val >> 16) & 0xFF;
	*(pointer+2) = (val >> 8) & 0xFF;
	*(pointer+3) = val & 0xFF;
	
	return 0;
}

int addAndStoreIn4Bytes(unsigned char *pointer, int val)
{
	val += *(pointer)*256 + *(pointer+1)*256 + *(pointer+2)*256 + *(pointer+3);
	
	*(pointer) = (val >> 24) & 0xFF;
	*(pointer+1) = (val >> 16) & 0xFF;
	*(pointer+2) = (val >> 8) & 0xFF;
	*(pointer+3) = val & 0xFF;
	
	return 0;
}

int subAndStoreIn4Bytes(unsigned char *pointer, int val)
{
	val = (*(pointer)*256 + *(pointer+1)*256 + *(pointer+2)*256 + *(pointer+3)) - val;
	
	*(pointer) = (val >> 24) & 0xFF;
	*(pointer+1) = (val >> 16) & 0xFF;
	*(pointer+2) = (val >> 8) & 0xFF;
	*(pointer+3) = val & 0xFF;
	
	return 0;
}

int getIntValueIn4Bytes(unsigned char *pointer)
{
	return *(pointer)*256 + *(pointer+1)*256 + *(pointer+2)*256 + *(pointer+3);
}



