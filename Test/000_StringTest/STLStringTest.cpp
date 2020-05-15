#include "pch.h"
#include "../../Src/000_String/STLString.h"

TEST(STLStringTest, FormatTest)
{
	EXPECT_EQ(TEXT("100") ,Format(TEXT("%d")   ,100));
	EXPECT_EQ(TEXT("0.1") ,Format(TEXT("%.1f") ,0.1f));
	EXPECT_EQ(TEXT("a")   ,Format(TEXT("%c")   ,TEXT('a')));
	EXPECT_EQ(TEXT("abc") ,Format(TEXT("%s")   ,TEXT("abc")));
	EXPECT_EQ(TEXT("A")   ,Format(TEXT("%X")   ,0xA));
	EXPECT_EQ(TEXT("a")   ,Format(TEXT("%x")   ,0xA));
	EXPECT_EQ(TEXT("%")   ,Format(TEXT("%%")));
}

TEST(STLStringTest, TrimTest)
{
	EXPECT_EQ(TEXT("a"), Trim(TEXT("   a")));
	EXPECT_EQ(TEXT("a"), Trim(TEXT("a\n")));
	EXPECT_EQ(TEXT("a"), Trim(TEXT("   a\t")));
	EXPECT_EQ(TEXT("a"), Trim(TEXT("\r a \n ")));
}

TEST(STLStringTest, MakeLowerTest)
{ 
	EXPECT_EQ(TEXT("ab->cd"), MakeLower(TEXT("aB->Cd")));
}

TEST(STLStringTest, MakeUpperTest)
{ 
	EXPECT_EQ(TEXT("AB->CD"), MakeUpper(TEXT("Ab->cD")));
}

TEST(STLStringTest, BecomeLowerTest)
{
	std::tstring strTarget = TEXT("aB->Cd");
	EXPECT_EQ(TEXT("ab->cd"), BecomeLower(strTarget));
	EXPECT_EQ(TEXT("ab->cd"), strTarget);
}

TEST(STLStringTest, BecomeUpperTest)
{
	std::tstring strTarget = TEXT("Ab->cD");
	EXPECT_EQ(TEXT("AB->CD"), BecomeUpper(strTarget));
	EXPECT_EQ(TEXT("AB->CD"), strTarget);
}

TEST(STLStringTest, ReplaceTest)
{
    ASSERT_TRUE(false);
}

TEST(STLStringTest, TokenizeTest)
{
    ASSERT_TRUE(false);
}

TEST(STLStringTest, TokenizeToArrayTest)
{
    ASSERT_TRUE(false);
}

TEST(STLStringTest, SwapTest)
{
    ASSERT_TRUE(false);
}

TEST(STLStringTest, SplitTest)
{
    ASSERT_TRUE(false);
}

TEST(STLStringTest, RightTest)
{
    ASSERT_TRUE(false);
}

TEST(STLStringTest, StrCmpWithWildcardTest)
{
    ASSERT_TRUE(false);
}