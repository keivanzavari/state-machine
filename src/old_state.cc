
#include <map>
#include <string>

// class StateMachine;
// class State;

// class State {
//  public:
//   State() = delete;
//   State(const std::string &name);

//   void entry() {}
//   void exit() {}
// };

// class StateMachine {
//  public:
//   StateMachine();
//   void addState(const State &state);
//   void addTransition(const std::string &from, const std::string &to);

//   void run() {
//     // go to initial state
//     // Find the state that is registered as the destination of next state
//   }

//  private:
//   std::map<std::string, State> states;
//   // std::vector<>
// };

int main() { return 0; }

StateMachine {
  State(A) {
    entry() {}

    exit() {}
  }

  State(B) {}

  Transition(A, B, {"e_done"});
};
