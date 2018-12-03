#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/types.h>

struct birthday{
	int day;
	int month;
	int year;
	struct list_head list;
	};

	static LIST_HEAD(birthday_list); //initialize the list variable

	struct birthday *person;

/* This function is called when the module is loaded. */
/* return 0 if in it correctly return  */

int simple_init(void) {

	struct birthday *ptr, *next;

	person = kmalloc(sizeof(*person), GFP_KERNEL);
	person->day =8;
	person->month =4;
	person->year =1995;

	INIT_LIST_HEAD(&person->list); //initialize the struct birthday
	list_add_tail(&person->list ,&birthday_list); //add the instance at the end of list
	

	list_for_each_entry(ptr, &birthday_list,list){
		printk(KERN_INFO "Adding a node \n");
		printk(KERN_INFO "birthday %d : %d : %d\n",ptr->year,ptr->month,ptr->day);
	}

	
	printk(KERN_INFO "freeing space\n");
    
	list_for_each_entry_safe(ptr,next,&birthday_list,list){
		list_del(&ptr->list);
		kfree(ptr);
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