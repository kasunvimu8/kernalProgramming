#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_SIZE 1024 
#define STDIN 0
#define STDOUT 1

void die(const char *msg);

int main() 
{ 

	int fd1, fd2; 
	char* fifo1 = "/tmp/fifo1"; 
	char* fifo2 = "/tmp/fifo2";

	char *tr_args[] = {"tr", "[:lower:]", "[:upper:]", NULL};
	
	printf("Waiting for the Sender \n");

    // Make 2 named pipelines
	mkfifo(fifo1,0666);
	mkfifo(fifo2, 0666);

	// Set STDIN and STDOUT for the process
	fd1 = open(fifo1, O_RDONLY); //reading the string from fifo1 
	fd2 = open(fifo2, O_WRONLY); //writing the capitalizd text back to the write end of the fifo2

	if (dup2(fd1, STDIN) == -1)  //because we use capiterlize command inbuild
		die("dup2()");

	if (dup2(fd2, STDOUT) == -1)
		die("dup2()");

	close(fd1);
	close(fd2);
	

	// Execute tr() command
	if(execvp("tr", tr_args) == -1)
	//if(execvp("grep", grep_args) == -1)
		die("execvp()");


	exit(EXIT_SUCCESS);

    return 0; 
}

/* A better way to Die (exit) */
void die(const char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}