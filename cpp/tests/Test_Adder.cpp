#include <gtest/gtest.h>
#include "../Adder.h"

TEST(Add, AddTwo) {
    Adder add;
    ASSERT_EQ(add.add(1, 2), 3);
}
