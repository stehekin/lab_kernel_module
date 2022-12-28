#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif


static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xe3978188, "nonseekable_open" },
	{ 0x8d522714, "__rcu_read_lock" },
	{ 0x7e20bf00, "init_task" },
	{ 0x2469810f, "__rcu_read_unlock" },
	{ 0x92997ed8, "_printk" },
	{ 0xa37b1ee1, "misc_register" },
	{ 0x60a5326c, "misc_deregister" },
	{ 0xe6021ce1, "param_ops_int" },
	{ 0xc311ec4c, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "3172C556371A87C49047D8F");
