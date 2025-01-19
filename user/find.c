#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
char *fmtname(char *path) // Give name without path
{
  static char buf[DIRSIZ + 1];
  char *p;

  // Find first character after last slash.
  for (p = path + strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if (strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf + strlen(p), ' ', DIRSIZ - strlen(p));
  buf[strlen(p)] = '\0';
  //printf("buf %s\n",buf);
  return buf;
}
void find(char *path, char *name)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;
  //printf("checking path %s\n",path);
  if ((fd = open(path, O_RDONLY)) < 0)
  {
    fprintf(2, "error opening path,check if your path is wrong");
    return;
  }

  if (fstat(fd, &st) < 0)
  {
    fprintf(2, "error cannot stat %s", path);
    close(fd);
    return;
  }

  switch (st.type)
  {
  case T_DEVICE:
  case T_FILE:
    //fprintf(2,"name:%s,fmt:%s\n",name,fmtname(path));
    if (!strcmp(fmtname(path), name))
    {
      fprintf(2, "%s\n", path);
    }
    break;
  case T_DIR:
      strcpy(buf, path);
      p = buf + strlen(buf);
      *p++ = '/';
      while (read(fd, &de, sizeof(de)) == sizeof(de))
      {
        if (de.inum == 0)
          continue;
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if (stat(buf, &st) < 0)
        {
          fprintf(2, "error!\n");
          continue;
        }
        //printf("name:%s,buf\n",fmtname(buf));
        if (st.type == T_DIR)
        {
          if (strcmp(".", fmtname(buf)) && strcmp("..", fmtname(buf)))
            find(buf, name);
        }else if(st.type == T_FILE||st.type == T_DEVICE){
            if(!strcmp(name,fmtname(buf))){
              fprintf(2,"%s\n",buf);
            }
        }
      }
    break;
  }
  close(fd);
}
int main(int argc, char *argv[])
{
  //printf("ready to find %s in dir %s\n",argv[2],argv[1]);
  find(argv[1], argv[2]);
  exit(0);
}
