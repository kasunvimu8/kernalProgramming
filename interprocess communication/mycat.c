#include <stdio.h> 
#include <fcntl.h>   //constrauctor that refers to file control, opening ,retrieving and changing the permission of the file
#include <sys/types.h> 
#include <sys/stat.h> 
#include <string.h> 
#include <unistd.h>
#include <stdlib.h>

int main(){
  
 size_t size = 10000; 	 
 int ret,readOpen;
 char* buffer = malloc(size);

 readOpen = open("read.txt", O_RDONLY);
 
 if(readOpen ==-1){

 	fprintf(stderr, "can't open the file\n" );
 return 1;	
 }
 printf("start reading the file...\n");

 ret = read(readOpen,buffer,size); //number of bytes read and placed in buffer
 
 if(ret == -1)
	{
		fprintf(stderr,"Error reading from file\n");
		return 1;
	}
 
 if(ret == -1)
	{
		fprintf(stderr,"Error reading from file\n");
		return 1;
	}
  
  buffer[ret] = '\0'; /* we have to null terminate the string ourselves. */
	
	printf("The string read back is: %s\n",buffer);
	/* In case there was something already written in the file, the text read back might not be the same as what was written */
	
	printf("Done with reading. Closing the file...\n");
	
	free(buffer);

	ret = close(readOpen);

	if(ret == -1)
	{
		fprintf(stderr,"Error closing the file after reading.\n");
		return 1;
	}


return 0;
}