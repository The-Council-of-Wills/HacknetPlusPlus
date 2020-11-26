#pragma once
#include "Command.hpp"
#include <fstream>

class HelpCommand : public Command {
    public:
        void run(GameManager *game, std::vector<std::string> args) {
            if (!hasExactArguments(1, args)) return;
            std::string buf;
            std::ifstream in("assets/help");
            while (getline(in, buf)) {
                std::cout << buf << '\n';
            }
            in.close();
        }
};
