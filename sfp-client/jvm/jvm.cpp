#include "jvm.h"

JavaVM* jvm::vm;
JNIEnv* jvm::env;

int jvm::init()
{
	if (vm != nullptr && env != nullptr)
	{
		std::cout << "JVM Wrapper was already initialized";
		return JNI_OK;
	}

	auto ret = JNI_GetCreatedJavaVMs(&vm, 1, nullptr);

	if (ret != JNI_OK)
		return ret;

	ret = vm->AttachCurrentThread(reinterpret_cast<void**>(&env), nullptr);

	if (ret != JNI_OK)
		return ret;

	ret = vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_8);

	if (ret != JNI_OK)
		return ret;

	return JNI_OK;
}

c_class_wrapper* jvm::find_class(const char* name)
{
	if (vm == nullptr || env == nullptr)
	{
		std::cout << "JVM Wrapper wasn't initialized" << std::endl;
		return nullptr;
	}

	auto wrapper = new c_class_wrapper(name);

	if (wrapper->is_valid())
		return wrapper;

	return nullptr;
}