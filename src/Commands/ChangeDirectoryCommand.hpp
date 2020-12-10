#pragma once
#include "Command.hpp"
#include "../FileSystem/FileSystemImport.hpp"

class ChangeDirectoryCommand : public Command {
    public:
        void run(std::vector<std::string> args) {
            if (!hasExactArguments(2, args)) return;

            std::string newDirectory = args[1];
            FileSystemElement *dir = GameManager::getInstance()->getDirectory();
            FileSystemElement *elem = evaluatePath(dir, newDirectory);

            if (elem != nullptr && elem->getType() == FileSystemType::Folder) {
                GameManager::getInstance()->setDirectory(elem);
            }
            else {
                std::cout << newDirectory << " is not a folder\n";
            }
        }
};
