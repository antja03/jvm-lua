#include "c_object_wrapper.h"

#include "../../jvm.h"

// gets + validates field id
// runs the provided code block
// deletes class reference
#define cls_get_field(sig, ...)							jclass class_ref =  jvm::env->GetObjectClass(get_ref());							\
														if (class_ref == NULL) return;														\
														jfieldID field_id = jvm::env->GetFieldID(class_ref, name, sig);						\
														if (field_id == NULL) return;														\
														__VA_ARGS__;  																		\
														jvm::env->DeleteLocalRef(class_ref);

#define cls_get_field_o(sig, ...)						jclass class_ref =  jvm::env->GetObjectClass(get_ref());							\
														if (class_ref == NULL) return nullptr;												\
														jfieldID field_id = jvm::env->GetFieldID(class_ref, name, sig);						\
														if (field_id == NULL) return nullptr;												\
														__VA_ARGS__;  																		\
														jvm::env->DeleteLocalRef(class_ref);

#define cls_get_field_t(sig, ret_val, ...)				jclass class_ref =  jvm::env->GetObjectClass(get_ref());							\
														if (class_ref == NULL) return ret_val;												\
														jfieldID field_id = jvm::env->GetFieldID(class_ref, name, sig);						\
														if (field_id == NULL) return ret_val;												\
														__VA_ARGS__;  																		\
														jvm::env->DeleteLocalRef(class_ref);

// gets + validates method id
// runs the provided code block
// deletes class reference
#define cls_get_method(sig, ...)						jclass class_ref =  jvm::env->GetObjectClass(get_ref());							\
														if (class_ref == NULL) return;														\
														jmethodID method_id = jvm::env->GetMethodID(class_ref, name, sig);					\
														if (method_id == NULL) return;														\
														__VA_ARGS__;	     																\
														jvm::env->DeleteLocalRef(class_ref);

#define cls_get_method_o(sig, ...)						jclass class_ref =  jvm::env->GetObjectClass(get_ref());							\
														if (class_ref == NULL) return nullptr;												\
														jmethodID method_id = jvm::env->GetMethodID(class_ref, name, sig);					\
														if (method_id == NULL) return nullptr;												\
														__VA_ARGS__;	     																\
														jvm::env->DeleteLocalRef(class_ref);

#define cls_get_method_t(sig, ret_val, ...)				jclass class_ref =  jvm::env->GetObjectClass(get_ref());							\
														if (class_ref == NULL) return ret_val;												\
														jmethodID method_id = jvm::env->GetMethodID(class_ref, name, sig);					\
														if (method_id == NULL) return ret_val;												\
														__VA_ARGS__;	     																\
														jvm::env->DeleteLocalRef(class_ref);

void c_object_wrapper::destroy()
{
	jvm::env->DeleteLocalRef(get_ref());
}

void c_object_wrapper::call_void(const char* name, const char* signature, c_params* params)
{
	cls_get_method(
		signature,
		jvm::env->CallVoidMethod(get_ref(), method_id, params->get());
	);
}

c_object_wrapper* c_object_wrapper::call_object(const char* name, const char* sig, c_params* params)
{
	cls_get_method_o(
		sig,
		jobject ret = (params == nullptr || params->empty()) ? jvm::env->CallObjectMethod(get_ref(), method_id) : jvm::env->CallObjectMethodA(get_ref(), method_id, params->get())
	);

	auto wrapper = new c_object_wrapper(ret);

	if (!wrapper->is_valid())
		return nullptr;

	return wrapper;
}

c_object_wrapper* c_object_wrapper::get_object(const char* name, const char* sig)
{
	cls_get_field_o(
		sig,
		jobject ret = jvm::env->GetObjectField(get_ref(), field_id);
	);

	auto wrapper = new c_object_wrapper(ret);

	if (!wrapper->is_valid())
		return nullptr;

	return wrapper;
}

void c_object_wrapper::set_object(const char* name, const char* ret_class, jobject value)
{
	cls_get_field(
		(std::string(std::string("L") + ret_class + ";")).c_str(),
		jvm::env->SetObjectField(get_ref(), field_id, value);
	);
}

jint c_object_wrapper::call_int(const char* name, const char* sig, c_params* params)
{
	cls_get_method_t(
		sig,
		0,
		jint ret = (params == nullptr || params->empty()) ? jvm::env->CallIntMethod(get_ref(), method_id) : jvm::env->CallIntMethodA(get_ref(), method_id, params->get())
	);

	return ret;
}

jint c_object_wrapper::get_int(const char* name)
{
	cls_get_field_t(
		"I",
		0,
		jint ret = jvm::env->GetIntField(get_ref(), field_id);
	);

	return ret;
}

jint c_object_wrapper::set_int(const char* name, jint value)
{
	cls_get_field_t(
		"I",
		0,
		jvm::env->SetIntField(get_ref(), field_id, value);
	);
}


jdouble c_object_wrapper::call_double(const char* name, c_params params)
{
	cls_get_method_t(
		"()D",
		0.0,
		jdouble ret = jvm::env->CallDoubleMethod(get_ref(), method_id, params.get());
	);

	return ret;
}

lua_Number c_object_wrapper::get_double(const char* name)
{
	cls_get_field_t(
		"D",
		0.0,
		jdouble ret = jvm::env->GetDoubleField(get_ref(), field_id);
	);

	return ret;
}

void c_object_wrapper::set_double(const char* name, jdouble value)
{
	cls_get_field(
		"D",
		jvm::env->SetDoubleField(get_ref(), field_id, value);
	);
}

jfloat c_object_wrapper::call_float(const char* name, c_params params)
{
	cls_get_method_t(
		"()F",
		0.0f,
		jfloat ret = jvm::env->CallFloatMethod(get_ref(), method_id, params.get());
	);

	return ret;
}

jfloat c_object_wrapper::get_float(const char* name)
{
	cls_get_field_t(
		"F",
		0.0f,

		Sleep(1000);
		jfloat ret = jvm::env->GetFloatField(get_ref(), field_id);
	);

	return ret;
}

void c_object_wrapper::set_float(const char* name, jfloat value)
{
	cls_get_field(
		"F",
		jvm::env->SetFloatField(get_ref(), field_id, value);
	);
}


