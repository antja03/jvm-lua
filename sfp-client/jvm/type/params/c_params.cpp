#include "c_params.h"

#include "../object/c_object_wrapper.h"

jvalue* c_params::get()
{
	jvalue* arr = new jvalue[params.size()];
	std::copy(params.begin(), params.end(), arr);
	return arr;
}

void c_params::push(jvalue value)
{
	params.push_back(value);
}

void c_params::push_object(c_object_wrapper* wrapper)
{

	jvalue value;
	value.l = wrapper->get_ref();
	push(std::move(value));
}

void c_params::push_int(int i)
{
	jvalue value;
	value.i = i;
	push(value);
}

void c_params::push_float(float f)
{
	jvalue value;
	value.f = f;
	push(value);
}



