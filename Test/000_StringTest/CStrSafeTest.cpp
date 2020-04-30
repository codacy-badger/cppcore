#include "pch.h"
#include "../../Src/000_String/CStrSafe.h"

/////////////////////////////////////////////////////////////////////////////////////////
using namespace core;

constexpr size_t MAX_BUFFER_SIZE = 50;

/////////////////////////////////////////////////////////////////////////////////////////
TEST(CStrSafeTest, StringCchCopy_test)
{
	LPTSTR pszDest = new TCHAR[MAX_BUFFER_SIZE];
	LPCTSTR pszSrc = TEXT("abcdefg");

	ASSERT_EC_SUCCESS(StringCchCopy(pszDest, MAX_BUFFER_SIZE, pszSrc));

	EXPECT_STREQ(pszDest, pszSrc);
}

TEST(CStrSafeTest, StringCchCopyN_test)
{
	LPTSTR pszDest = new TCHAR[MAX_BUFFER_SIZE];
	LPCTSTR pszSrc = TEXT("abcdefg");
	LPCTSTR pszExpected = TEXT("abcde");

	ASSERT_EC_SUCCESS(StringCchCopyN(pszDest, MAX_BUFFER_SIZE, pszSrc, 5));

	EXPECT_STREQ(pszDest, pszExpected);
}

TEST(CStrSafeTest, StringCchCat_test)
{
	LPTSTR pszDest = new TCHAR[MAX_BUFFER_SIZE];
	ASSERT_EC_SUCCESS(StringCchCopy(pszDest, MAX_BUFFER_SIZE, TEXT("abc")));
	LPCTSTR pszSrcToCat = TEXT("def");
	LPCTSTR pszExpected = TEXT("abcdef");

	ASSERT_EC_SUCCESS(StringCchCat(pszDest, MAX_BUFFER_SIZE, pszSrcToCat));

	EXPECT_STREQ(pszDest, pszExpected);
}

TEST(CStrSafeTest, StringCchCatN_test)
{
	LPTSTR pszDest = new TCHAR[MAX_BUFFER_SIZE];
	ASSERT_EC_SUCCESS(StringCchCopy(pszDest, MAX_BUFFER_SIZE, TEXT("abc")));
	LPCTSTR pszSrcToCat = TEXT("defghijk");
	LPCTSTR pszExpected = TEXT("abcdef");

	ASSERT_EC_SUCCESS(StringCchCatN(pszDest, MAX_BUFFER_SIZE, pszSrcToCat, 3));
	EXPECT_STREQ(pszDest, pszExpected);
}

static inline ECODE VaFormatTest(LPTSTR pszBuffer, LPCTSTR pszFormat, ...)
{
	va_list list;
	va_start(list, pszFormat);
	ECODE nRet = StringCchVPrintf(pszBuffer, MAX_BUFFER_SIZE, pszFormat, list);
	va_end(list);
	return nRet;
}

TEST(CStrSafeTest, StringCchPrtinf_test)
{
	LPTSTR pszDest = new TCHAR[MAX_BUFFER_SIZE];
	LPCTSTR pszExpected = TEXT("-1 1 a 0.10 a abcd");

	ASSERT_EC_SUCCESS(StringCchPrintf(pszDest, MAX_BUFFER_SIZE
		,TEXT("%d %u %x %.2f %c %s"), -1, 1, 0xa, 0.1f, TEXT('a'), TEXT("abcd")));

	EXPECT_STREQ(pszDest, pszExpected);
}

TEST(CStrSafeTest, StringCchVPrintf_test)
{
	LPTSTR pszDest = new TCHAR[MAX_BUFFER_SIZE];
	LPCTSTR pszExpected = TEXT("-1 1 a 0.10 a abcd");

	ASSERT_EC_SUCCESS(VaFormatTest(pszDest
		,TEXT("%d %u %x %.2f %c %s"), -1, 1, 0xa, 0.1f, TEXT('a'), TEXT("abcd")));

	EXPECT_STREQ(pszDest, pszExpected);
}

TEST(CStrSafeTest, StringCchGets_test)
{
	ASSERT_EC_SUCCESS(EC_NOT_IMPLEMENTED);
}

TEST(CStrSafeTest, StringCchLength_test)
{
	ASSERT_EC_SUCCESS(EC_NOT_IMPLEMENTED);
}

/////////////////////////////////////////////////////////////////////////////////////////
TEST(CStrSafeTest, StringCbCopy_test)
{
	ASSERT_EC_SUCCESS(EC_NOT_IMPLEMENTED);
}

TEST(CStrSafeTest, StringCbCopyN_test)
{
	ASSERT_EC_SUCCESS(EC_NOT_IMPLEMENTED);
}

TEST(CStrSafeTest, StringCbCat_test)
{
	ASSERT_EC_SUCCESS(EC_NOT_IMPLEMENTED);
}

TEST(CStrSafeTest, StringCbCatN_test)
{
	ASSERT_EC_SUCCESS(EC_NOT_IMPLEMENTED);
}

TEST(CStrSafeTest, StringCbPrintf_test)
{
	ASSERT_EC_SUCCESS(EC_NOT_IMPLEMENTED);
}

TEST(CStrSafeTest, StringCbVPrintf_test)
{
	ASSERT_EC_SUCCESS(EC_NOT_IMPLEMENTED);
}

TEST(CStrSafeTest, StringCbGets_test)
{
	ASSERT_EC_SUCCESS(EC_NOT_IMPLEMENTED);
}

TEST(CStrSafeTest, StringCbLength_test)
{
	ASSERT_EC_SUCCESS(EC_NOT_IMPLEMENTED);
}

/////////////////////////////////////////////////////////////////////////////////////////
TEST(CStrSafeTest, StringCchCopyEx_test)
{
	ASSERT_EC_SUCCESS(EC_NOT_IMPLEMENTED);
}

TEST(CStrSafeTest, StringCchCopyNEx_test)
{
	ASSERT_EC_SUCCESS(EC_NOT_IMPLEMENTED);
}

TEST(CStrSafeTest, StringCchCatEx_test)
{
	ASSERT_EC_SUCCESS(EC_NOT_IMPLEMENTED);
}

TEST(CStrSafeTest, StringCchCatNEx_test)
{
	ASSERT_EC_SUCCESS(EC_NOT_IMPLEMENTED);
}

TEST(CStrSafeTest, StringCchPrintfEx_test)
{
	ASSERT_EC_SUCCESS(EC_NOT_IMPLEMENTED);
}

TEST(CStrSafeTest, StringCchVPrintfEx_test)
{
	ASSERT_EC_SUCCESS(EC_NOT_IMPLEMENTED);
}

TEST(CStrSafeTest, StringCchGetsEx_test)
{
	ASSERT_EC_SUCCESS(EC_NOT_IMPLEMENTED);
}

/////////////////////////////////////////////////////////////////////////////////////////
TEST(CStrSafeTest, StringCbCopyEx_test)
{
	ASSERT_EC_SUCCESS(EC_NOT_IMPLEMENTED);
}

TEST(CStrSafeTest, StringCbCopyNEx_test)
{
	ASSERT_EC_SUCCESS(EC_NOT_IMPLEMENTED);
}

TEST(CStrSafeTest, StringCbCatEx_test)
{
	ASSERT_EC_SUCCESS(EC_NOT_IMPLEMENTED);
}

TEST(CStrSafeTest, StringCbCatNEx_test)
{
	ASSERT_EC_SUCCESS(EC_NOT_IMPLEMENTED);
}

TEST(CStrSafeTest, StringCbPrintfEx_test)
{
	ASSERT_EC_SUCCESS(EC_NOT_IMPLEMENTED);
}

TEST(CStrSafeTest, StringCbVPrintfEx_test)
{
	ASSERT_EC_SUCCESS(EC_NOT_IMPLEMENTED);
}

TEST(CStrSafeTest, StringCbGetsEx_test)
{
	ASSERT_EC_SUCCESS(EC_NOT_IMPLEMENTED);
}
