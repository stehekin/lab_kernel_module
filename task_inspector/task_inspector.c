#include <linux/cgroup-defs.h>
#include <linux/cred.h>
#include <linux/fs.h>	
#include <linux/init.h>
#include <linux/kernfs.h>
#include <linux/miscdevice.h>
#include <linux/mm.h>		
#include <linux/mm_types.h>
#include <linux/module.h>	
#include <linux/nsproxy.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/sched/task.h>
#include <linux/slab.h>		
#include <linux/types.h>
#include <linux/user_namespace.h>
#include <net/net_namespace.h>

#define MODNAME "ti"
MODULE_AUTHOR("qiang");
MODULE_DESCRIPTION("task inspector");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");

static int task_id;
module_param(task_id, int, 0600);
MODULE_PARM_DESC(task_id, "ID of the task to inspect.");

static int open_ti(struct inode *inode, struct file *filp) {
    return nonseekable_open(inode, filp);
}

struct task_info {
    int cgroup_level;
    u64 cgroup_id;
};

/*
enum cgroup_subsys_id {
    cpuset_cgrp_id = 0,
    cpu_cgrp_id = 1,
    cpuacct_cgrp_id = 2,
    io_cgrp_id = 3,
    memory_cgrp_id = 4,
    devices_cgrp_id = 5,
    freezer_cgrp_id = 6,
    net_cls_cgrp_id = 7,
    perf_event_cgrp_id = 8,
    net_prio_cgrp_id = 9,
    hugetlb_cgrp_id = 10,
    pids_cgrp_id = 11,
    rdma_cgrp_id = 12,
    CGROUP_SUBSYS_COUNT = 13,
*/

static ssize_t read_ti(struct file *filp, char __user *ubuf, size_t count, loff_t *off) {
    struct task_struct * p;
    struct task_info task_info;
    bool found = false;

    // Iterate the task list.
    rcu_read_lock();
    for_each_process(p) {
        if (p->thread_pid->numbers[0].nr != task_id) {
            continue;
        }
        found = true;
        struct cgroup_subsys_state *css = p->cgroups->subsys[memory_cgrp_id];
        struct kernfs_node *kn = css->cgroup->kn;
        task_info.cgroup_level = css->cgroup->level;
        task_info.cgroup_id = kn->id;
    }    
    rcu_read_unlock();

    if (found) {
        pr_info("cgroup_level %d, cgroup_id: %llu", task_info.cgroup_level, task_info.cgroup_id);
    } else {
        pr_warn("cannot found the task.");
    }

    return 0;
}

static const struct file_operations ti_fops = {
    .open = open_ti,
    .read = read_ti,
};

static struct miscdevice ti_misc_dev = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = MODNAME,
    .mode = 0666,
    .fops = &ti_fops,
};

static int __init ti_init(void) {
    int ret = misc_register(&ti_misc_dev);
    if (ret) {
        return ret;
    }
    return 0;
}

static void __exit ti_exit(void) {
    misc_deregister(&ti_misc_dev);
}

module_init(ti_init);
module_exit(ti_exit);
