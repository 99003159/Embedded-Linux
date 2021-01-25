#include<unistd.h>
#include<stdio.h>
#include<string.h>

#define __NR_testcall 402

int main()
{
int ret;
ret=syscall(__NR_testcall);
if(ret<0)
perror("testcall");
printf("%d",ret);
return 0;
}
