#ifndef CRASHHANDLER_H
#define CRASHHANDLER_H

#if defined (_WINDOWS)
#include <windows.h>
#include <tchar.h>

LONG WINAPI unhandled_handler(struct _EXCEPTION_POINTERS* apExceptionInfo);
#endif

#endif