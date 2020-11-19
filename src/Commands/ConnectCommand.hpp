#pragma once
#include "Command.hpp"

class ConnectCommand : public Command {
    public:
        void run(GameManager *game, std::vector<std::string> args) {
            if (hasExactArguments(2, args)) {
                game->connect(args[1]);
            }
        }
};
