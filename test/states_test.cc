#include "states.h"

#include <gtest/gtest.h>

#include <string>

#include "gmock/gmock.h"
#include "types.h"
namespace fsm {

TEST(States, SimpleTest) {
  State a("A");
  State b("B");
}

}  // namespace fsm

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
