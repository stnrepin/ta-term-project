#include <iostream>
#include <string>
#include <vector>

#include "mealy-fsm.hpp"

inline bool use_samples(int argc, const char** argv) {
    return argc == 2 && argv[1][0] == 's' && argv[1][1] == '\0';
}

int main(int argc, const char** argv) {
    MealyFsm fsm;

    // _s, _i, _o -- user-defined literals
    // --> все лишь перегрузка двух операторов: -- (постфиксный декремент) и >
    //     (знак больше);
    //     см. https://stackoverflow.com/questions/1642028/what-is-the-operator-in-c
    fsm.Register({
        { "q0"_s --> "q0"_s, '0'_i/'i'_o },
        { "q0"_s --> "q1"_s, '1'_i/'i'_o },
        { "q0"_s --> "q2"_s, '2'_i/'i'_o },
        { "q0"_s --> "q3"_s, '3'_i/'i'_o },
        { "q0"_s --> "q0"_s, '$'_i/'0'_o },

        { "q1"_s --> "q1"_s, '0'_i/'i'_o },
        { "q1"_s --> "q1"_s, '1'_i/'i'_o },
        { "q1"_s --> "q2"_s, '2'_i/'i'_o },
        { "q1"_s --> "q3"_s, '3'_i/'i'_o },
        { "q1"_s --> "q0"_s, '$'_i/'1'_o },

        { "q2"_s --> "q2"_s, '0'_i/'i'_o },
        { "q2"_s --> "q2"_s, '1'_i/'i'_o },
        { "q2"_s --> "q2"_s, '2'_i/'i'_o },
        { "q2"_s --> "q3"_s, '3'_i/'i'_o },
        { "q2"_s --> "q0"_s, '$'_i/'2'_o },

        { "q3"_s --> "q3"_s, '0'_i/'i'_o },
        { "q3"_s --> "q3"_s, '1'_i/'i'_o },
        { "q3"_s --> "q3"_s, '2'_i/'i'_o },
        { "q3"_s --> "q3"_s, '3'_i/'i'_o },
        { "q3"_s --> "q0"_s, '$'_i/'3'_o },
    });

    if (use_samples(argc, argv)) {
        std::vector<std::string> samples {
            "213$", "111$", "200$", "123$", "2301$",
        };

        for (auto& s : samples) {
            auto out = fsm.Eval(s);
            std::cout << s << " :: " << out.first << '\n';
        }
    }
    else {
        std::cout << "Enter input symbols (end with '$')\n";
        char in;
        std::string fsm_in;
        int i = 1;
        do {
            std::cout << i++ << ": ";
            std::cin >> in;
            fsm_in += in;
        }
        while (in != '$');

        auto out = fsm.Eval(fsm_in);
        if (!out.second) {
            std::cout << "Input is invalid\n";
            return 0;
        }
        std::cout << "Answer: " << out.first << '\n';
    }

    return 0;
}
