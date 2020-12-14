#pragma once
#include "Command.hpp"

class TreeCommand : public Command {
    public:
        void run(const std::vector<std::string> &args) override {
            if (!hasExactArguments(1, args)) return;
            std::cout << GameManager::getInstance()->getDirectory()->showTree() << '\n';
        }
};
