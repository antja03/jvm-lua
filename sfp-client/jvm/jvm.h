#pragma once

#include "../utils/includes.h"
#include "type/class/c_class_wrapper.h" // includes object wrapper

class c_jvm_wrapper
{
private:
	JavaVM* vm;
	JNIEnv* env;

public:
	JavaVM* get_vm()
	{
		return this->vm;
	}

	JNIEnv* get_env()
	{
		return this->env;
	}

	int init();
	std::unique_ptr<c_class_wrapper> find_class(const char* name);

};

extern std::unique_ptr<c_jvm_wrapper> g_jvm;