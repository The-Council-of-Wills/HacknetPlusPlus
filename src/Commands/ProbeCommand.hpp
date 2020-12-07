#pragma once
#include "Command.hpp"

class ProbeCommand : public Command {
    public:
        void run(std::vector<std::string> args) {
            if (!hasExactArguments(1, args)) return;
            
            SecuritySuite* security = GameManager::getInstance()->getCurrent()->getSecurity();
            std::cout << security->probe();
        }
};
