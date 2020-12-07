#pragma once
#include "Command.hpp"

class TouchCommand : public Command {
    public:
        void run(std::vector<std::string> args) {
            if (!hasExactArguments(2, args)) return;
            GameManager *game = GameManager::getInstance();
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
