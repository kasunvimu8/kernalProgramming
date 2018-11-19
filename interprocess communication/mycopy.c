#include <stdio.h> 
#include <fcntl.h>   //constrauctor that refers to file control, opening ,retrieving and changing the permission of the file
#include <sys/types.h> 
#include <sys/stat.h> 
#include <string.h> 
#include <unistd.h>
#include <stdlib.h>

int main (int argc, char *argv[]){
    
 size_t size = 1000; 	 
 int ret,readOpen,writeOpen; //to save file discriptor vales.
 char* buffer = malloc(size);
 
 if (argc != 3){
 	printf("\n Usage : ./a.out readTextFileName writeTextFileName");
 }

 readOpen = open(argv[1], O_RDONLY);
 
 	if(readOpen ==-1){

 	   fprintf(stderr, "can't open the file\n" );
	 return 1;	
 	}

ret = read(readOpen,buffer,size);
 
 	if(ret == -1)
	{
		fprintf(stderr,"Error reading from file\n");
		return 1;
	}
buffer[ret] = '\0'; /* we have to null terminate the string ourselves. */

ret = close(readOpen);


writeOpen = open(argv[2], O_WRONLY  | O_CREAT , S_IRUSR | S_IWUSR );
 
	 if(writeOpen ==-1){

	 	fprintf(stderr, "can't open the file\n" );
	 return 1;	
	 }

ret = write(writeOpen,buffer,strlen(buffer));

	if(ret == -1)
		{
			fprintf(stderr,"Error writing to file\n");
			return 1;
		}

ret = close(writeOpen);

	if(ret == -1)
	{
		fprintf(stderr,"Error closing the file after writing.\n");
		return 1;
	}

free(buffer);

return 0;
}