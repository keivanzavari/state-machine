#ifndef FSM_INCLUDE_STATES_H_
#define FSM_INCLUDE_STATES_H_

#include <functional>
#include <string>
#include <utility>

#include "constants.h"
// #include "state_machine.h"
#include "transmitters.h"
#include "types.h"

namespace fsm {
class State;

class StatesStore {
 public:
  static void addState(State* state) { states[state->getName()] = state; }

 private:
  static std::unordered_map<std::string, State*> states;
};

std::unordered_map<std::string, State*> StatesStore::states{};
class State {
 public:
  State(std::string state_name_) : state_name(std::move(state_name_)), event_sender(0) { initialize(); }
  std::string getName() const { return state_name; }

  void setEntryFunction(const std::function<void()>& entryFunction) {}
  void setExitFunction(const std::function<void()>& exitFunction) {}
  friend class StateMachine;

 private:
  void initialize() {
    current_event = "";
    StatesStore::addState(this);
  }
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
  std::function<void()> enter;
  std::function<void()> exit;
};

}  // namespace fsm

#endif  // FSM_INCLUDE_STATES_H_
