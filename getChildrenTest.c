#include "types.h"
#include "stat.h"
#include "user.h"

int stdout = 1;

int 
main() {

    printf(stdout, "pid is: %d\n", getpid()); 
    
    int n1 = fork(); 
    // int n2 = fork();
    // int n3 = fork();
    // int n4 = fork(); 
    printf(stdout, "%d\n", n1);
    // printf(stdout, "%d\n", n2);
    // printf(stdout, "%d\n", n3);
    // printf(stdout, "%d\n", n4);

    int *p;
    p = getChildren();
    printf(stdout, "first child: %d\n", *p); 
//  && n2 > 0 && n3 > 0 && n4 > 0
    if (n1 > 0) { 
        printf(stdout, "pid is: %d\n", getpid()); 
        printf(stdout, "ppid is: %d\n", getParentID());
        printf(stdout, "childrens are:\n");  
        // for (int i = 0; *(p + i) != -1; i++ ) {
        //     printf(stdout, "salam");
        //     printf(stdout, "*(p + %d) : %d\t", i, *(p + i));
        // }
    } 

    while(wait() != -1) { }
    sleep(1);
    exit();
}