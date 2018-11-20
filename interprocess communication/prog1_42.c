#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 

#define MAX_SIZE 1024 

int main() 
{ 
    int fd1,fd2; 
    char * fifo1 = "/tmp/fifo1"; 
    char * fifo2 = "/tmp/fifo2"; 

    mkfifo(fifo1,0666); 
    
    char buf1[512] = {};
    char buf2[512] = {};
    printf("write a word here\n"); 
    scanf("%s",buf1);
    
    
    fd1 = open(fifo1, O_WRONLY);  // write only to the fifo1 write end.
    write(fd1, buf1,strlen(buf1)); 
    close(fd1); 


    fd2 = open(fifo2, O_RDONLY); //read the content in fifo2 readend. 
    read(fd2, buf2, MAX_SIZE); 
    printf("message read = %s\n", buf2); 
    close(fd2);

    unlink(fifo1); 
    unlink(fifo2); 

    return 0; 
}

