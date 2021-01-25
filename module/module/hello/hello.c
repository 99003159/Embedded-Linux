//hello.c
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
int choice=1;
int*ptr=NULL;
module_param(choice,int,S_IRUGO);
void noinline do_write(void) {
    int i,dummy=0;
    for(i=1;i<=10;i++)              //dummy code
      dummy+=i;
    *ptr = 100;                     //suspected code
    printk("end of do_write\n");
}
void noinline do_read(void) {
    int val,i,dummy;
    for(i=1;i<=10;i++)              //dummy code
      dummy+=i;
    val = *ptr;                     //suspected code
    printk("val is %d\n",*ptr);
}

 

static int __init hello_init(void) {        //init_module
  printk("Hello World..welcome\n");
	
  if(choice==1)
     do_write();   
  else
     do_read();
  return 0;
}

static void __exit hello_exit(void)
{
printk("Bye,Leaving the world\n");
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sriram");
MODULE_DESCRIPTION("A simple module");
