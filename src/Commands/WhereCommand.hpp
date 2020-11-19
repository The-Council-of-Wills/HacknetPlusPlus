#pragma once
#include "Command.hpp"

class WhereCommand : public Command {
    public:
        void run(GameManager *game, std::vector<std::string> args) {
            if (hasExactArguments(1, args)) {
                std::cout << game->getCurrent()->toString() << '\n';
            }
        }
};
