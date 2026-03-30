#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  int pid;
  int *p;

  printf(1, "testforkprotect: allocating one page\n");
  p = (int*)sbrk(4096);
  if((int)p == -1){
    printf(1, "sbrk failed\n");
    exit();
  }

  p[0] = 123;
  printf(1, "parent: initial write worked\n");

  if(mprotect((void*)p, 1) < 0){
    printf(1, "parent: mprotect failed\n");
    exit();
  }

  pid = fork();
  if(pid < 0){
    printf(1, "fork failed\n");
    exit();
  }

  if(pid == 0){
    printf(1, "child: about to write to protected page\n");
    p[0] = 456;
    printf(1, "ERROR: child write should have faulted\n");
    exit();
  }

  wait();
  printf(1, "parent: child finished\n");
  exit();
}