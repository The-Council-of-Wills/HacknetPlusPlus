#pragma once
#include "Command.hpp"
#include <string>

class AddComputerCommand : public Command {
    public:
        void run(std::vector<std::string> args) {
            if (!hasExactArguments(5, args)) return;
            GameManager::getInstance()->addComputer(
                new Computer(args[1], args[2], args[3], std::stoi(args[4]))
            );
        }
};
