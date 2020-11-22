#pragma once
#include "Command.hpp"
#include <string>

class AddComputerCommand : public Command {
    public:
        void run(GameManager *game, std::vector<std::string> args) {
            if (!hasExactArguments(4, args)) return;
            game->addComputer(args[1], args[2], std::stoi(args[3]));
        }
};
