#ifndef MEALY_FSM_HPP
#define MEALY_FSM_HPP

#include <utility>
#include <string>
#include <vector>
#include <optional>

struct ConnectedStates;

struct State {
    State operator--(int);

    friend ConnectedStates operator>(State lhs, State rhs);

    std::string name;
};

struct ConnectedStates {
    State start;
    State end;
};

struct InputOutput;

struct Output {
    char symbol;
};

struct Input {
    char symbol;
    friend InputOutput operator/(Input lhs, Output rhs);
};

struct InputOutput {
    Input i;
    Output o;
};

struct Transition {
    State start;
    State end;
    Input in;
    Output out;
};

class MealyFsm {
public:
    void Register(std::vector<std::pair<ConnectedStates, InputOutput>> pairs);

    void Register(ConnectedStates ss, InputOutput io);

    std::pair<std::string, bool> Eval(const std::string& input) const;

private:
    std::optional<Transition> FindTransitionFor(const State& s, char sym) const;

    std::vector<Transition> transitions_;
};

State operator ""_s(const char* s, unsigned long n);

Input operator ""_i(char c);

Output operator ""_o(char c);

#endif // !MEALY_FSM_HPP

