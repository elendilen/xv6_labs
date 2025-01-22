#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/riscv.h"

int
main(int argc, char *argv[])
{
  // your code here.  you should write the secret to fd 2 using write
  // (e.g., write(2, secret, 8)
  char *end = sbrk(PGSIZE*32);
  end = end+32+16*PGSIZE;
  char secret[9];
  for(int i = 0;i < 8;i++){
    secret[i] = end[i];
  }
  write(2,secret,8);
  exit(1);
}
