//hello.c
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
extern int xvar;
extern void sayHello(void); 
static int __init samplemod_init(void)
{
printk("Hello World..xvar=%d\n",xvar);
sayHello();
return 0;
}
static void __exit samplemod_exit(void)
{
printk("Bye,Leaving the world\n");
}
module_init(samplemod_init);
module_exit(samplemod_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sriram");
MODULE_DESCRIPTION("A hello world module");
