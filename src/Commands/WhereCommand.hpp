#pragma once
#include "Command.hpp"

class WhereCommand : public Command {
    public:
        void run(std::vector<std::string> args) {
            if (!hasExactArguments(1, args)) return;
            GameManager *game = GameManager::getInstance();
            std::cout << game->getCurrent()->toString() << '\n';
        }
};
