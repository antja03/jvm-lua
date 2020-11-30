#pragma once

#ifndef sfp_c_class_wrapper
#define sfp_c_class_wrapper

#include "../../../utils/includes.h"
#include "../object/c_object_wrapper.h"

class c_class_wrapper
{
private:
	const char* name;

	inline jclass get_ref();
	inline void del_ref(jclass ref);

public:
	c_class_wrapper(const char* name)
	{
		this->name = name;
	}

	const char* get_name();

	std::unique_ptr<c_object_wrapper> call_static_object(const char* name, const char* ret_class, const jvalue* args);
	std::unique_ptr<c_object_wrapper> get_static_object(const char* name, const char* ret_class);
	void set_static_object(const char* name, const char* ret_class, jobject value);

	jdouble call_static_double(const char* name, const jvalue* args);
	jdouble get_static_double(const char* name);
	void set_static_double(const char* name, jdouble value);
	
};

#endif

