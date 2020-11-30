#include "c_class_wrapper.h"

#include "../../jvm.h"

// gets + validates field id
// runs the provided code block
// deletes class reference
#define cls_get_field(field_desc, ...)			jclass ref =  get_ref();															\
												if (ref == NULL) return;															\
												jfieldID field_id = g_jvm->get_env()->GetFieldID(ref, name, field_desc);			\
												if (field_id == NULL) return;														\
												__VA_ARGS__;  																		\
												g_jvm->get_env()->DeleteLocalRef(ref);

// gets + validates method id
// runs the provided code block
// deletes class reference
#define cls_get_method(method_desc, ...)		jclass ref =  get_ref();															\
												if (ref == NULL) return;														    \
												jmethodID method_id = g_jvm->get_env()->GetStaticMethodID(ref, name, method_desc);  \
												if (method_id == NULL) return;													    \
												__VA_ARGS__;	     															    \
												g_jvm->get_env()->DeleteLocalRef(ref);

inline jclass c_class_wrapper::get_ref()
{
	return g_jvm->get_env()->FindClass(name);
}

inline void c_class_wrapper::del_ref(jclass ref)
{
	g_jvm->get_env()->DeleteLocalRef(ref);
}

const char* c_class_wrapper::get_name()
{
	return name;
}

std::unique_ptr<c_object_wrapper> c_class_wrapper::call_static_object(const char* name, const char* ret_class, const jvalue* args)
{
	cls_get_method(
		(std::string(std::string("()L") + ret_class)).c_str(),
		jobject ret = g_jvm->get_env()->CallStaticObjectMethod(ref, method_id, args);
	);

	return std::make_unique<c_object_wrapper>(new c_object_wrapper(ret));
}

std::unique_ptr<c_object_wrapper> c_class_wrapper::get_static_object(const char* name, const char* ret_class)
{
	cls_get_field(
		(std::string(std::string("L") + ret_class)).c_str(),
		jobject ret = g_jvm->get_env()->GetStaticObjectField(ref, field_id); 
	);

	return std::make_unique<c_object_wrapper>(new c_object_wrapper(ret));
}

void c_class_wrapper::set_static_object(const char* name, const char* ret_class, jobject value)
{
	cls_get_field(
		(std::string(std::string("L") + ret_class)).c_str(),
		g_jvm->get_env()->SetStaticObjectField(ref, field_id, value);
	);
}

jdouble c_class_wrapper::call_static_double(const char* name, const jvalue* args)
{
	cls_get_method(
		"()Ljava/lang/Double",
		jdouble ret = g_jvm->get_env()->CallStaticDoubleMethod(ref, method_id, args);
	);

	return ret;
}

jdouble c_class_wrapper::get_static_double(const char* name)
{
	cls_get_field(
		"Ljava/lang/Double",
		jdouble ret = g_jvm->get_env()->GetStaticDoubleField(ref, field_id);
	);

	return ret;
}

void c_class_wrapper::set_static_double(const char* name, jdouble value)
{
	cls_get_field(
		"Ljava/lang/Double",
		g_jvm->get_env()->SetStaticDoubleField(ref, field_id, value);
	);
}



