// #pragma once

#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

#include "types.h"

namespace fsm {

// Right now the event store doesn't implement any form of priority to the queued messages.
// This could be a future improvement.
class EventStore {
 public:
  void send(const EventType& event) {
    // What is used for transportation can be different from what type is used for internal messages.
    // For example if the events are serialized.
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

  static std::vector<MsgType> toVector() {
    auto p = msg_queue;
    std::vector<MsgType> vec(p.size());
    std::size_t size = p.size();
    for (unsigned int i = 0; i < size; ++i) {
      vec.at(i) = p.front();
      p.pop();
    }
    return vec;
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
