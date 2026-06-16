/*
 * Copyright © 2025 pyjamabrah.com. All Rights Reserved.
 * Author: Piyush Itankar <piyush@pyjamabrah.com>
 *
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>

static LIST_HEAD(head);

struct bookkeeping {
    int id;
    int long_id;
    struct list_head list_meta;
};

static int __init dog_init(void) {
    printk(KERN_INFO "linked list experiments\n");
    struct bookkeeping *data1, *data2;

    data1 = kmalloc(sizeof(struct bookkeeping), GFP_KERNEL);
    if (!data1) {
        printk(KERN_INFO "memory allocation failed!\n");
        return -1;
    }

    data1->id = 10;
    data1->long_id = 123410;

    list_add(&(data1->list_meta), &head);

    data2 = kmalloc(sizeof(struct bookkeeping), GFP_KERNEL);
    if (!data2) {
        printk(KERN_INFO "memory allocation failed!\n");
        return -1;
    }

    data2->id = 20;
    data2->long_id = 100020;

    list_add_tail(&(data2->list_meta), &head);

    struct bookkeeping *cur;
    list_for_each_entry(cur, &head, list_meta) {
        printk(KERN_INFO "node id: %d\n", cur->id);
    }

    printk(KERN_INFO "removing %d\n", data2->id);
    list_del(&(data2->list_meta));
    kfree(data2);

    list_for_each_entry(cur, &head, list_meta) {
        printk(KERN_INFO "node id: %d\n", cur->id);
    }
    return 0;
}

static void __exit dog_exit(void) {
    struct bookkeeping *cur;
    printk(KERN_INFO "driver unload\n");
    list_for_each_entry(cur, &head, list_meta) {
        printk(KERN_INFO "node id: %d\n", cur->id);
        kfree(cur);
    }
    printk(KERN_INFO "module unloaded!\n");
}

module_init(dog_init);
module_exit(dog_exit);

MODULE_AUTHOR("Street Dogg <streetdogg@pyjamabrah.com>");
MODULE_LICENSE("GPL");