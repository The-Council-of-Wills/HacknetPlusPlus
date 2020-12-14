#pragma once
#include "Command.hpp"

class AddNoteCommand : public Command {
    public:
        void run(const std::vector<std::string> &args) override {
            if (!hasExactArguments(2, args)) return;
            
            Folder* playerDir = GameManager::getInstance()->getPlayerDir();
            playerDir = playerDir->getOrCreateFolder("home");
            playerDir = playerDir->getOrCreateFolder("notes");

            File* notes = playerDir->getOrCreateFile("notes.txt");
            notes->append(args[1]);
        }
};
