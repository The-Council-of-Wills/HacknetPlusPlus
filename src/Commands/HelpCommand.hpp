#pragma once
#include "Command.hpp"
#include <fstream>

class HelpCommand : public Command {
    public:
        void run(std::vector<std::string> args) {
            if (!hasExactArguments(1, args)) return;
            
            std::ifstream in("assets/help");
            if (!in.is_open()) {
                std::cerr << "Error opening help file.\n";
                return;
            }

            for (std::string buf; getline(in, buf);) {
                std::cout << buf << '\n';
            }
        }
};
