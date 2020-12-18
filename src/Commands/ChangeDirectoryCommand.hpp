#pragma once
#include "Command.hpp"
#include "../FileSystem/FileSystemImport.hpp"

class ChangeDirectoryCommand : public Command {
    public:
        void run(const std::vector<std::string> &args) override {
            if (!hasExactArguments(2, args)) return;

            std::string newDirectory = args[1];
            Folder* dir = GameManager::getInstance()->getDirectory();
            Folder* elem = (Folder*) Folder::evaluatePath(dir, newDirectory);

            if (elem != nullptr && elem->getType() == FileSystemType::Folder) {
                GameManager::getInstance()->setDirectory(elem);
            }
            else {
                std::cout << newDirectory << " is not a folder\n";
            }
        }
};
