#include <gtest/gtest.h>

#include "../../Src/_Common/Type.h"
#include "../../Src/_Common/Define.h"
#include "../../Src/_Common/Errorcode.h"

#define ASSERT_EC_SUCCESS(val) ASSERT_EQ(EC_SUCCESS, val);
#define EXPECT_EC_SUCCESS(val) EXPECT_EQ(EC_SUCCESS, val);