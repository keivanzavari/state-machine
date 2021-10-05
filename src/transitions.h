#ifndef FSM_INCLUDE_TRANSITIONS_H_
#define FSM_INCLUDE_TRANSITIONS_H_

#include <string>
#include <unordered_map>
#include <vector>

#include "types.h"

namespace fsm {

class Transition {
 public:
  Transition(const std::string& from_, const std::string& to_, const std::vector<EventType>& events_)
      : from(from_), to(to_), events(events_) {
    updateTable();
  }
  // this means that if state "from" is done, and the done event is fired, we should go to state "to",
  // therefore there should be a mapping from this event to the target state "to".
  // that state should run and that state.enter method should be executed.
  // * This mean that the state machine should own an instance of that class and execute it.
  // example:
  // from init to A with e_init
  // from A to B with e_done, with e_random
  // from A to C with e_quick
  // from B to C with e_done
  // from C to A with e_restart
  void updateTable() {
    for (auto& event : events) {
      table[from][to].emplace(event);
    }
  }

  static TransitionTable& getTable() { return Transition::table; }

 private:
  const std::string from;
  const std::string to;
  const std::vector<EventType> events;

  static TransitionTable table;
};

TransitionTable Transition::table{};

}  // namespace fsm

#endif  // FSM_INCLUDE_TRANSITIONS_H_
