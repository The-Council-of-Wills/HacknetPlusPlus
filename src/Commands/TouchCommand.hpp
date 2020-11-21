#pragma once
#include "Command.hpp"

class TouchCommand : public Command {
    public:
        void run(GameManager *game, std::vector<std::string> args) {
            if (!hasExactArguments(2, args)) return;
            FileSystemElement* file = game->getDirectory()->getElement(args[1]);
            if (file == nullptr) {
                file = new File(args[1]);
                game->getDirectory()->insertElement(file);
            }
            else {
                std::cout << "The file already exists\n";
            }
        }
};
