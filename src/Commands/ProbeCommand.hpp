#pragma once
#include "Command.hpp"

class ProbeCommand : public Command {
    public:
        void run(std::vector<std::string> args) {
            if (!hasExactArguments(1, args)) return;
            GameManager *game = GameManager::getInstance();
            SecuritySuite* security = game->getCurrent()->getSecurity();
            std::cout << security->probe();
        }
};
