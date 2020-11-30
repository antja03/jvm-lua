#include "jvm.h"

int c_jvm_wrapper::init()
{
	auto ret = JNI_GetCreatedJavaVMs(&vm, 1, nullptr);

	if (ret != JNI_OK)
		return ret;
		
	ret = get_vm()->AttachCurrentThread(reinterpret_cast<void**>(&env), nullptr);

	if (ret != JNI_OK)
		return ret;

	ret = get_vm()->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_8);

	if (ret != JNI_OK)
		return ret;

	return JNI_OK;
}

inline std::unique_ptr<c_class_wrapper> c_jvm_wrapper::find_class(const char* name)
{
	return std::make_unique<c_class_wrapper>(new c_class_wrapper(name));
}

std::unique_ptr<c_jvm_wrapper> g_jvm = std::make_unique<c_jvm_wrapper>(new c_jvm_wrapper());

