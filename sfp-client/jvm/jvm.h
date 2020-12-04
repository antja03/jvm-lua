#pragma once

#ifndef sfp_c_jvm_wrapper
#define sfp_c_jvm_wrapper

#include "type/class/c_class_wrapper.h"

namespace jvm
{
	extern JavaVM* vm;
	extern JNIEnv* env;

	int init();
	c_class_wrapper* find_class(const char* name);


};

#endif