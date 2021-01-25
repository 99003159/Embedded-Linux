#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#define __NR_testcall 404

struct process_custom
{
pid_t pid;
pid_t tgid;
int prio;
unsigned int policy;
};

int main()
{
int ret;
struct process_custom * p1=malloc(sizeof(struct process_custom));
ret=syscall(__NR_testcall,p1);
if(ret<0)
perror("testcall");
printf("The pid of the calling process is %d",p1->pid);
printf("The group id of the process is %d",p1->tgid);
printf("The priority of the process is %d",p1->prio);
printf("The policy is %d",p1->policy);
return 0;
}
