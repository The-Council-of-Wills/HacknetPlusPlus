#pragma once
#include "Command.hpp"

class TouchCommand : public Command {
    public:
        void run(const std::vector<std::string> &args) override {
            if (!hasExactArguments(2, args)) return;

            Folder* dir = GameManager::getInstance()->getDirectory();
            FileSystemElement* file = dir->getElement(args[1]);
            
            if (file == nullptr) {
                file = new File(args[1]);
                dir->insertElement(file);
            }
            else {
                std::cout << "The file already exists\n";
            }
        }
};
