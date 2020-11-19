#pragma once
#include "Command.hpp"

class TreeCommand : public Command {
    public:
        void run(GameManager *game, std::vector<std::string> args) {
            if (hasExactArguments(1, args)) {
                std::cout << game->getDirectory()->showTree() << '\n';
            }
        }
};
