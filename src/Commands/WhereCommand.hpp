#pragma once
#include "Command.hpp"

class WhereCommand : public Command {
    public:
        void run(const std::vector<std::string> &args) override {
            if (!hasExactArguments(1, args)) return;
            Printer::print(GameManager::getInstance()->getCurrentComputer()->toString());
        }
};
