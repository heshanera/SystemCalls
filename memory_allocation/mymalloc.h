unsigned char memory[25000];

unsigned char * MyMalloc(int size);
int MyFree(unsigned char *pointer);

int storeIn4Bytes(unsigned char *, int val);
int addAndStoreIn4Bytes(unsigned char *pointer, int val);
int subAndStoreIn4Bytes(unsigned char *pointer, int val);
int getIntValueIn4Bytes(unsigned char *pointer);


