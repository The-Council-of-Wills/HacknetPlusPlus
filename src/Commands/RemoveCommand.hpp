#pragma once
#include "Command.hpp"

class RemoveCommand : public Command {
    public:
        void run(std::vector<std::string> args) {
            if (!hasExactArguments(2, args)) return;
            
            Folder* directory = GameManager::getInstance()->getDirectory();
            FileSystemElement* elem = evaluatePath(directory, args[1]);
            
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
