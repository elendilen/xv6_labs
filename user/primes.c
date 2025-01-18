/*#include <kernel/types.h>
#include <kernel/stat.h>
#include <user/user.h>
void prime(int n)
{
    int num, sieve, pid;
    int p[2];
    if (read(n, &sieve, sizeof(int)) <= 0 || sieve <= 0)
    {
        close(p[1]);
        exit(1);
    }
    printf("prime %d\n", sieve);
    pipe(p);
    pid = fork();
    if (pid == 0)
    {
        close(p[1]);
        close(p[0]);
        prime(p[0]);
        
    }
    else
    {
        close(p[0]);
        while (read(n, &num, sizeof(int)) && num)
        {
            if (num % sieve)
            {
                write(p[1], &num, sizeof(int));
            }
        }
        close(p[1]);
        close(n);
        wait(0);
    }
}
void PrimeStart()
{
    int i;
    int p[2];
    pipe(p);
    if (fork() == 0)
    {
        close(p[1]);
        prime(p[0]);
        close(p[0]);
    }
    else
    {
        for (i = 2; i < 280; i++)
        {
            write(p[1], &i, sizeof(int));
        }
        close(p[1]);
        wait(0);   
    }
}
int main(int argc, char *argv[])
{
    PrimeStart();
    exit(0);
}
*/
#include "kernel/types.h"
#include "user/user.h"

void
close_pipe(int *p) {
  close(p[0]);
  close(p[1]);
}

void
primes() {
  int n, p, len;
  int fd[2];

  // read from prev progress 
  if ((len = read(0, &n, sizeof(int))) <= 0 || n <= 0) {
    close(1);
    exit(1);
  }
  // write first prime to console
  printf("prime %d\n", n);
  
  pipe(fd);
  if (fork() == 0) {
    close(0);
    dup(fd[0]);
    close_pipe(fd);
    primes();
  } else {
    close(1);
    dup(fd[1]);
    close_pipe(fd);
    while ((len = read(0, &p, sizeof(int))) > 0 && p > 0) {
      if (p % n != 0) {
        write(1, &p, sizeof(int));
      }
    }
    if (len <= 0 || p <= 0) {
      close(1);
      exit(0);
    }
  } 
}

int
main(void) {
  int i;
  int fd[2];
  
  pipe(fd);
  if (fork() == 0) {
    close(0);
    dup(fd[0]);
    close_pipe(fd);
    primes();
  } else {
    close(1);
    dup(fd[1]);
    close_pipe(fd);
    for (i = 2; i <= 280; i++) {
      write(1, &i, sizeof(int));
    }
    close(1);
    wait(0);
  }
  exit(0);
}