#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  int *p;

  printf(1, "testmprotect: allocating one page\n");
  p = (int*)sbrk(4096);
  if((int)p == -1){
    printf(1, "sbrk failed\n");
    exit();
  }

  p[0] = 123;
  printf(1, "before mprotect: write worked\n");

  if(mprotect((void*)p, 1) < 0){
    printf(1, "mprotect failed\n");
    exit();
  }

  printf(1, "after mprotect: about to write to protected page\n");
  p[0] = 456;

  printf(1, "ERROR: write should have faulted\n");
  munprotect((void*)p, 1);
  exit();
}