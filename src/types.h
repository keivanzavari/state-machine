#pragma once

#include <set>
#include <string>
#include <unordered_map>
#include <vector>

namespace fsm {
using EventType = std::string;
using MsgType = std::string;

using EventsType = std::set<EventType>;

using TransitionTable = std::unordered_map<std::string, std::unordered_map<std::string, EventsType>>;

}  // namespace fsm
