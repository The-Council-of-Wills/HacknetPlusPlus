#pragma once
#include "Command.hpp"

class SelfCommand : public Command {
    public:
        void run(const std::vector<std::string> &args) override {
            if (!hasExactArguments(1, args)) return;
            std::cout << GameManager::getInstance()->getPlayer()->toString() << '\n';
        }
};
