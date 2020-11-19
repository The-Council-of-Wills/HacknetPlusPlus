#pragma once
#include "Command.hpp"

class AddComputerCommand : public Command {
    public:
        void run(GameManager *game, std::vector<std::string> args) {
            if (hasExactArguments(3, args)) {
                game->addComputer(args[1], args[2]);
            }
        }
};
