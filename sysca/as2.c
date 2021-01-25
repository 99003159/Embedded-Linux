#include<unistd.h>
#include<stdio.h>
#include<string.h>

#define __NR_testcall 400

int main()
{
int nbytes,ret;
char buf[64];
strcpy(buf,"Hi, I am the string");
nbytes=strlen(buf);
ret=syscall(__NR_testcall,&buf,nbytes+1);
if(ret<0)
perror("testcall");
return 0;
}
