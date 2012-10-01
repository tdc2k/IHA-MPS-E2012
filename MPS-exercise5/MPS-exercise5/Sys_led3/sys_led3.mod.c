#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x611eb49e, "module_layout" },
	{ 0xfe990052, "gpio_free" },
	{ 0xd119bbde, "cdev_del" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0x65d6d0f0, "gpio_direction_input" },
	{ 0x70788176, "cdev_add" },
	{ 0xaaeaa98c, "cdev_init" },
	{ 0xd8e484f0, "register_chrdev_region" },
	{ 0xa8f59416, "gpio_direction_output" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x4141f80, "__tracepoint_module_get" },
	{ 0x43b0c9c3, "preempt_schedule" },
	{ 0xbed60566, "sub_preempt_count" },
	{ 0x4c6ff041, "add_preempt_count" },
	{ 0x20a6ae6c, "module_put" },
	{ 0x432fd7f6, "__gpio_set_value" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xfbc74f64, "__copy_from_user" },
	{ 0x42224298, "sscanf" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x67c2fa54, "__copy_to_user" },
	{ 0x6c8d5ae8, "__gpio_get_value" },
	{ 0x91715312, "sprintf" },
	{ 0x27e1a049, "printk" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "4B78F37CBF20345B31B12ED");
