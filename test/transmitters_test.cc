
#include "transmitters.h"

#include <gtest/gtest.h>

#include <thread>

#include "gmock/gmock.h"
#include "types.h"

namespace fsm {
void send_event(fsm::EventSender& sender, const fsm::EventType& msg) { sender.send(msg); }

TEST(Transmitters, AllEventsReceived) {
  std::vector<std::thread> threads;
  std::vector<fsm::EventSender> senders;
  std::vector<fsm::MsgType> values;
  for (int i = 0; i < 5; ++i) {
    auto sender = senders.emplace_back(i);
    threads.emplace_back(send_event, std::ref(sender), std::to_string(i));
    values.push_back(std::to_string(i));
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  for (auto& thread : threads) {
    thread.join();
  }
  auto vec = fsm::EventStore::toVector();
  EXPECT_THAT(vec, ::testing::UnorderedElementsAreArray(values));
}

}  // namespace fsm

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
