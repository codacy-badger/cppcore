#include "pch.h"
#include "../../Src/000_String/CStrLegacy.h"

using namespace core;

TEST(IsWhiteSpaceTest, return_true_on_whitespace_input)
{
	EXPECT_TRUE(IsWhiteSpace(TEXT(' ')));
	EXPECT_TRUE(IsWhiteSpace(TEXT('\n')));
	EXPECT_TRUE(IsWhiteSpace(TEXT('\t')));
	EXPECT_TRUE(IsWhiteSpace(TEXT('\r')));
	EXPECT_TRUE(IsWhiteSpace(TEXT('\b')));
}

TEST(IsWhiteSpaceTest, return_false_on_other_input)
{
	EXPECT_FALSE(IsWhiteSpace(TEXT('a')));
	EXPECT_FALSE(IsWhiteSpace(TEXT('Z')));
	EXPECT_FALSE(IsWhiteSpace(TEXT('%')));
	EXPECT_FALSE(IsWhiteSpace(TEXT('-')));
}

TEST(SafeStrLenTest, return_value_within_max_cch)
{
	EXPECT_EQ(3, SafeStrLen(TEXT("123"), 10));
	EXPECT_EQ(8, SafeStrLen(TEXT("123 5678"), 10));
}

TEST(SafeStrLenTest, return_value_on_edged_max_cch)
{
	EXPECT_EQ(0, SafeStrLen(TEXT(""), 1));
	EXPECT_EQ(3, SafeStrLen(TEXT("12345"), 3));
	EXPECT_EQ(5, SafeStrLen(TEXT("12345"), 5));
}