#pragma once
#include "Command.hpp"

class ScanCommand : public Command {
    public:
        void run(GameManager *game, std::vector<std::string> args) {
            if (!hasExactArguments(1, args)) return;
            std::cout << game->getCurrent()->scan();
        }
};
