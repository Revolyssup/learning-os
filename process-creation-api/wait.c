#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
    printf("The current process has process id %d\n",(int)getpid());
    fflush(stdout); //Flush the stdout of any buffer
    int rc=fork();
    if(rc<0){ //fork failed-exit
        fprintf(stderr,"Fork failed\n");
        exit(1);
    }
    if(rc==0){//child
        printf("The Child has process id %d\n",(int)getpid());
    }
    else{
        int rc_wait=wait(NULL);
         printf("The parent of %d has process id %d\n",rc_wait,(int)getpid());
    }
return 0;
}