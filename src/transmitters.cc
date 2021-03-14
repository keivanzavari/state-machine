// #pragma once

#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

#include "types.h"

namespace fsm {

class EventStore {
 public:
  void send(const EventType& event) {
    // What is used for transportation can be different from what type is used for internal messages.
    // Here they are the same. Hence no conversion is required.
    std::scoped_lock lock(mutex);
    msg_queue.push(event);
  }

  EventType next() const { return msg_queue.front(); }

  EventType receive() {
    auto front = next();
    std::scoped_lock lock(mutex);
    msg_queue.pop();

    return front;
  }

  static void print() {
    auto p = msg_queue;
    std::cout << "queue of length " << p.size() << ": [";
    std::size_t size = p.size();
    for (unsigned int i = 0; i < size; ++i) {
      std::cout << p.front() << " ";
      p.pop();
    }
    std::cout << "]\n";
  }

 private:
  static std::queue<MsgType> msg_queue;
  std::mutex mutex;
};
std::queue<MsgType> EventStore::msg_queue{};

class EventSender {
 public:
  EventSender(int id_) : id(id_) {}
  EventSender(const EventSender& other) { id = other.id; }

  void send(const EventType& event) {
    // What is used for transportation can be different from what type is used for internal messages.
    // Here they are the same. Hence no conversion is required.
    store.send(event);
  }

 private:
  EventStore store;
  int id;
};

class EventReceiver {
 public:
  EventReceiver() = default;

  MsgType receive() {
    // What is used for transportation can be different from what type is used for internal messages.
    // Here they are the same. Hence no conversion is required.
    return store.receive();
  }

  MsgType next() {
    // What is used for transportation can be different from what type is used for internal messages.
    // Here they are the same. Hence no conversion is required.
    return store.next();
  }

 private:
  EventStore store;
};
}  // namespace fsm

void send_event(fsm::EventSender& sender, const fsm::EventType& msg) { sender.send(msg); }

int main() {
  std::vector<std::thread> threads;
  std::vector<fsm::EventSender> senders;
  for (int i = 0; i < 5; ++i) {
    auto sender = senders.emplace_back(i);
    threads.emplace_back(send_event, std::ref(sender), std::to_string(i));
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  fsm::EventStore::print();
  for (auto& thread : threads) {
    thread.join();
  }
  return 0;
}
