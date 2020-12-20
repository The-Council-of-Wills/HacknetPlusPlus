#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include "GameManager.hpp"
#include "Commands/CommandManager.hpp"
#include "FileSystem/FileSystemImport.hpp"
#include "Computer.hpp"
#include "SDL.h"

void startupText();
void parseArgs(std::string userInput, std::vector<std::string> &out);

int main(int argc, char *argv[]) {
    GameManager::setAppDirFromExe(argv[0]);
    if (argc == 1) {
        std::cerr << "Debug mode enabled" << '\n';
        //std::cerr << "No extension will be loaded." << '\n';
        std::cerr << "Loading sample extension." << '\n';

        GameManager::loadExtension("./extensions/sample");
    }
    else if (argc == 2) {
        std::string extensionFolder(argv[1]);
        GameManager::loadExtension(extensionFolder);
    }
    else {
        std::cerr << "Error: unexpected arguments found. Please try again." << '\n';
        return 1;
    }

    startupText();
    
    GameManager* game = GameManager::getInstance();
    CommandManager* commands = new CommandManager();

    game->showConnected();

    while (true) {
        commands->updateExecutables();
        
        //TODO: Process user input in another thread
        std::cout << '>';
        std::string userInput;
        getline(std::cin, userInput);

        if (userInput == "exit") {
            std::cout << "Exiting Hacknet++...\n";
            return 0;
        }

        std::vector<std::string> args;
        parseArgs(userInput, args);
        
        commands->processCommand(args);
    }
}

void startupText() {
    std::string buffer;
    std::ifstream bannerStream(GameManager::getResource("assets/banner"));

    if (bannerStream.is_open()) {
        while (getline(bannerStream, buffer)) {
            std::cout << buffer << '\n';
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        bannerStream.close();
        std::cout << "\n\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "Enter 'help' for a list of commands" << '\n';
}

void parseArgs(std::string userInput, std::vector<std::string> &out) {
    std::stringstream userInputStream(userInput);
    char current;
    bool quote = false;
    std::string buffer;
    while(userInputStream.get(current)) {
        if (current == '"') {
            if (quote) {
                out.push_back(buffer);
                buffer = "";
            }
            quote = !quote;
        }
        else if (quote) {
            buffer += current;
        }
        else if (current == ' ') {
            if (buffer != "") {
                out.push_back(buffer);
                buffer = "";
            }
        }
        else {
            buffer += current;
        }
    }

    if (buffer != "") out.push_back(buffer);
}