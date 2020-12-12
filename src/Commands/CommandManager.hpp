#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "../GameManager.hpp"
#include "CommandInclude.hpp"

class CommandManager {
    private:
        GameManager* game;
        std::map<std::string, Command*> commands;
        std::map<std::string, Command*> executables;
    public:
        CommandManager();

        ~CommandManager() {
            for (auto c : commands) {
                delete c.second;
            }
        }

        void addCommand(std::string name, Command *c) {
            commands[name] = c;
        }

        void processCommand(std::vector<std::string> args) {
            if (commands.count(args[0])) {
                commands[args[0]]->run(args);
            }
            else if (executables.count(args[0])) {
                executables[args[0]]->run(args);
            }
            else {
                std::cout << "Unknown command." << '\n';
            }
        }

        void updateExecutables();
};

void CommandManager::updateExecutables() {
    Folder* playerRoot = GameManager::getInstance()->getPlayerDir();
    Folder* binFolder = playerRoot->getOrCreateFolder("bin");
    
    executables.clear();
    //Note: we dont erase the Command* because, if the file was deleted, the Command was deleted there,
    //and if it wasnt, we will add the pointer back again.

    for (auto elem : binFolder->getChildren()) {
        if (elem->getType() != FileSystemType::Executable) continue;
        executables[elem->getName()] = (Executable *)elem;
    }
}

CommandManager::CommandManager() {
    commands["scan"]        = new ScanCommand;
    commands["self"]        = new SelfCommand;
    commands["whoami"]      = new SelfCommand;
    commands["connect"]     = new ConnectCommand;
    commands["whereami"]    = new WhereCommand;
    commands["cd"]          = new ChangeDirectoryCommand;
    commands["tree"]        = new TreeCommand;
    commands["ls"]          = new ListDirectoryCommand;
    commands["cat"]         = new CatCommand;
    commands["mkdir"]       = new MakeDirCommand;
    commands["rmdir"]       = new RemoveDirCommand;
    commands["touch"]       = new TouchCommand;
    commands["append"]      = new AppendCommand;
    commands["probe"]       = new ProbeCommand;
    commands["help"]        = new HelpCommand;
    commands["notes"]       = new NotesCommand;
    commands["addNote"]     = new AddNoteCommand;
    commands["rm"]          = new RemoveCommand;
}