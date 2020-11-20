#pragma once
#include "Command.hpp"

class ListDirectoryCommand : public Command {
    public:
        void run(GameManager *game, std::vector<std::string> args) {
            if (!hasExactArguments(1, args)) return;
            std::cout << game->getDirectory()->listChildren();
        }
};
