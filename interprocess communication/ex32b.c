#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>



/**
 * Executes the command "cat fixtures | grep <input_country>".  
 * Basic error checking is included for most system calls
 * 
 * @author Asitha Bandaranayake 
 * @version 0.2 05/08/2015
 */

#define INPUTFILE "fixtures"

/* function prototypes */
void die(const char*);

int main(int argc, char **argv)
{
	int pipefd[2];
	int pid;
	int  wstatus;
	if (argc < 2)
	{
		printf("%s: missing operand\n", argv[0]);
		printf("Usage: %s <search_term in %s>\n", argv[0],INPUTFILE); 
		exit(EXIT_FAILURE);
	}
	
	char *cat_args[] = {"cat", INPUTFILE, NULL};
	char *grep_args[] = {"grep", "-i", argv[1], NULL}; //ignore case sensitivity

	// make a pipe (fds go in pipefd[0] and pipefd[1])

	if(pipe(pipefd) == -1) 
		die("pipe()");

	pid = fork();
	if(pid == (pid_t)(-1))
		die("fork()");

	if (pid == 0)
	{
		// parent gets here and handles "cat INPUTFILE"

		// close standard output
		close(1);

		// replace standard output with output part of pipe
		if(dup(pipefd[1]) == -1)  //write the exection result in stdout to the pipefd[1] 
			die("dup()");

		// close unused input half of pipe
		close(pipefd[0]);

		// execute cat
		if(execvp("cat", cat_args) == -1)
			die("execvp()");

		exit(EXIT_SUCCESS);
	}
	else
	{
		// child gets here and handles "grep <search_term>"
        waitpid(-1, &wstatus, 0);
		// Close standard input
		close(0);

		// replace standard input with input part of pipe
		if(dup(pipefd[0]) == -1) //get the stdin things write by the parent in here as stdin 
			die("dup()");

		// close unused hald of pipe ---> prevent writing to ( stdout ) 
		 close(pipefd[1]);
		//close(pipefd[0]); //no problem we can interchangably use pipefd[0] and stdin //line 53 

		// execute grep
		if(execvp("grep", grep_args) == -1)
			die("execvp()");

		exit(EXIT_SUCCESS);
	}
}

/* A better way to Die (exit) */
void die(const char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}