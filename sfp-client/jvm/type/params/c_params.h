#pragma once

#ifndef sfp_c_params
#define sfp_c_params

#include "LuaBridge/RefCountedPtr.h"
#include "../../../utils/includes.h"

struct c_object_wrapper;

struct c_params: public luabridge::RefCountedObject
{
private:
	std::vector<jvalue> params;

public:
	jvalue* get();

	bool empty()
	{
		return params.empty();
	}

	void push(jvalue value);
	
	void push_object(c_object_wrapper* wrapper);
	void push_int(int value);
	void push_float(float value);

};

#endif

