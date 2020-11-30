#pragma once

#ifndef sfp_c_object_wrapper
#define sfp_c_object_wrapper

#include "../../../utils/includes.h"

class c_object_wrapper
{
private:
	jobject ref;

public:
	c_object_wrapper(jobject ref)
	{
		this->ref = ref;
	}

	~c_object_wrapper()
	{
		destroy();
	}

	inline void destroy();

	std::unique_ptr<c_object_wrapper> call_object(const char* name, const char* ret_class, const jvalue* args);
	std::unique_ptr<c_object_wrapper> get_object(const char* name, const char* ret_class);
	void set_object(const char* name, const char* ret_class, jobject value);

	jdouble call_double(const char* name, const jvalue* args);
	jdouble get_double(const char* name);
	void set_double(const char* name, jdouble value);

	jfloat call_float(const char* name, const jvalue* args);
	jfloat get_float(const char* name);
	void set_float(const char* name, jfloat value);

};

#endif