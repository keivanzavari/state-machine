#ifndef FSM_INCLUDE_STATE_MACHINE_H_
#define FSM_INCLUDE_STATE_MACHINE_H_

#include <string>
#include <unordered_map>

#include "states.h"
#include "transitions.h"
namespace fsm {

class StateMachine {
 public:
  StateMachine() : prepare("prepare"), init("init"), transition("prepare", "init", {"e_done"}) {
    // prepare.
  }

  void run() {
    current_state->executeEntry();
    current_state->executeExit();

    findNextState();
  }

  void findNextState() {}
  friend class State;

 private:
  State prepare;
  State init;
  State* current_state;
  Transition transition;
  EventReceiver receiver;
};

std::unordered_map<std::string, State*> StateMachine::states;

}  // namespace fsm

#endif  // FSM_INCLUDE_STATE_MACHINE_H_
