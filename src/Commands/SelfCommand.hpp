#pragma once
#include "Command.hpp"

class SelfCommand : public Command {
    public:
        void run(GameManager *game, std::vector<std::string> args) {
            if (args.size() > 1) {
                std::cout << "Unexpected arguments.\n";
            }
            else {
                std::cout << game->getPlayer()->toString() << '\n';
            }
        }
};
