#pragma once
#include "Command.hpp"

class ConnectCommand : public Command {
    public:
        void run(std::vector<std::string> args) {
            if (!hasExactArguments(2, args)) return;
            GameManager *game = GameManager::getInstance();
            game->connect(args[1]);
        }
};
