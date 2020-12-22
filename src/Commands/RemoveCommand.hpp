#pragma once
#include "Command.hpp"

class RemoveCommand : public Command {
    public:
        void run(const std::vector<std::string> &args) override {
            if (!hasExactArguments(2, args)) return;
            
            Folder* dir = GameManager::getInstance()->getDirectory();
            FileSystemElement* elem = dir->evaluatePath(args[1]);
            
            if (elem == nullptr) {
                std::cout << "Error: file does not exist.\n";
            }
            else if (elem->getType() != FileSystemType::Folder) {
                Folder* folder = (Folder *)elem->getParent();
                folder->deleteElement(elem->getName());
            }
            else {
                std::cout << "Error: is not a file.\n";
            }
        }
};
