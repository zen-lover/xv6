#include "types.h"
#include "stat.h"
#include "user.h"

int stdout = 1;
int
main(int argc, char **argv)
{
  int i;

  if(argc < 2){
    printf(2, "usage: getSyscallCounterTest pid...\n");
    exit();
  }
  for(i=1; i<argc; i++)
    printf(stdout, "counter is: %d\n", getSyscallCounter(atoi(argv[i])));
  exit();
}
