#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  int *p;

  printf(1, "testmunprotect: allocating one page\n");
  p = (int*)sbrk(4096);
  if((int)p == -1){
    printf(1, "sbrk failed\n");
    exit();
  }

  p[0] = 111;
  printf(1, "initial write worked\n");

  if(mprotect((void*)p, 1) < 0){
    printf(1, "mprotect failed\n");
    exit();
  }

  if(munprotect((void*)p, 1) < 0){
    printf(1, "munprotect failed\n");
    exit();
  }

  p[0] = 222;
  printf(1, "write after munprotect worked: %d\n", p[0]);
  exit();
}