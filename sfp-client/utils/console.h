#pragma once

#include <Windows.h>

namespace console
{
	extern HANDLE _out, _old_out;
    extern HANDLE _err, _old_err;
    extern HANDLE _in, _old_in;

    void alloc();
    void dealloc();
    bool print(const char* fmt, ...);
}