#pragma once
#include "Command.hpp"

class ScanCommand : public Command {
    public:
        void run(const std::vector<std::string> &args) override {
            if (!hasExactArguments(1, args)) return;
            Printer::print(GameManager::getInstance()->getCurrentComputer()->scan());
        }
};
