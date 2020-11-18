#pragma once
#include "Command.hpp"

class AddComputerCommand : public Command {
    public:
        void run(GameManager *game, std::vector<std::string> args) {
            if (args.size() < 3) {
                std::cout << "Missing arguments.\n";
            }
            else if (args.size() == 3) {
                game->addComputer(args[1], args[2]);
            }
            else {
                std::cout << "Unexpected arguments.\n";
            }
        }
};
