#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
char* fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}
void find(char* path){
    int fd;
    struct dirent de;
    struct stat st;
    if((fd = open(path,O_RDONLY)) < 0){
        fprintf(2,"error opening path,check if your path is wrong");
        return;
    }
    if(fstat(fd,&st) < 0){
        fprintf(2,"error cannot stat %s",path);
        close(fd);
        return;
    }
    switch(st.type){
        case T_DEVICE:
            break;
        case T_FILE:
            
    }
}
int main(int argc,char* argv[]){

    exit(0);
}