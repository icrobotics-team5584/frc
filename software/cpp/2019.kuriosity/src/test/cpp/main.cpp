#include <hal/HAL.h>
#include "main/include/purePursuit/src/pathFollower.hpp"

int main(int argc, char** argv) {
  HAL_Initialize(500, 0);
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
TEST_METHOD(TestCurvature) {
  Assert::AreEqual(5, 5);
}
