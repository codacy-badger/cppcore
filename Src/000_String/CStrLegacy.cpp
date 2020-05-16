#include "CStrLegacy.h"
#include <string.h>
#include <stack>
#include <algorithm>

namespace core
{
	////////////////////////////////////////////////////////////////////////////////////////
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

	////////////////////////////////////////////////////////////////////////////////////////
	int SafeStrLen(LPCTSTR tcsContext, size_t tMaxCch)
	{
		size_t i = 0;
		for (i = 0; i < tMaxCch; i++)
		{
			if (tcsContext[i] == 0)
				break;
		}
		return static_cast<int>(i);
	}

	////////////////////////////////////////////////////////////////////////////////////////
	TCHAR* SafeStrCpy(LPTSTR tcsDest, size_t tDestCch, LPCTSTR tcsSrc)
	{
		if (0 == tDestCch)
			return tcsDest;
		
		const size_t tSrcCch = SafeStrLen(tcsSrc, tDestCch);
		const size_t tCopyLen = std::min(tSrcCch, tDestCch);
		memcpy(tcsDest, tcsSrc, tCopyLen * sizeof(TCHAR));

		const size_t tNullIndex = std::min(tDestCch - 1, tCopyLen);
		tcsDest[tNullIndex] = 0;
		return tcsDest;
	}

	////////////////////////////////////////////////////////////////////////////////////////
	TCHAR* SafeStrCat(LPTSTR tcsDest, size_t tDestCch, LPCTSTR tcsSrc)
	{
		if (0 == tDestCch)
			return tcsDest;

		const size_t tIdxToCat = SafeStrLen(tcsDest, tDestCch);
		return SafeStrCpy(tcsDest + tIdxToCat, tDestCch - tIdxToCat, tcsSrc);
	}

	////////////////////////////////////////////////////////////////////////////////////////
	static inline bool StrExactMatchWorker(LPCTSTR tcsDest, LPCTSTR tcsSrc, size_t tLen)
	{
		for (size_t i = 0; i < tLen; i++)
		{
			if (tcsDest[i] != tcsSrc[i])
				return false;
		}
		return true;
	}

	////////////////////////////////////////////////////////////////////////////////////////
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

	////////////////////////////////////////////////////////////////////////////////////////
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

	////////////////////////////////////////////////////////////////////////////////////////
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
		if ((size_t)nRet > tDestCch) // Linux returns size of buffer needed when buffer is not sufficent
			return -1;
		return nRet;
	}

	////////////////////////////////////////////////////////////////////////////////////////
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

	////////////////////////////////////////////////////////////////////////////////////////
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

	////////////////////////////////////////////////////////////////////////////////////////
	static inline void TokenizeWildCardPattern(std::tstring strWildCard, std::vector<std::tstring>& vecTokens)
	{
		static const std::tstring s_WildCards = TEXT("?*");
		size_t tBeginIndex = 0;
		size_t i;
		for (i = 0; i < strWildCard.size(); i++)
		{
			const TCHAR cCurChar = strWildCard.at(i);
			if (std::tstring::npos == s_WildCards.find(cCurChar))
				continue;

			if (tBeginIndex != i)
				vecTokens.push_back(strWildCard.substr(tBeginIndex, i - tBeginIndex));

			TCHAR szToken[2] = { cCurChar, 0 };
			vecTokens.push_back(szToken);
			tBeginIndex = i + 1;
			continue;
		}

		if (tBeginIndex != i)
			vecTokens.push_back(strWildCard.substr(tBeginIndex));
	}

	////////////////////////////////////////////////////////////////////////////////////////
	struct ST_WILDCARDSEARCH
	{
		size_t tWildCardPos;
		size_t tContextPos;

		ST_WILDCARDSEARCH(void) : tWildCardPos(0), tContextPos(0) {}
		ST_WILDCARDSEARCH(size_t w, size_t c) : tWildCardPos(w), tContextPos(c) {}
	};

	////////////////////////////////////////////////////////////////////////////////////////
	bool SafeStrCmpWithWildcard(LPCTSTR pszDest, size_t tDestCch, LPCTSTR pszPattern)
	{
		std::vector<std::tstring> vecPatternTokens;
		TokenizeWildCardPattern(pszPattern, vecPatternTokens);

		std::stack<ST_WILDCARDSEARCH> stackSearchingScenario;
		stackSearchingScenario.push(ST_WILDCARDSEARCH(0, 0));
		while (!stackSearchingScenario.empty())
		{
			ST_WILDCARDSEARCH stCur = stackSearchingScenario.top();
			stackSearchingScenario.pop();

			bool bAsteriskMark = false;
			size_t tQuestionMarkCount = 0;

			for (; stCur.tWildCardPos < vecPatternTokens.size(); stCur.tWildCardPos++)
			{
				const std::tstring& strPatternToken = vecPatternTokens[stCur.tWildCardPos];
				if (TEXT("*") == strPatternToken)
				{
					bAsteriskMark = true;
					continue;
				}

				if (TEXT("?") == strPatternToken)
				{
					if (bAsteriskMark)
					{
						tQuestionMarkCount++;
						continue;
					}

					// failure, one charactor wildcard is exceeding context length
					if (stCur.tContextPos + 1 > tDestCch)
						break;
					stCur.tContextPos++;
					continue;
				}

				if (bAsteriskMark)
				{
					// failure, question mark was exceeded remaining context length
					if (stCur.tContextPos + tQuestionMarkCount > tDestCch)
						break;

					stCur.tContextPos += tQuestionMarkCount;
					tQuestionMarkCount = 0;

					do
					{
						int nIndex = SafeFindStr(pszDest + stCur.tContextPos, tDestCch - stCur.tContextPos, strPatternToken.c_str());
						if (nIndex < 0)
							break;

						stCur.tContextPos += nIndex;
						stackSearchingScenario.push(stCur);
						stCur.tContextPos += strPatternToken.length();
					} while (stCur.tContextPos < tDestCch);
					break;
				}

				// failure, token text is exceeding context length
				if (stCur.tContextPos + strPatternToken.length() > tDestCch)
					break;

				// failure, token text is matched to context
				if (SafeStrCmp(pszDest + stCur.tContextPos, strPatternToken.c_str(), strPatternToken.length()))
					break;

				stCur.tContextPos += strPatternToken.length();
			}

			if (stCur.tWildCardPos == vecPatternTokens.size())
			{
				if (stCur.tContextPos == tDestCch)
					return true;

				if (bAsteriskMark && (stCur.tContextPos + tQuestionMarkCount <= tDestCch))
					return true;
			}
		}

		return false;
	}
}