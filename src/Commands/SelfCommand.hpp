#pragma once
#include "Command.hpp"

class SelfCommand : public Command {
    public:
        void run(GameManager *game, std::vector<std::string> args) {
            if (hasExactArguments(1, args)) {
                std::cout << game->getPlayer()->toString() << '\n';
            }
        }
};
