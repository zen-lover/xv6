#include "types.h"
#include "stat.h"
#include "user.h"

int stdout = 1;

void print_children(int* children){
    for (int i =0;i<20;i++){
        printf(1,"%d _",children[i]);
    }
    printf(1,"\n");
}

int main(){

    int pid1 = fork();
    int pid2 = fork();
    int pid3 = fork();
    int pid4 = fork();
    if (pid1>0 && pid2>0 && pid3>0 && pid4>0)
    {
     int* children=(int *)malloc(sizeof(int)*20);
     getChildren(children);
     printf(1,"The process is %d and the children are ",getpid());
     print_children(children);   
    }
    while (wait()!=-1){  }
    sleep(1);
    exit();
}