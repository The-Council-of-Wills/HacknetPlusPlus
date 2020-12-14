#pragma once
#include "Command.hpp"

class NotesCommand : public Command {
    public:
        void run(const std::vector<std::string> &args) override {
            if (!hasExactArguments(1, args)) return;

            Folder* playerDir = GameManager::getInstance()->getPlayerDir();
            playerDir = playerDir->getOrCreateFolder("home");
            playerDir = playerDir->getOrCreateFolder("notes");
            
            File* notes = playerDir->getOrCreateFile("notes.txt");
            std::cout << notes->getContents() << '\n';
       }
};
