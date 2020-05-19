#include "pch.h"
#include <limits>
#include "../../Src/000_String/NumericString.h"

/////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
class _NumericStringTest : public ::testing::Test
{
protected:
    T value;
};

using StringSupportTypes = ::testing::Types<BYTE, WORD, DWORD, QWORD, uint32_t,
                                            char, short, int32_t, int64_t>;

TYPED_TEST_SUITE(_NumericStringTest, StringSupportTypes);

TYPED_TEST(_NumericStringTest, StringSupportTypesTest)
{
    EXPECT_EQ(TEXT("0"), StringFrom(0));
    EXPECT_EQ(TEXT("1"), StringFrom(1));
    EXPECT_EQ(TEXT("12"), StringFrom(12));
    EXPECT_EQ(TEXT("123"), StringFrom(123));

    if ( std::numeric_limits<decltype(this->value)>::is_signed )
    {
        EXPECT_EQ(TEXT("-1"), StringFrom(-1));
        EXPECT_EQ(TEXT("-12"), StringFrom(-12));
        EXPECT_EQ(TEXT("-123"), StringFrom(-123));
    }
}

TEST(NumericStringTest, StringFromBoolTest)
{
    EXPECT_EQ(TEXT("true"), StringFrom(true));
    EXPECT_EQ(TEXT("false"), StringFrom(false));
}

TEST(NumericStringTest, StringFromFloatNumberTest)
{
    EXPECT_EQ(TEXT("0.000000"), StringFrom(0.0f));
    EXPECT_EQ(TEXT("1.010000"), StringFrom(1.01f));
    EXPECT_EQ(TEXT("-1.010000"), StringFrom(-1.01f));
}

TEST(NumericStringTest, StringFromDoubleNumberTest)
{
    EXPECT_EQ(TEXT("0.000000"), StringFrom(0.0));
    EXPECT_EQ(TEXT("1.010000"), StringFrom(1.01));
    EXPECT_EQ(TEXT("-1.010000"), StringFrom(-1.01));
}

TEST(NumericStringTest, StringFromExponentialExpressionTest)
{
    EXPECT_EQ(TEXT("1.000000"), StringFrom(0.1e+1));
    EXPECT_EQ(TEXT("0.000010"), StringFrom(10E-006));
    EXPECT_EQ(TEXT("-1.234000"), StringFrom(-1234E-003));
    EXPECT_EQ(TEXT("0.000000"), StringFrom(1e-10));
    EXPECT_EQ(TEXT("1234.000000"), StringFrom(1.234e3));
}

TEST(NumericStringTest, StringFromStringTest)
{
    std::tstring strValue = TEXT("value");
    EXPECT_EQ(TEXT("value"), StringFrom(strValue));
}

/////////////////////////////////////////////////////////////////////////////////////////
using HexFromSupportType = ::testing::Types<BYTE, WORD, DWORD, QWORD, uint32_t,
                                            char, short, int32_t, int64_t>;

TEST(_NumericStringTest, HexFromSupportTypeTest)
{
    EXPECT_EQ(TEXT("0x00000000"), HexFrom(0));
    EXPECT_EQ(TEXT("0xAAAAAAAA"), HexFrom(0xAAAAAAAA));
}

TEST(NumericStringTest, HexFromBoolTest)
{
    EXPECT_EQ(TEXT("true"), HexFrom(true));
    EXPECT_EQ(TEXT("false"), HexFrom(false));
}

TEST(NumericStringTest, HexFromFloatNumberTest)
{
    EXPECT_EQ(TEXT("0.000000"), HexFrom(0.0f));
    EXPECT_EQ(TEXT("1.010000"), HexFrom(1.01f));
    EXPECT_EQ(TEXT("-1.010000"), HexFrom(-1.01f));
}

TEST(NumericStringTest, HexFromDoubleNumberTest)
{
    EXPECT_EQ(TEXT("0.000000"), HexFrom(0.0));
    EXPECT_EQ(TEXT("1.010000"), HexFrom(1.01));
    EXPECT_EQ(TEXT("-1.010000"), HexFrom(-1.01));
}

TEST(NumericStringTest, HexFromStringTest)
{
    std::tstring strValue = TEXT("value");
    EXPECT_EQ(TEXT("value"), HexFrom(strValue));
}