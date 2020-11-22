#pragma once
#include "Command.hpp"

class ProbeCommand : public Command {
    public:
        void run(GameManager *game, std::vector<std::string> args) {
            if (!hasExactArguments(1, args)) return;
            SecuritySuite* security = game->getCurrent()->getSecurity();
            std::cout << security->probe();
        }
};
