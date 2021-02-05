#include "types.h"
#include "stat.h"
#include "user.h"

int stdout = 1;

int 
main() {
    printf(stdout, "pid is: %d\n", getpid());
    printf(stdout, "ppid is: %d\n", getParentID());
    
    while(wait() != -1) { }
    sleep(1);
    exit();
}