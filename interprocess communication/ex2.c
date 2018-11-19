#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>

int main() {

    int parent_pipe[2];
    int child_pipe[2];
    char buff[50];
   
    char input[15];
    printf("Type your input: ");
    scanf("%s",input);

    if(pipe(parent_pipe) || pipe(child_pipe)) {
        perror("pipe(...)");
        exit(1);
    }

    
    int pid = fork();
    if (pid == -1) {
        perror("fork()");
        exit(1);
    }

    if (pid == 0) {
        // this is the child process.  read from child_pipe, write to parent_pipe
        char cbuff[50];
        int in, out;
        in = child_pipe[0];
        out = parent_pipe[1];
        
            read(in,cbuff,50);
            //printf("Parent: %s",cbuff);
            // NOTE: `strlen(child)` doesn't include the nul at the end!
          for(int i=0;i<strlen(cbuff);i++){
           cbuff[i] = toupper(cbuff[i]);
          }

            write(out, cbuff, strlen(cbuff) + 1);
        
    }
    else {

    	char pbuff[50];
        // this is the parent process
        int in, out;
        in = parent_pipe[0]; //read parent from here
        out = child_pipe[1];  //write parent from here
               
        	printf("sending to child :%s\n",input);
            write(out, input, strlen(input) + 1);
            read(in, pbuff, 50);
            printf("received from child: %s\n", pbuff);
        
    }


}

