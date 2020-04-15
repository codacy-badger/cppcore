#include "CStrLegacy.h"
#include <string.h>
#include <algorithm>

namespace core
{
	bool IsWhiteSpace(TCHAR cChar)
	{
		if (TEXT(' ') == cChar)
			return true;
		if (TEXT('\t') == cChar)
			return true;
		if (TEXT('\n') == cChar)
			return true;
		if (TEXT('\r') == cChar)
			return true;
		if (TEXT('\b') == cChar)
			return true;
		return false;
	}

	int SafeStrLen(LPCTSTR tcsContext, size_t tMaxCch)
	{
		size_t i = 0;
		for (i = 0; i < tMaxCch; i++)
		{
			if (tcsContext[i] == NULL)
				break;
		}
		return static_cast<int>(i);
	}

	TCHAR* SafeStrCpy(LPTSTR tcsDest, size_t tDestCch, LPCTSTR tcsSrc)
	{
		if (0 == tDestCch)
			return tcsDest;
		
		const size_t tSrcCch = SafeStrLen(tcsSrc, tDestCch);
		const size_t tCopyLen = std::min(tSrcCch, tDestCch);
		memcpy(tcsDest, tcsSrc, tCopyLen * sizeof(TCHAR));

		const size_t tNullIndex = std::min(tDestCch - 1, tCopyLen);
		tcsDest[tNullIndex] = NULL;
		return tcsDest;
	}

	TCHAR* SafeStrCat(LPTSTR tcsDest, size_t tDestCch, LPCTSTR tcsSrc)
	{
		if (0 == tDestCch)
			return tcsDest;

		const size_t tIdxToCat = SafeStrLen(tcsDest, tDestCch);
		return SafeStrCpy(tcsDest + tIdxToCat, tDestCch - tIdxToCat, tcsSrc);
	}

	static inline bool StrExactMatchWorker(LPCTSTR tcsDest, LPCTSTR tcsSrc, size_t tLen)
	{
		for (size_t i = 0; i < tLen; i++)
		{
			if (tcsDest[i] != tcsSrc[i])
				return false;
		}
		return true;
	}

	LPCTSTR SafeStrStr(LPCTSTR tcsDest, size_t tDestCch, LPCTSTR tcsSubStr)
	{
		const size_t tSubStrCch = SafeStrLen(tcsSubStr, tDestCch);
		if (tDestCch < tSubStrCch)
			return NULL;

		const size_t tMaxDestSearchLen = tDestCch - tSubStrCch + 1;
		for (size_t i = 0; i < tMaxDestSearchLen; i++)
		{
			if (StrExactMatchWorker(tcsDest + i, tcsSubStr, tSubStrCch))
				return tcsDest + i;
		}
		return NULL;
	}

	int SafeSPrintf(LPTSTR tcsDest, size_t tDestCch, LPCTSTR tcsFormat, ...)
	{
		va_list list;
		va_start(list, tcsFormat);
		const ECODE nRet = SafeSVPrintf(tcsDest, tDestCch, tcsFormat, list);
		va_end(list);

		if (nRet >= static_cast<int>(tDestCch))
		{
			tcsDest[tDestCch - 1] = 0;
			return -1;
		}
		return nRet;
	}

	int SafeSVPrintf(LPTSTR tcsDest, size_t tDestCch, LPCTSTR tcsFormat, va_list vaList)
	{
	#if defined (_MSC_VER) & defined(UNICODE)
		std::tstring strFormat(pszFormat);
		size_t tLength = strFormat.length();

		for (size_t i = 0; (i + 1) < tLength; i++)
		{
			if (TEXT('%') != strFormat[i])
				continue;

			switch (strFormat[i+1])
			{
			case TEXT('s'): strFormat[i+1] = TEXT('S'); break;
			case TEXT('S'): strFormat[i+1] = TEXT('s'); break;
			}
		}
		int nRet = vsntprintf(tcsDest, tDestCch, strFormat.c_str(), vaList);
	#else
		int nRet = vsntprintf(tcsDest, tDestCch, tcsFormat, vaList);
	#endif
		if (nRet < 0)	     // Windows returns -1 when buffer is not sufficent
			return nRet;
		if (nRet > tDestCch) // Linux returns size of buffer needed when buffer is not sufficent
			return -1;
		return nRet;
	}

	size_t SafeFindStr(LPCTSTR tcsDest, size_t tCchDest, LPCTSTR tcsKey)
	{
		const size_t tCchKey = SafeStrLen(tcsKey, tCchDest);
		if (tCchKey > tCchDest)
			return -1;
		
		const int nMaxDestSearchLen = static_cast<int>(tCchDest) - static_cast<int>(tCchKey) + 1;
		for (int i = 0; i < nMaxDestSearchLen; i++)
		{
			if (StrExactMatchWorker(tcsDest + i, tcsKey, tCchKey))
				return i;
		}
		return -1;
	}

	int SafeStrCmp(LPCTSTR tcsSrc, LPCTSTR tcsTarget, size_t tMaxCch)
	{
		size_t i;
		for (i = 0; i < tMaxCch && tcsSrc[i] && tcsTarget[i]; i++)
		{
			const TCHAR tcSrc = tcsSrc[i];
			const TCHAR tcTarget = tcsTarget[i];
			if (tcSrc < tcTarget)
				return -1;
			if (tcSrc > tcTarget)
				return 1;
		}

		if (tMaxCch == i)
			return 0;

		if (tcsSrc[i] < tcsTarget[i])
			return -1;
		if (tcsSrc[i] > tcsTarget[i])
			return 1;
		return 0;
	}
}