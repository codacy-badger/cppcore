#include "CStrLegacy.h"
#include <string.h>

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
}