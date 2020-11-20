#pragma once
#include "Command.hpp"

class MakeDirCommand : public Command {
    public:
        void run(GameManager *game, std::vector<std::string> args) {
            if (!hasExactArguments(2, args)) return;
            FileSystemElement* elem = game->getDirectory()->getElement(args[1]);
            if (elem == nullptr) {
                game->getDirectory()->insertElement(new Folder(args[1]));
            }
            else {
                std::cout << "Can't create directory. Archive already exists.\n";
            }
        }
};
