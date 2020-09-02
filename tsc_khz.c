// SPDX-License-Identifier: GPL-2.0-only
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <asm/tsc.h>
#include <linux/cpu.h>
#include <linux/module.h>
#include <linux/sysfs.h>


/* sysfs file to export tsc_khz */
static ssize_t tsc_khz_show(struct kobject *kobj,
			    struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", tsc_khz);
}

struct kobj_attribute tsc_khz_attr = __ATTR_RO(tsc_khz);

static int __init init_tsc_khz(void)
{
	if (!sysfs_create_file(&cpu_subsys.dev_root->kobj, &tsc_khz_attr.attr))
		pr_info("tsc_khz exported in sysfs");
	else
		pr_warn("tsc_khz failed to be exported in sysfs");

	return 0;
}

static void __exit cleanup_tsc_khz(void)
{
	sysfs_remove_file(&cpu_subsys.dev_root->kobj, &tsc_khz_attr.attr);

	pr_info("tsc_khz unexported from sysfs");
}

module_init(init_tsc_khz);
module_exit(cleanup_tsc_khz);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Redha Gouicem, <redha.gouicem@gmail.com>");
MODULE_DESCRIPTION("export tsc clock frequency to sysfs");
