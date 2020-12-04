#pragma once

#ifndef sfp_c_object_wrapper
#define sfp_c_object_wrapper

#include "../../../utils/includes.h"
#include "../executor/executor.h"
#include "../params/c_params.h"

struct c_object_wrapper: public luabridge::RefCountedObject
{
	luabridge::RefCountedPtr<_jobject> ref;

	c_object_wrapper(jobject ref)
	{
		this->ref = luabridge::RefCountedPtr<_jobject>(ref);
	}

	~c_object_wrapper()
	{
		destroy();
	}

	jobject get_ref()
	{
		return ref.get();
	}

	void destroy();

	bool is_valid()
	{
		return ref.get() != 0;
	}

	void call_void(const char* name, const char* sig, c_params* params);

	c_object_wrapper* call_object(const char* name, const char* ret_class, c_params* params);
	c_object_wrapper* get_object(const char* name, const char* ret_class);
	void set_object(const char* name, const char* ret_class, jobject value);

	jint call_int(const char* name, const char* sig, c_params* params);
	jint get_int(const char* name);
	jint set_int(const char* name, jint value);

	jdouble call_double(const char* name, c_params params);
	lua_Number get_double(const char* name);
	void set_double(const char* name, jdouble value);

	jfloat call_float(const char* name, c_params params);
	jfloat get_float(const char* name); 
	void set_float(const char* name, jfloat value);
};

#endif