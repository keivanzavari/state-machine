#pragma once

#include <string>

#include "constants.h"
#include "transmitters.h"
#include "types.h"

namespace fsm {

class State {
 public:
  State(const std::string& state_name_) : state_name(state_name_), event_sender(0) { initialize(); }
  virtual void enter() = 0;
  virtual void exit() = 0;

 private:
  void initialize() { current_event = ""; }
  void onEntry() { current_event = kStateEnterEvent; }
  void onExit() { current_event = kStateExitEvent; }
  void sendEvents(const EventType& event) { event_sender.send(event); }

  void executeEntry() {
    onEntry();
    sendEvents();
    enter();
  }

  void executeExit() {
    onExit();
    sendEvents();
    exit();
  }

  void sendEvents() { event_sender.send(state_name + "_" + current_event); }

  const std::string state_name;
  EventType current_event;
  EventSender event_sender;
};

}  // namespace fsm
