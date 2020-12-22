#pragma once
#include "Command.hpp"

class AddNoteCommand : public Command {
    public:
        void run(const std::vector<std::string> &args) override {
            if (!hasExactArguments(2, args)) return;
            
            Folder* playerDir = GameManager::getInstance()->getPlayerDir();
            File* notes = playerDir->getElement("home")->getElement("notes")->openFile("notes.txt");
            notes->append(args[1]);
        }
};
