#pragma once
#include "Command.hpp"

class ConnectCommand : public Command {
    public:
        void run(GameManager *game, std::vector<std::string> args) {
            if (args.size() < 2) {
                std::cout << "Missing arguments.\n";
            }
            else if (args.size() == 2){
                game->connect(args[1]);
            }
            else {
                std::cout << "Unexpected arguments.\n";
            }
        }
};
