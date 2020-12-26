#pragma once
#include "Command.hpp"

class MakeDirCommand : public Command {
    public:
        void run(const std::vector<std::string> &args) override {
            if (!hasExactArguments(2, args)) return;

            GameManager *game = GameManager::getInstance();
            FileSystemElement* elem = game->getDirectory()->evaluatePath(args[1]);
            
            if (elem == nullptr) {
                game->getDirectory()->insertElement(new Folder(args[1]));
            }
            else {
                Printer::print("Can't create directory. Archive already exists.");
            }
        }
};
