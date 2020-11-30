#include "c_object_wrapper.h"

#include "../../jvm.h"

// gets + validates field id
// runs the provided code block
// deletes class reference
#define cls_get_field(custom_desc, ...)		jclass class_ref =  g_jvm->get_env()->GetObjectClass(ref);						    \
												if (class_ref == NULL) return;														\
												jfieldID field_id = g_jvm->get_env()->GetFieldID(class_ref, name, custom_desc);     \
												if (field_id == NULL) return;														\
												__VA_ARGS__;  																		\
												g_jvm->get_env()->DeleteLocalRef(class_ref);

// gets + validates method id
// runs the provided code block
// deletes class reference
#define cls_get_method(custom_desc, ...)		jclass class_ref =  g_jvm->get_env()->GetObjectClass(ref);							\
												if (class_ref == NULL) return;														\
												jmethodID method_id = g_jvm->get_env()->GetMethodID(class_ref, name, custom_desc);  \
												if (method_id == NULL) return;														\
												__VA_ARGS__;	     																\
												g_jvm->get_env()->DeleteLocalRef(class_ref);

inline void c_object_wrapper::destroy()
{
	g_jvm->get_env()->DeleteLocalRef(ref);
}

std::unique_ptr<c_object_wrapper> c_object_wrapper::call_object(const char* name, const char* ret_class, const jvalue* args)
{
	cls_get_method(
		(std::string(std::string("()L") + ret_class)).c_str(),
		jobject ret = g_jvm->get_env()->CallObjectMethod(ref, method_id, args);
	);

	return std::make_unique<c_object_wrapper>(new c_object_wrapper(ret));
}

std::unique_ptr<c_object_wrapper> c_object_wrapper::get_object(const char* name, const char* ret_class)
{
	cls_get_field(
		(std::string(std::string("L") + ret_class)).c_str(),
		jobject ret = g_jvm->get_env()->GetObjectField(ref, field_id);
	);

	return std::make_unique<c_object_wrapper>(new c_object_wrapper(ret));
}

void c_object_wrapper::set_object(const char* name, const char* ret_class, jobject value)
{
	cls_get_field(
		(std::string(std::string("L") + ret_class)).c_str(),
		g_jvm->get_env()->SetObjectField(ref, field_id, value);
	);
}

jdouble c_object_wrapper::call_double(const char* name, const jvalue* args)
{
	cls_get_method(
		"()Ljava/lang/Double",
		jdouble ret = g_jvm->get_env()->CallDoubleMethod(ref, method_id, args);
	);

	return ret;
}

jdouble c_object_wrapper::get_double(const char* name)
{
	cls_get_field(
		"Ljava/lang/Double",
		jdouble ret = g_jvm->get_env()->GetDoubleField(ref, field_id);
	);

	return ret;
}

void c_object_wrapper::set_double(const char* name, jdouble value)
{
	cls_get_field(
		"Ljava/lang/Double",
		g_jvm->get_env()->SetDoubleField(ref, field_id, value);
	);
}

jfloat c_object_wrapper::call_float(const char* name, const jvalue* args)
{
	cls_get_method(
		"()Ljava/lang/Float",
		jdouble ret = g_jvm->get_env()->CallFloatMethod(ref, method_id, args);
	);

	return ret;
}

jfloat c_object_wrapper::get_float(const char* name)
{
	cls_get_field(
		"Ljava/lang/Float",
		jdouble ret = g_jvm->get_env()->GetFloatField(ref, field_id);
	);

	return ret;
}

void c_object_wrapper::set_float(const char* name, jfloat value)
{
	cls_get_field(
		"Ljava/lang/Float",
		g_jvm->get_env()->SetFloatField(ref, field_id, value);
	);
}



