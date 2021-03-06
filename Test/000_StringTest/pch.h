#include <gtest/gtest.h>

#include "../../Src/_Common/Type.h"
#include "../../Src/_Common/Define.h"
#include "../../Src/_Common/ErrorCode.h"
#include "../../Src/000_String/000_String.h"

using namespace core;

#define ASSERT_EC_SUCCESS(val) ASSERT_EQ(EC_SUCCESS, val);
#define EXPECT_EC_SUCCESS(val) EXPECT_EQ(EC_SUCCESS, val);