#include <linux/sched.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/sched/signal.h>

	struct task_struct *task;

int simple_init(void) {

	for_each_process( task ){ 
		/* on each iteration task points to the next task */
		printk( KERN_INFO "task name : %s , state : %ld , pid : %d \n",task->comm,task->state ,task->pid);	

	}
	
 return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");