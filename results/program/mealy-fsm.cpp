#include "mealy-fsm.hpp"

State State::operator--(int) {
    return *this; 
}

ConnectedStates operator>(State lhs, State rhs) {
    return { lhs, rhs };
}

InputOutput operator/(Input lhs, Output rhs) {
    return { lhs, rhs };
}

void MealyFsm::Register(std::vector<std::pair<ConnectedStates, InputOutput>> pairs) {
    for (auto& pair : pairs) {
        Register(pair.first, pair.second);
    }
}

void MealyFsm::Register(ConnectedStates ss, InputOutput io) {
    Transition t { ss.start, ss.end, io.i, io.o };
    transitions_.push_back(t);
}

std::pair<std::string, bool> MealyFsm::Eval(const std::string& input) const {
    if (transitions_.size() == 0) {
        return { "", false };
    }
    auto cur = transitions_[0].start;
    std::string out_str;
    for (auto symbol : input) {
        auto t = FindTransitionFor(cur, symbol);
        if (!t) {
            return { out_str, false };
        }
        out_str += t->out.symbol;
        cur = t->end;
    }
    return { out_str, true };
}

std::optional<Transition> MealyFsm::FindTransitionFor(const State& s, char sym) const {
    for (auto& t : transitions_) {
        if (t.start.name == s.name && t.in.symbol == sym) {
            return t;
        }
    }
    return {};
}

State operator ""_s(const char* s, size_t n) {
    return State { s };
}

Input operator ""_i(char c) {
    return Input { c };
}

Output operator ""_o(char c) {
    return Output { c };
}
