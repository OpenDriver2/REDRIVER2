#ifdef _WINDOWS

#include <windows.h>
#include <Dbghelp.h>
#include <tchar.h>
#include <stdio.h>

typedef BOOL(WINAPI *MINIDUMPWRITEDUMP)(HANDLE hProcess, DWORD dwPid, HANDLE hFile, MINIDUMP_TYPE DumpType, CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam, CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam, CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam);


typedef struct exception_codes_s {
	DWORD		exCode;
	const char* exName;
	const char* exDescription;
} exception_codes;

exception_codes except_info[] = {
	{EXCEPTION_ACCESS_VIOLATION,		"ACCESS VIOLATION",
	"The thread tried to read from or write to a virtual address for which it does not have the appropriate access."},

	{EXCEPTION_ARRAY_BOUNDS_EXCEEDED,	"ARRAY BOUNDS EXCEEDED",
	"The thread tried to access an array element that is out of bounds and the underlying hardware supports bounds checking."},

	{EXCEPTION_BREAKPOINT,				"BREAKPOINT",
	"A breakpoint was encountered."},

	{EXCEPTION_DATATYPE_MISALIGNMENT,	"DATATYPE MISALIGNMENT",
	"The thread tried to read or write data that is misaligned on hardware that does not provide alignment. For example, 16-bit values must be aligned on 2-byte boundaries; 32-bit values on 4-byte boundaries, and so on."},

	{EXCEPTION_FLT_DENORMAL_OPERAND,	"FLT DENORMAL OPERAND",
	"One of the operands in a floating-point operation is denormal. A denormal value is one that is too small to represent as a standard floating-point value. "},

	{EXCEPTION_FLT_DIVIDE_BY_ZERO,		"FLT DIVIDE BY ZERO",
	"The thread tried to divide a floating-point value by a floating-point divisor of zero. "},

	{EXCEPTION_FLT_INEXACT_RESULT,		"FLT INEXACT RESULT",
	"The result of a floating-point operation cannot be represented exactly as a decimal fraction. "},

	{EXCEPTION_FLT_INVALID_OPERATION,	"FLT INVALID OPERATION",
	"This exception represents any floating-point exception not included in this list. "},

	{EXCEPTION_FLT_OVERFLOW,			"FLT OVERFLOW",
	"The exponent of a floating-point operation is greater than the magnitude allowed by the corresponding type. "},

	{EXCEPTION_FLT_STACK_CHECK,			"FLT STACK CHECK",
	"The stack overflowed or underflowed as the result of a floating-point operation. "},

	{EXCEPTION_FLT_UNDERFLOW,			"FLT UNDERFLOW",
	"The exponent of a floating-point operation is less than the magnitude allowed by the corresponding type. "},

	{EXCEPTION_ILLEGAL_INSTRUCTION,		"ILLEGAL INSTRUCTION",
	"The thread tried to execute an invalid instruction. "},

	{EXCEPTION_IN_PAGE_ERROR,			"IN PAGE ERROR",
	"The thread tried to access a page that was not present, and the system was unable to load the page. For example, this exception might occur if a network connection is lost while running a program over the network. "},

	{EXCEPTION_INT_DIVIDE_BY_ZERO,		"INT DIVIDE BY ZERO",
	"The thread tried to divide an integer value by an integer divisor of zero. "},

	{EXCEPTION_INT_OVERFLOW,			"INT OVERFLOW",
	"The result of an integer operation caused a carry out of the most significant bit of the result. "},

	{EXCEPTION_INVALID_DISPOSITION,		"INVALID DISPOSITION",
	"An exception handler returned an invalid disposition to the exception dispatcher. Programmers using a high-level language such as C should never encounter this exception. "},

	{EXCEPTION_NONCONTINUABLE_EXCEPTION,"NONCONTINUABLE EXCEPTION",
	"The thread tried to continue execution after a noncontinuable exception occurred. "},

	{EXCEPTION_PRIV_INSTRUCTION,		"PRIV INSTRUCTION",
	"The thread tried to execute an instruction whose operation is not allowed in the current machine mode. "},

	{EXCEPTION_SINGLE_STEP,				"SINGLE STEP",
	"A trace trap or other single-instruction mechanism signaled that one instruction has been executed. "},

	{EXCEPTION_STACK_OVERFLOW,			"STACK OVERFLOW",
	"The thread used up its stack. "}
};


void GetExceptionStrings(DWORD code, const char** pName, const char** pDescription)
{
	int i;
	int count = sizeof(except_info) / sizeof(exception_codes);
	for (i = 0; i < count; i++)
	{
		if (code == except_info[i].exCode)
		{
			*pName = except_info[i].exName;
			*pDescription = except_info[i].exDescription;
			return;
		}
	}

	*pName = "Unknown exception";
	*pDescription = "n/a";
}

extern char* g_appNameStr;

void CreateMiniDump(struct _EXCEPTION_POINTERS* exceptionInfo)
{
	char tmpStr[256];

	sprintf(tmpStr, "%s.dmp", g_appNameStr);
	
	HMODULE mhLib = LoadLibraryA("dbghelp.dll");
	MINIDUMPWRITEDUMP pDump = (MINIDUMPWRITEDUMP)::GetProcAddress(mhLib, "MiniDumpWriteDump");
	HANDLE  hFile = CreateFileA(tmpStr, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	_MINIDUMP_EXCEPTION_INFORMATION ExInfo;
	ExInfo.ThreadId = GetCurrentThreadId();
	ExInfo.ExceptionPointers = exceptionInfo;
	ExInfo.ClientPointers = FALSE;

	pDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &ExInfo, NULL, NULL);
	CloseHandle(hFile);
}

LONG WINAPI unhandled_handler(struct _EXCEPTION_POINTERS* exceptionInfo)
{
	EXCEPTION_RECORD* pRecord = exceptionInfo->ExceptionRecord;

	const char* pName, * pDescription;
	GetExceptionStrings(pRecord->ExceptionCode, &pName, &pDescription);

	char tmp[2048];
	sprintf(tmp, "Exception code: %s (0x%x)\nAddress: %p\n\n\n",
							pName, pRecord->ExceptionCode, pRecord->ExceptionAddress);

	if (pRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION)
	{
		if (pRecord->ExceptionInformation[0])
		{
			sprintf(tmp, "%s (0x%x)\nAddress: %p\n\n\nThe thread attempted to write to an inaccessible address %p\nMinidump '%s.dmp' will be saved.", 
				pName, pRecord->ExceptionCode, pRecord->ExceptionAddress, pRecord->ExceptionInformation[1], g_appNameStr);
		}
		else
		{
			sprintf(tmp, "%s (0x%x)\nAddress: %p\n\n\nThe thread attempted to read the inaccessible data at %p\nMinidump '%s.dmp' will be saved.", 
				pName, pRecord->ExceptionCode, pRecord->ExceptionAddress, pRecord->ExceptionInformation[1], g_appNameStr);
		}
	}
	else
	{
		sprintf(tmp, "%s (0x%x)\nAddress: %p\n\n\nMinidump '%s.dmp' will be saved.",
			pName, pRecord->ExceptionCode, pRecord->ExceptionAddress, g_appNameStr);
	}

	MessageBoxA(NULL, tmp, "Unhandled exception!", MB_OK | MB_ICONERROR);
	
	CreateMiniDump(exceptionInfo);
	
	return EXCEPTION_CONTINUE_SEARCH;
}

typedef LONG(WINAPI* EXCEPTHANDLER)(EXCEPTION_POINTERS* ExceptionInfo);
static EXCEPTHANDLER oldHandler = NULL;
static int handler_installed = 0;

static _purecall_handler oldPureCall = NULL;

void pure_call_handler()
{
	MessageBoxA(NULL, "Pure virtual function call", "FATAL ERROR", MB_OK | MB_ICONERROR);
}

void InstallExceptionHandler()
{
	oldHandler = SetUnhandledExceptionFilter(unhandled_handler);

	oldPureCall = _get_purecall_handler();
	_set_purecall_handler(pure_call_handler);

	handler_installed = 1;
}


void UnInstallExceptionHandler()
{
	if (handler_installed)
	{
		SetUnhandledExceptionFilter(oldHandler);
		_set_purecall_handler(oldPureCall);
	}
}

#else

void InstallExceptionHandler()
{
	
}

void UnInstallExceptionHandler()
{

}

#endif