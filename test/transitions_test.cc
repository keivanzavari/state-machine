#include "transitions.h"

#include <gtest/gtest.h>

#include <string>

#include "gmock/gmock.h"
#include "types.h"
namespace fsm {

template <typename T>
bool contains(const std::set<T>& set, const T& val) {
  return set.find(val) != set.end();
}

TEST(Transitions, SampleTransition) {
  std::set<std::string> states{"init", "A", "B", "C"};
  std::vector<std::string> ab_events{"e_done", "e_random"};
  Transition t0("init", "A", {"e_init"});
  Transition tab("A", "B", ab_events);
  Transition tbc("B", "C", {"e_done"});
  Transition tac("A", "C", {"e_quick"});
  Transition tca("C", "A", {"e_restart"});

  TransitionTable& table = t0.getTable();
  for (const auto& state : states) {
    ASSERT_TRUE(table.contains(state));
  }
  for (const auto& event : ab_events) {
    ASSERT_TRUE(contains(table.at("A").at("B"), event));
  }

  EXPECT_THAT(table.at("B").at("C"), ::testing::ElementsAre("e_done"));
  EXPECT_THAT(table.at("A").at("C"), ::testing::ElementsAre("e_quick"));
  EXPECT_THAT(table.at("C").at("A"), ::testing::ElementsAre("e_restart"));
}

}  // namespace fsm

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
