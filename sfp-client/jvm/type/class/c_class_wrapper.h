#pragma once

#ifndef sfp_c_class_wrapper
#define sfp_c_class_wrapper

#include "../object/c_object_wrapper.h"

struct c_class_wrapper: public luabridge::RefCountedObject
{
private:
	const char* name;

public:
	c_class_wrapper(const char* name)
	{
		this->name = name;
	}

	
	const char* get_name();

	inline jclass get_ref();
	inline void del_ref(jclass ref);
	bool is_valid();

	void call_static_void(const char* name, c_params* params);

	c_object_wrapper* call_static_object(const char* name, const char* ret_class);
	c_object_wrapper* get_static_object(const char* name, const char* ret_class);
	void set_static_object(const char* name, const char* ret_class, jobject value);

	jdouble call_static_double(const char* name, const jvalue* args);
	jdouble get_static_double(const char* name);
	void set_static_double(const char* name, jdouble value);

	jint get_static_int(const char* name);
	
};

#endif

