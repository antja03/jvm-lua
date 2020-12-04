#include "c_class_wrapper.h"

#include "../../jvm.h"

// gets + validates field id
// runs the provided code block
// deletes class reference
#define cls_get_field(field_desc, ...)					jclass ref =  get_ref();															\
														if (ref == NULL) return;															\
														jfieldID field_id = jvm::env->GetStaticFieldID(ref, name, field_desc);				\
														if (field_id == NULL) return;														\
														__VA_ARGS__;  																		\
														jvm::env->DeleteLocalRef(ref);

#define cls_get_field_o(field_desc, ...)				jclass ref =  get_ref();															\
														if (ref == NULL) return nullptr;													\
														jfieldID field_id = jvm::env->GetStaticFieldID(ref, name, field_desc);				\
														if (field_id == NULL) return nullptr;												\
														__VA_ARGS__;  																		\
														jvm::env->DeleteLocalRef(ref);

#define cls_get_field_t(field_desc, ret_val, ...)		jclass ref =  get_ref();															\
														if (ref == NULL) return ret_val;													\
														jfieldID field_id = jvm::env->GetStaticFieldID(ref, name, field_desc);				\
														if (field_id == NULL) return ret_val;												\
														__VA_ARGS__;  																		\
														jvm::env->DeleteLocalRef(ref);

// gets + validates method id
// runs the provided code block
// deletes class reference
#define cls_get_method(method_desc, ...)				jclass ref =  get_ref();															\
														if (ref == NULL) return;															\
														jmethodID method_id = jvm::env->GetStaticMethodID(ref, name, method_desc);			\
														if (method_id == NULL) return;														\
														__VA_ARGS__;	     															    \
														jvm::env->DeleteLocalRef(ref);

#define cls_get_method_o(method_desc, ...)				jclass ref =  get_ref();															\
														if (ref == NULL) return nullptr;													\
														jmethodID method_id = jvm::env->GetStaticMethodID(ref, name, method_desc);			\
														if (method_id == NULL) return nullptr;												\
														__VA_ARGS__;	     															    \
														jvm::env->DeleteLocalRef(ref);

#define cls_get_method_t(method_desc, ret_val, ...)		jclass ref =  get_ref();															\
														if (ref == NULL) return ret_val;													\
														jmethodID method_id = jvm::env->GetStaticMethodID(ref, name, method_desc);			\
														if (method_id == NULL) return ret_val;												\
														__VA_ARGS__;	     															    \
														jvm::env->DeleteLocalRef(ref);

inline jclass c_class_wrapper::get_ref()
{
	return jvm::env->FindClass(name);
}

inline void c_class_wrapper::del_ref(jclass ref)
{
	jvm::env->DeleteLocalRef(ref);
}

const char* c_class_wrapper::get_name()
{
	return name;
}

bool c_class_wrapper::is_valid()
{
	jclass ref = get_ref();
	
	if (ref == 0)
		return false;

	del_ref(ref);
	return true;
}

void c_class_wrapper::call_static_void(const char* name, c_params* params)
{
	cls_get_method(
		"()V",
		jvm::env->CallStaticVoidMethodA(ref, method_id, params->get());
	)
}

c_object_wrapper* c_class_wrapper::call_static_object(const char* name, const char* ret_class)
{
	cls_get_method_o(
		(std::string(std::string("()L") + ret_class + ";")).c_str(),
		jobject ret = jvm::env->CallStaticObjectMethod(ref, method_id);
	);

	auto wrapper = new c_object_wrapper(ret);

	if (!wrapper->is_valid())
		return nullptr;

	return wrapper;
}

c_object_wrapper* c_class_wrapper::get_static_object(const char* name, const char* ret_class)
{
	cls_get_field_o(
		(std::string(std::string("L") + ret_class + ";")).c_str(),
		jobject ret = jvm::env->GetStaticObjectField(ref, field_id); 
	);

	return new c_object_wrapper(ret);
}

void c_class_wrapper::set_static_object(const char* name, const char* ret_class, jobject value)
{
	cls_get_field(
		(std::string(std::string("L") + ret_class + ";")).c_str(),
		jvm::env->SetStaticObjectField(ref, field_id, value);
	);
}

jdouble c_class_wrapper::call_static_double(const char* name, const jvalue* args)
{
	cls_get_method_t(
		"()Ljava/lang/Double;",
		0.0,
		jdouble ret = jvm::env->CallStaticDoubleMethod(ref, method_id, args);
	);

	return ret;
}

jdouble c_class_wrapper::get_static_double(const char* name)
{
	cls_get_field_t(
		"Ljava/lang/Double;",
		0.0,
		jdouble ret = jvm::env->GetStaticDoubleField(ref, field_id);
	);

	return ret;
}

void c_class_wrapper::set_static_double(const char* name, jdouble value)
{
	cls_get_field(
		"Ljava/lang/Double;",
		jvm::env->SetStaticDoubleField(ref, field_id, value);
	);
}

jint c_class_wrapper::get_static_int(const char* name)
{
	cls_get_field_t(
		"I",
		0,
		jint ret = jvm::env->GetStaticIntField(ref, field_id)
	)

	return ret;
}



