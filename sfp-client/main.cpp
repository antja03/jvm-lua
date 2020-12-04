#include <windows.h>

#include "jvm/jvm.h"
#include "executor/executor.h"
 
void print(const char* msg) { std::cout << msg << std::endl; }
void sleep(int ms) { Sleep(ms); }

DWORD WINAPI OnDllAttach(LPVOID base)
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	jvm::init();
	executor::initialize();

	luaL_openlibs(executor::state);

	luabridge::getGlobalNamespace(executor::state)
		.addFunction("cout", print)
		.addFunction("schleep", sleep)
		.beginNamespace("jvm")
			.addFunction("find_class", jvm::find_class)
			.beginClass<c_params>("c_params")
				.addConstructor<void (*) (void)>()
				.addFunction("empty", &c_params::empty)
				.addFunction("push_object", &c_params::push_object)
				.addFunction("push_int", &c_params::push_int)
				.addFunction("push_float", &c_params::push_float)
			.endClass()
			.beginClass<c_class_wrapper>("c_class_wrapper")
				.addFunction("is_valid", &c_class_wrapper::is_valid)
				.addFunction("call_static_object", &c_class_wrapper::call_static_object)
				.addFunction("get_static_object", &c_class_wrapper::get_static_object)
				.addFunction("set_static_object", &c_class_wrapper::set_static_object)
				.addFunction("call_static_double", &c_class_wrapper::call_static_double)
				.addFunction("get_static_double", &c_class_wrapper::get_static_double)
				.addFunction("set_static_double", &c_class_wrapper::set_static_double)
				.addFunction("get_static_int", &c_class_wrapper::get_static_int)
			.endClass()
			.beginClass<c_object_wrapper>("c_object_wrapper")
				.addFunction("is_valid", &c_object_wrapper::is_valid)
				.addFunction("destroy", &c_object_wrapper::destroy)
				.addFunction("call_void", &c_object_wrapper::call_void)
				.addFunction("call_object", &c_object_wrapper::call_object)
				.addFunction("get_object", &c_object_wrapper::get_object)
				.addFunction("set_object", &c_object_wrapper::set_object)
				.addFunction("call_int", &c_object_wrapper::call_int)
				.addFunction("get_int", &c_object_wrapper::get_int)
				.addFunction("set_int", &c_object_wrapper::set_int)
				.addFunction("call_double", &c_object_wrapper::call_double)
				.addFunction("get_double", &c_object_wrapper::get_double)
				.addFunction("set_double", &c_object_wrapper::set_double)
				.addFunction("call_float", &c_object_wrapper::call_float)
				.addFunction("get_float", &c_object_wrapper::get_float)
				.addFunction("set_float", &c_object_wrapper::set_float)
			.endClass()
		.endNamespace();


	lua_getglobal(executor::state, "package");
	lua_getfield(executor::state, -1, "path"); // get field "path" from table at top of stack (-1)
	std::string cur_path = lua_tostring(executor::state, -1); // grab path string from top of stack
	cur_path.append(";"); // do your path magic here
	cur_path.append(R"(D:/Development/fs-lua-libs/?.lua)");
	lua_pop(executor::state, 1); // get rid of the string on the stack we just pushed on line 5
	lua_pushstring(executor::state, cur_path.c_str()); // push the new one
	lua_setfield(executor::state, -2, "path"); // set the field "path" in table at -2 with value at top of stack
	lua_pop(executor::state, 1); // get rid of package table from top of stack

	int ret = luaL_dofile(executor::state, "D:\\Development\\fs-lua-libs\\script.lua");

	if (ret != 0)
	{
		printf("Error: %s", lua_tostring(executor::state, -1));
	}

	try 
	{
		luabridge::LuaRef main = luabridge::getGlobal(executor::state, "main");
		main();
	}
	catch (luabridge::LuaException const& e)
	{
		
		std::cout << e.what() << std::endl;
	}

	// Close lua state
	lua_close(executor::state);

	while (!GetAsyncKeyState(VK_INSERT))
		Sleep(5);

	FreeLibraryAndExitThread((HINSTANCE) base, 0);
}

BOOL WINAPI OnDllDetach()
{
	fclose(reinterpret_cast<FILE*>(stdout));
	FreeConsole();
	return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hinstDLL);
        CreateThread(nullptr, 0, OnDllAttach, hinstDLL, 0, nullptr);
        return TRUE;
    case DLL_PROCESS_DETACH:
        if (lpReserved == nullptr)
            return OnDllDetach();
		return TRUE;
	default:
		return TRUE;
    }
}

