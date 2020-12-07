#pragma once
#include "Command.hpp"

class WhereCommand : public Command {
    public:
        void run(std::vector<std::string> args) {
            if (!hasExactArguments(1, args)) return;
            std::cout << GameManager::getInstance()->getCurrent()->toString() << '\n';
        }
};
