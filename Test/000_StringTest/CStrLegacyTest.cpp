#include "pch.h"
#include "../../Src/000_String/CStrLegacy.h"

using namespace core;

constexpr size_t MAX_BUFFER_SIZE = 30;

TEST(CStrLegacyTest, IsWhiteSpace_return_true_on_whitespace_input)
{
	EXPECT_TRUE(IsWhiteSpace(TEXT(' ')));
	EXPECT_TRUE(IsWhiteSpace(TEXT('\n')));
	EXPECT_TRUE(IsWhiteSpace(TEXT('\t')));
	EXPECT_TRUE(IsWhiteSpace(TEXT('\r')));
	EXPECT_TRUE(IsWhiteSpace(TEXT('\b')));
}

TEST(CStrLegacyTest, IsWhiteSpace_return_false_on_other_input)
{
	EXPECT_FALSE(IsWhiteSpace(TEXT('a')));
	EXPECT_FALSE(IsWhiteSpace(TEXT('Z')));
	EXPECT_FALSE(IsWhiteSpace(TEXT('%')));
	EXPECT_FALSE(IsWhiteSpace(TEXT('-')));
}

TEST(CStrLegacyTest, SafeStrLen_return_value_within_max_cch)
{
	EXPECT_EQ(3, SafeStrLen(TEXT("123"), 10));
	EXPECT_EQ(8, SafeStrLen(TEXT("123 5678"), 10));
}

TEST(CStrLegacyTest, SafeStrLen_return_value_on_edged_max_cch)
{
	EXPECT_EQ(0, SafeStrLen(TEXT(""), 1));
	EXPECT_EQ(3, SafeStrLen(TEXT("12345"), 3));
	EXPECT_EQ(5, SafeStrLen(TEXT("12345"), 5));
}

TEST(CStrLegacyTest, SafeStrCpy_strcpy_within_max_cch)
{
	LPTSTR pszDestBuffer = new TCHAR[MAX_BUFFER_SIZE];
	LPCTSTR pszSrcStr = TEXT("string to copy");

	EXPECT_STRNE(pszDestBuffer, pszSrcStr);
	EXPECT_EQ(pszDestBuffer, SafeStrCpy(pszDestBuffer, MAX_BUFFER_SIZE, pszSrcStr));
	EXPECT_STREQ(pszDestBuffer, pszSrcStr);
}

TEST(CStrLegacyTest, SafeStrCat_strcat_within_max_cch)
{
	LPTSTR pszDestBuffer = new TCHAR[MAX_BUFFER_SIZE];
	
	SafeStrCpy(pszDestBuffer, MAX_BUFFER_SIZE, TEXT("string"));
	SafeStrCat(pszDestBuffer, MAX_BUFFER_SIZE, TEXT("cat"));
	EXPECT_STREQ(pszDestBuffer, TEXT("stringcat"));
}

TEST(CStrLegacyTest, SafeStrStr_strstr_within_max_cch)
{
	LPCTSTR pszDest		 = TEXT("123cat789cat");
	LPCTSTR pszKeyToFind = TEXT("cat");
	LPCTSTR pszExpected  = TEXT("cat789cat");

	LPCTSTR tcsStrFound = SafeStrStr(pszDest, MAX_BUFFER_SIZE, pszKeyToFind);
	EXPECT_STREQ(tcsStrFound, pszExpected);
}

TEST(CStrLegacyTest, SafeSPrintf_sprintf_within_max_cch)
{
	LPTSTR tcsDestBuffer = new TCHAR[MAX_BUFFER_SIZE];
	
	SafeSPrintf(tcsDestBuffer, MAX_BUFFER_SIZE, TEXT("%s %d"), TEXT("string"), 10);
	EXPECT_STREQ(tcsDestBuffer, TEXT("string 10"));
}

TEST(CStrLegacyTest, SafeFindStr_findstr_within_max_cch)
{
	LPCTSTR tcsDestStr = TEXT("123 cat apple");

	EXPECT_EQ(0, SafeFindStr(tcsDestStr, MAX_BUFFER_SIZE, TEXT("123")));
	EXPECT_EQ(4, SafeFindStr(tcsDestStr, MAX_BUFFER_SIZE, TEXT("cat")));
	EXPECT_EQ(8, SafeFindStr(tcsDestStr, MAX_BUFFER_SIZE, TEXT("apple")));
}

TEST(CStrLegacyTest, SafeStrCmp_strcmp_within_max_cch)
{
	EXPECT_EQ(0, SafeStrCmp(TEXT(""), TEXT(""), MAX_BUFFER_SIZE));
	EXPECT_EQ(0, SafeStrCmp(TEXT("abcdef"), TEXT("abcdef"), MAX_BUFFER_SIZE));
	EXPECT_EQ(-1, SafeStrCmp(TEXT("abcdef"), TEXT("abcdex"), MAX_BUFFER_SIZE));
	EXPECT_EQ(1, SafeStrCmp(TEXT("abcx"), TEXT("abcd"), MAX_BUFFER_SIZE));
}