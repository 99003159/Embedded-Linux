#include<stdio.h>
#include<stdlib.h>
int main()
{
u_int8_t ret;
asm("LDR r7, #398;"
"SVC #0;"
"LDR %[result], r0" : [result] "=r" (ret));
return 0;
}
