#include <kernel/types.h>
#include <kernel/param.h>
#include <user/user.h>
int main(int argc,char* argv[]){
	int i;
	char args[MAXARG][32];
	if(argc < 2){
			fprintf(2,"usage: xargs <command>\n");
			exit(0);
	}
	else{
			while(1){
					int Argc = argc-1;
					char buf;
					i = 0;
					memset(args,0,MAXARG*32);
					for(int j = 1;j < argc;j++){
							strcpy(args[i++],argv[j]);
					}
					i = 0;
					while(Argc < MAXARG-1){
							if(read(0,&buf,1) <= 0){
									wait(0);
									exit(0);
							}
							//printf("%c\n",buf);
							if(buf == '\n'){
									break;
							}
							args[Argc][i++] = buf;
					}
					char* p[MAXARG];
					for(i = 0;i < MAXARG;i++){
							p[i] = args[i];
					}
					p[MAXARG-1] = 0;
					if(fork() == 0){
							exec(argv[1],p);
					}else{
						wait(0);
					}
			}

			exit(0);
	}
}
/*
#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int i, j, pid, len;
  int first_blank;
  char args[MAXARG][32];
  char *p[MAXARG];
  char buf;

  if(argc < 2) {
    fprintf(2, "usage: xargs <cmd> ...\n");
    exit(0);
  }
  while (1)
  {
    // init
    i = 0;
    first_blank = 0;
    memset(args, 0, MAXARG * 32);

    // push command args and stdin args together
    // the first arg must be command itself
    for(j = 1; j < argc; j++) {
      strcpy(args[i++], argv[j]);
    }
    j = 0;  
    while (i < MAXARG-1) {
      if ((len = read(0, &buf, 1)) <= 0) {
        // CTRL+D 
        wait(0); 
        exit(0);
      }
      if (buf == '\n') {
        break;
      }
      if (buf == ' ') {
        if (first_blank) {
          i++;
          j = 0;
          first_blank = 0;
        }
        continue;
      }
      args[i][j++] = buf;
      first_blank = 1;
    }
    for (i = 0; i < MAXARG-1; i++) {
      p[i] = args[i];
    }
    // the last arg must be 0
    p[MAXARG-1] = 0;
    
    // exec command
    if ((pid = fork()) == 0) {
      exec(argv[1], p);
      exit(0);
    }
  }
  exit(0);
}
*/