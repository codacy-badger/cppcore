#pragma once

#include <string>

/////////////////////////////////////////////////////////////////////////////////////////
using CHAR  = char;
using WCHAR = wchar_t;
#ifdef UNICODE
using TCHAR = wchar_t;
#else
using TCHAR = char;
#endif

using LPSTR  = CHAR*;
using LPWSTR = WCHAR*;
using LPTSTR = TCHAR*;

using LPCSTR  = const CHAR*;
using LPCWSTR = const WCHAR*;
using LPCTSTR = const TCHAR*;

namespace std
{
#ifdef UNICODE
	using tstring  = wstring;
	using ntstring = string;
#else
	using tstring  = string;
	using ntstring = wstring;
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////
using HANDLE  = void*;

using LPVOID  = void*;
using LPCVOID = const void*;

/////////////////////////////////////////////////////////////////////////////////////////
#ifdef _MSC_VER
using uint32_t = unsigned __int32;
using uint64_t = unsigned __int64;
using int32_t  =		  __int32;
using int64_t  =		  __int64;

using DWORD   = unsigned long	  ; // For windows definition
using QWORD   = unsigned __int64  ;	// For windows definition
#else
using uint32_t = __uint32_t;
using uint64_t = __uint64_t;
using int32_t  = __int32_t;
using int64_t  = __int64_t;

using DWORD = unsigned int   ; // For 64bits Mac definition.(long size will be 64bits)
using QWORD = __uint64_t     ; // For 64bits Mac definition.(long size will be 64bits)
#endif

using uchar		= unsigned char;
using ushort	= unsigned short;
using uint		= unsigned int;
using ulonglong = uint64_t;

using UCHAR  = unsigned char;
using USHORT = unsigned short;
using UINT   = unsigned int;
using UINT64 = uint64_t;

using INT = int;

using BYTE = unsigned char;
using WORD = unsigned short;
#ifdef _MSC_VER
using DWORD = unsigned long;	// For windows definition
using QWORD = unsigned __int64;	// For windows definition
#else
using DWORD = unsigned int;		// For 64bits Mac definition.(long size will be 64bits)
using QWORD = __uint64_t;		// For 64bits Mac definition.(long size will be 64bits)
#endif

using CBYTE  = const BYTE;
using CWORD  = const WORD;
using CDWORD = const DWORD;
using CQWORD = const QWORD;

using LPBYTE  = BYTE*;
using LPWORD  = WORD*;
using LPCBYTE = CBYTE*; 
using LPDWORD = DWORD*;
using LPQWORD = QWORD*;

using BOOL = int;
using LPBOOL = BOOL*;