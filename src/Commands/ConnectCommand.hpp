#pragma once
#include "Command.hpp"

class ConnectCommand : public Command {
    public:
        void run(std::vector<std::string> args) {
            if (!hasExactArguments(2, args)) return;
            GameManager::getInstance()->connect(args[1]);
        }
};
