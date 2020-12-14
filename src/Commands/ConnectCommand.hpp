#pragma once
#include "Command.hpp"

class ConnectCommand : public Command {
    public:
        void run(const std::vector<std::string> &args) override {
            if (!hasExactArguments(2, args)) return;
            GameManager::getInstance()->connect(args[1]);
        }
};
