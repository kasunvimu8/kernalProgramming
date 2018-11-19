#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include  <stdlib.h>
#define INPUTFILE "fixtures"
/**
 * Executes the command "cat fixtures | grep <search_term> | cut -b 1-9".
 */
void die(const char*);

int main(int argc, char **argv)
{
	int status;
	int i;
	int  wstatus;
	// arguments for commands
	char *cat_args[] =  {"cat", INPUTFILE, NULL};
	char *grep_args[] = {"grep", "-i", argv[1], NULL}; //ignore case sensitivity
	char *cut_args[] =  {"cut","-b", "1-9", 0 ,NULL};

	// make 2 pipes (cat to grep and grep to cut); each has 2 fds

	int pipe1[2];
	int pipe2[2];

	// sets up 1st pipe
	// TODO: ** insert your code here **
	if(pipe(pipe1) == -1) 
		die("pipe()");

	// sets up 2nd pipe
	// TODO: ** insert your code here **
    if(pipe(pipe2) == -1) 
		die("pipe()");

	// we now have 4 fds:
	// pipes[0] = read end of cat->grep pipe (read by grep)
	// pipes[1] = write end of cat->grep pipe (written by cat)
	// pipes[2] = read end of grep->cut pipe (read by cut)
	// pipes[3] = write end of grep->cut pipe (written by grep)

	// fork the first child (to execute cat)

	if (fork() == 0)
	{
		// replace cat's stdout with write part of 1st pipe
		// TODO: ** insert your code here **
		 close(1);
		 if(dup(pipe1[1]) == -1)  
		 	die("dup()");

		// close all pipes (very important!); end we're using was safely copied
		// TODO: ** insert your code here **
		 close(pipe1[0]);
		 close(pipe1[1]);
		 close(pipe2[0]);
		 close(pipe2[1]);

		// Execute the cat command
		// TODO: ** insert your code here **
		 if(execvp("cat", cat_args) == -1)
			die("execvp()");

		 exit(EXIT_SUCCESS);
	}
	else
	{
		// fork second child (to execute grep)

		if (fork() == 0)
		{
			// replace grep's stdin with read end of 1st pipe
			// TODO: ** insert your code here **
			close(0);
			if(dup(pipe1[0]) == -1) 
				die("dup()");


			// replace grep's stdout with write end of 2nd pipe
			// TODO: ** insert your code here **
			 close(1);
		    if(dup(pipe2[1]) == -1)  
		 	 die("dup()");

			// close all ends of pipes
			// TODO: ** insert your code here **
		 	 close(pipe1[0]);
		 	 close(pipe1[1]);
			 close(pipe2[0]);
			 close(pipe2[1]);

			// execute grep command
			// TODO: ** insert your code here **
			if(execvp("grep", grep_args) == -1)
			die("execvp()");

	    	exit(EXIT_SUCCESS);
		}
		else
		{
			 waitpid(-1, &wstatus, 0);
			// fork third child (to execute cut)

			if (fork() == 0)
			{
				// replace cut's stdin with input read of 2nd pipe
				// TODO: ** insert your code here **
				close(0);
		       if(dup(pipe2[0]) == -1)  
		 	    die("dup()");
				
				// close all ends of pipes
				// TODO: ** insert your code here **
		 			 close(pipe1[0]);
		 			 close(pipe1[1]);
		 			 close(pipe2[0]);
					 close(pipe2[1]);
					

				// execute cut command
				// TODO: ** insert your code here **
		 	        if(execvp("cut", cut_args) == -1)
						die("execvp()");

	    			exit(EXIT_SUCCESS);
			}
		}
	}

	// only the parent gets here and waits for 3 children to finish
	// It's a good idea to close all your pipes (the parent needs none!)
	// before waiting for your children! 

	// TODO: ** insert your code here **
		close(pipe1[0]);
		close(pipe1[1]);
		 	        
	// TODO: ** insert your code here **
		close(pipe2[0]);
		close(pipe2[1]);

}

void die(const char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}