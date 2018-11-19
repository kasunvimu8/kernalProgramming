#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/types.h>
#include <stdlib.h>

int  main(char  argc,  char *argv[]){

    int  pid,wstatus;
    char string[30];
    
	pid  =  fork();

			if (pid  ==  0){ //child create the exec
			puts("This  is the  child  process");
			scanf("%s",string);
			execl("/bin/ls",  "-",  string , NULL); //cant get the data after creating this process to the child process.


	      	}
			
			 else{
			waitpid(-1, &wstatus, 0);
			puts("This  is the  parent  process\n");
			
			 }

    	return 0;

}