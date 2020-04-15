#include "pch.h"
#include "../../Src/000_String/CStrLegacy.h"

using namespace core;

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
	constexpr size_t MAX_BUFFER_SIZE = 20;
	LPTSTR tcsDestBuffer = new TCHAR[MAX_BUFFER_SIZE];
	LPCTSTR tcsSrcStr = TEXT("string to copy");

	EXPECT_STRNE(tcsDestBuffer, tcsSrcStr);
	EXPECT_EQ(tcsDestBuffer, SafeStrCpy(tcsDestBuffer, MAX_BUFFER_SIZE, tcsSrcStr));
	EXPECT_STREQ(tcsDestBuffer, tcsSrcStr);
}

TEST(CStrLegacyTest, SafeStrCat_strcat_within_max_cch)
{
	constexpr size_t MAX_BUFFER_SIZE = 30;
	LPTSTR tcsDestBuffer = new TCHAR[MAX_BUFFER_SIZE];
	
	SafeStrCpy(tcsDestBuffer, MAX_BUFFER_SIZE, TEXT("string"));
	SafeStrCat(tcsDestBuffer, MAX_BUFFER_SIZE, TEXT("cat"));
	EXPECT_STREQ(tcsDestBuffer, TEXT("stringcat"));
}

TEST(CStrLegacyTest, SafeStrStr_strstr_within_max_cch)
{
	constexpr size_t MAX_BUFFER_SIZE = 30;
	LPCTSTR tcsDestStr = TEXT("123cat789cat");
	LPCTSTR tcsKeyStr = TEXT("cat");
	LPCTSTR tcsStrExpected = TEXT("cat789cat");

	LPCTSTR tcsStrFound = SafeStrStr(tcsDestStr, MAX_BUFFER_SIZE, tcsKeyStr);
	EXPECT_STREQ(tcsStrFound, tcsStrExpected);
}

TEST(CStrLegacyTest, SafeSPrintf_sprintf_within_max_cch)
{
	constexpr size_t MAX_BUFFER_SIZE = 30;
	LPTSTR tcsDestBuffer = new TCHAR[MAX_BUFFER_SIZE];
	
	SafeSPrintf(tcsDestBuffer, MAX_BUFFER_SIZE, TEXT("%s %d"), TEXT("string"), 10);
	EXPECT_STREQ(tcsDestBuffer, TEXT("string 10"));
}

TEST(CStrLegacyTest, SafeFindStr_findstr_within_max_cch)
{
	constexpr size_t MAX_BUFFER_SIZE = 30;
	LPCTSTR tcsDestStr = TEXT("123 cat apple");

	EXPECT_EQ(0, SafeFindStr(tcsDestStr, MAX_BUFFER_SIZE, TEXT("123")));
	EXPECT_EQ(4, SafeFindStr(tcsDestStr, MAX_BUFFER_SIZE, TEXT("cat")));
	EXPECT_EQ(8, SafeFindStr(tcsDestStr, MAX_BUFFER_SIZE, TEXT("apple")));
}

TEST(CStrLegacyTest, SafeStrCmp_strcmp_within_max_cch)
{
	constexpr size_t MAX_BUFFER_SIZE = 30;

	EXPECT_EQ(0, SafeStrCmp(TEXT(""), TEXT(""), MAX_BUFFER_SIZE));
	EXPECT_EQ(0, SafeStrCmp(TEXT("abcdef"), TEXT("abcdef"), MAX_BUFFER_SIZE));
	EXPECT_EQ(-1, SafeStrCmp(TEXT("abcdef"), TEXT("abcdex"), MAX_BUFFER_SIZE));
	EXPECT_EQ(1, SafeStrCmp(TEXT("abcx"), TEXT("abcd"), MAX_BUFFER_SIZE));
}