#include<unistd.h>
#include<stdio.h>

#define __NR_testcall 399

int main()
{
int ret,a,b;
a=4;
b=3;
ret=syscall(__NR_testcall,a,b);
if(ret<0)
perror("testcall");
return 0;
}
