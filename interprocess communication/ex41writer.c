#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 

int main() 
{ 
    int fd; 
    char * fifo = "/tmp/fifo"; 

    //mkfifo(fifo,0666); 

    fd = open(fifo, O_WRONLY); 
    write(fd, "Hi",2); 
    close(fd); 

    unlink(fifo); 

    return 0; 
}

/*as we can see when we writer first, write program should create the pipe and after
 execute the read we can get what is written by the writer.
if it is other way reader should create the pipe and should execute first 
and listing untill something written to the wrtiien end.*/