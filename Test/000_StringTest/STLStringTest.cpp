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
	std::tstring strContext = TEXT("  \ra\t\n  ");
	EXPECT_EQ(TEXT("a"), Trim(strContext));
	EXPECT_EQ(TEXT("a"), Trim(strContext.c_str()));
}

TEST(STLStringTest, TrimLeftTest)
{
	std::tstring strContext = TEXT("  \ra\t\n  ");
	EXPECT_EQ(TEXT("a\t\n  "), TrimLeft(strContext));
	EXPECT_EQ(TEXT("a\t\n  "), TrimLeft(strContext.c_str()));
}

TEST(STLStringTest, TrimRightTest)
{
	std::tstring strContext = TEXT("  \ra\t\n  ");
	EXPECT_EQ(TEXT("  \ra"), TrimRight(strContext));
	EXPECT_EQ(TEXT("  \ra"), TrimRight(strContext.c_str()));
}

TEST(STLStringTest, MakeLowerTest)
{ 
	const std::tstring strContext = TEXT("aB->Cd");

	EXPECT_EQ(TEXT("ab->cd"), MakeLower(strContext));
	EXPECT_EQ(TEXT("ab->cd"), MakeLower(strContext.c_str()));
}

TEST(STLStringTest, MakeUpperTest)
{ 
	const std::tstring strContext = TEXT("Ab->cD");

	EXPECT_EQ(TEXT("AB->CD"), MakeUpper(strContext));
	EXPECT_EQ(TEXT("AB->CD"), MakeUpper(strContext.c_str()));
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
	std::tstring strContext = TEXT("a123ab123abc");
	const std::tstring strTarget = TEXT("ab");
	const std::tstring strReplace = TEXT("cc");
	
	EXPECT_EQ(TEXT("a123cc123ccc"), Replace(strContext, strTarget, strReplace));
	EXPECT_EQ(TEXT("a123cc123ccc"), Replace(strContext.c_str(), strTarget, strReplace));
}

TEST(STLStringTest, TokenizeTest)
{
	int nOffset = 0;
	const std::tstring strContext = TEXT("a B c D");

	EXPECT_EQ(TEXT("a"), Tokenize(strContext, nOffset));
	EXPECT_EQ(nOffset, 1);
	EXPECT_EQ(TEXT("B"), Tokenize(strContext, nOffset));
	EXPECT_EQ(TEXT("c"), Tokenize(strContext, nOffset));
	EXPECT_EQ(TEXT("D"), Tokenize(strContext, nOffset));
}

TEST(STLStringTest, Tokenize_invalied_delimiter_Test)
{
	int nOffset = 0;
	const std::tstring strContext = TEXT("a-B-c-D");

	EXPECT_EQ(strContext, Tokenize(strContext, TEXT("*"), nOffset));
	EXPECT_EQ(nOffset, -1);
}

TEST(STLStringTest, Tokenize_special_delimiter_Test)
{
	int nOffset = 0;
	const std::tstring strContext = TEXT("a-B*c!D");

	EXPECT_EQ(TEXT("a"), Tokenize(strContext, TEXT("-*!"), nOffset));
	EXPECT_EQ(nOffset, 2);
	EXPECT_EQ(TEXT("B"), Tokenize(strContext, TEXT("-*!"), nOffset));
	EXPECT_EQ(TEXT("c"), Tokenize(strContext, TEXT("-*!"), nOffset));
	EXPECT_EQ(TEXT("D"), Tokenize(strContext, TEXT("-*!"), nOffset));
}

TEST(STLStringTest, TokenizeToArrayTest)
{
	std::vector<std::tstring> vecToken;
	const std::tstring strContext = TEXT("a B c D");
	
	EXPECT_EQ(4, TokenizeToArray(strContext, TEXT(" "), vecToken));
	
	ASSERT_EQ(4, vecToken.size());
	EXPECT_EQ(TEXT("a"), vecToken[0]);	
	EXPECT_EQ(TEXT("B"), vecToken[1]);
	EXPECT_EQ(TEXT("c"), vecToken[2]);
	EXPECT_EQ(TEXT("D"), vecToken[3]);	
}

TEST(STLStringTest, SwapTest)
{
	std::tstring strLeft = TEXT("left");
	std::tstring strRight = TEXT("right");

	Swap(strLeft, strRight);

	EXPECT_EQ(strLeft, TEXT("right"));
	EXPECT_EQ(strRight, TEXT("left"));
}

TEST(STLStringTest, SplitTest)
{
	std::tstring strLeft;
	std::tstring strRight;
	const std::tstring strContext = TEXT("left-right");
	
	strLeft = Split(strContext, TEXT("-"), &strRight); 

	EXPECT_EQ(strLeft  ,TEXT("left"));
	EXPECT_EQ(strRight ,TEXT("right"));
}

TEST(STLStringTest, RightTest)
{
	const std::tstring stcContext = TEXT("01234right");
	
	EXPECT_EQ(TEXT("right"), Right(stcContext, 5));
}

TEST(STLStringTest, StrCmpWithWildcardTest)
{
	const std::tstring strContext = TEXT("/abc");
	
	EXPECT_TRUE(StrCmpWithWildcard(strContext, TEXT("????")));
	EXPECT_TRUE(StrCmpWithWildcard(strContext, TEXT("*")));
	EXPECT_FALSE(StrCmpWithWildcard(strContext, TEXT("/??*??")));
}