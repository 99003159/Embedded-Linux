#include<linux/fs.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/uaccess.h>
#include<linux/slab.h>

#define MAX_SIZE 1024

struct cdev cdev;
dev_t pdevid;
int ndevices=1;
struct device *pdev;
struct class *pclass;
unsigned char *pbuffer;
int rd_offset=0;
int wr_offset=0;
int buflen=0;
int ret;
int wcount;
int rcount;
int pseudo_open(struct inode* inode , struct file* file)
{
printk("Pseudo--open method\n");
return 0;
}
int pseudo_close(struct inode*inode,struct file*file)
{
printk("Pseudo--release method\n");
return 0;
}
ssize_t pseudo_read(struct file*file,char __user*buf,size_t size,loff_t*off)
{
//unsigned char ubuf[64];
if(buflen==0)
{
printk("buffer is empty\n");
return 0;
}
rcount=size;
if(rcount>buflen)
rcount=buflen;
ret=copy_to_user(buf,pbuffer+rd_offset,rcount);
if(ret)
{
printk("copy to user failed\n");
return -EFAULT;
}
printk("The read value-- %s",buf);
rd_offset+=rcount;
buflen-=rcount;
return rcount;
}
ssize_t pseudo_write(struct file*file,const char __user*buf,size_t size,loff_t * off)
{
//unsigned char* ubuf;
if(wr_offset>=MAX_SIZE)
{
printk("buffer is full\n");
return -ENOSPC;
}
wcount=size;
if(wcount>MAX_SIZE-wr_offset)
wcount=MAX_SIZE-wr_offset;
ret=copy_from_user(pbuffer+wr_offset,buf,wcount);
if(ret)
{
printk("copy from user failed\n");
return -EFAULT;
}
wr_offset+=wcount;
buflen+=wcount;
return wcount;
}
 

struct file_operations fops = {
.open = pseudo_open,
.release = pseudo_close,
.write = pseudo_write,
.read = pseudo_read
};

static int __init pseudo_init(void)
{
int ret,i=1;
pclass=class_create(THIS_MODULE,"pseudo_class");
cdev_init(&cdev,&fops);
alloc_chrdev_region(&pdevid,0,ndevices,"pseudo_sample");
ret=cdev_add(&cdev,pdevid,1);
pdev=device_create(pclass,NULL,pdevid,NULL,"psample%d",i);

if(ret)
{
printk("pseudo: Failed toregister driver\n");
return -EINVAL;
}
printk("Successfully registered,major=%d,minor=%d\n",MAJOR(pdevid),MINOR(pdevid));
printk("Pseudo Driver Sample...welcome\n");
pbuffer=kmalloc(MAX_SIZE,GFP_KERNEL);
return 0;
}
static void __exit pseudo_exit(void)
{
unregister_chrdev_region(pdevid,ndevices);
printk("Pseudo Driver sample..Bye\n");
cdev_del(&cdev);
device_destroy(pclass,pdevid);
class_destroy(pclass);
kfree(pbuffer);
}
module_init(pseudo_init);
module_exit(pseudo_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sriram");
MODULE_DESCRIPTION("Pseudo buffer module");
