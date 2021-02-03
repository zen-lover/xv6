#include "types.h"
#include "stat.h"
#include "user.h"

int 
main() {
    printf(1, "pid is: %d\n", getpid());
    printf(1, "ppid is: %d\n", getParentID(getpid()));
    return 0;
}