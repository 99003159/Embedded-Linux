#include<unistd.h>
#include<stdio.h>
#include<string.h>

#define __NR_testcall 401

int main()
{
int nbytes,ret;
char src[64],dest[64];
strcpy(src,"string to be copied");
nbytes=strlen(src);
ret=syscall(__NR_testcall,&src,&dest,nbytes+1);
if(ret<0)
perror("testcall");
printf("The string is %s",dest);
return 0;
}
