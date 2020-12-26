#pragma once
#include "Command.hpp"
#include <fstream>

class HelpCommand : public Command {
    public:
        void run(const std::vector<std::string> &args) override {
            if (!hasExactArguments(1, args)) return;
            
            std::ifstream in(GameManager::getResource("assets/help"));
            if (!in.is_open()) {
                std::cerr << "Error opening help file.\n";
                return;
            }

            for (std::string buf; getline(in, buf);) {
                Printer::print(buf);
            }
        }
};
