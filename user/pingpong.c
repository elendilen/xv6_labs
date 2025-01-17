#include <kernel/types.h>
#include <kernel/stat.h>
#include <user/user.h>
int main()
{
    int p[2], q[2];
    char Child[2];
    char Parent[2];
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
        //close(p[0]);
        //close(q[1]);
        write(p[1],"aaaaaaaaaa",10);
        //close(p[1]);
        read(p[0],Child,10);
        //close(q[0]);
        printf("child %s\n",Child);
        printf("%d: received ping\n",getpid());
    }
    else
    {
        //close(p[1]);
        //close(q[0]);
        write(p[1],"bbbbbbbbbb",10);
        //close(q[1]);
        read(p[0],Parent,10);
        //close(p[0]);
        wait(0);
        printf("Parent %s\n",Parent);
        printf("%d: received pong\n",getpid());
    }
    exit(0);
}