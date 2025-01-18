#include <kernel/types.h>
#include <kernel/stat.h>
#include <user/user.h>
void prime(int n)
{
    int num, sieve, pid;
    int p[2];
    if (read(n, &sieve, sizeof(int)) <= 0 || sieve <= 0)
    {
        exit(1);
    }
    printf("prime %d\n", sieve);
    pipe(p);
    pid = fork();
    if (pid == 0)
    {
        close(p[1]);
        prime(p[0]);
        close(p[0]);
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
    }
}
void PrimeStart()
{
    int i;
    int p[2];
    pipe(p);
    if (fork() == 0)
    {
        for (i = 2; i < 280; i++)
        {
            write(p[1], &i, sizeof(int));
        }
    }
    else
    {
        close(p[1]);
        prime(p[0]);
    }
}
int main(int argc, char *argv[])
{
    PrimeStart();
    exit(0);
}