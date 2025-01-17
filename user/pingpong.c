#include <kernel/types.h>
#include <kernel/stat.h>
#include <user/user.h>
int main()
{
    int p[2], q[2];
    char Child;
    char Parent;
    if (pipe(p) < 0|| pipe(q) < 0)
        exit(1);
    int pid = fork();
    if (pid < 0)
    {
        printf("error during fork process\n");
        exit(1);
    }
    else if (pid == 0)
    {
        close(p[0]);
        close(q[1]);
        write(p[1],"a",1);
        close(p[1]);
        read(q[0],&Child,1);
        close(q[0]);
        printf("%d: received ping\n",getpid());
    }
    else
    {
        close(p[1]);
        close(q[0]);
        write(q[1],"a",1);
        close(q[1]);
        read(p[0],&Parent,1);
        close(p[0]);
        wait(0);
        printf("%d: received pong\n",getpid());
    }
    exit(0);
}