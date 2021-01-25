#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#define __NR_testcall 403

struct sample
{
int x;
int y;
int z;
};

int main()
{
int ret;
struct sample * s1=malloc(sizeof(struct sample));
s1->x=3;
s1->y=4;
s1->z=5;
ret=syscall(__NR_testcall,s1);
if(ret<0)
perror("testcall");
return 0;
}
