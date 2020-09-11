#include<stdio.h>
#include<unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
int main(){
    FILE * f;
    f=fopen("./test.txt","r");
    int rc=fork();
    if(rc==0) fprintf(f,"<==in child..\n");
    else fprintf(f,".<==in parent.\n");
}
