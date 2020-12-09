#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "GameManager.hpp"
#include "Commands/CommandManager.hpp"
#include "FileSystem/FileSystemImport.hpp"
#include "Computer.hpp"

void showBanner();
void parseArgs(std::string userInput, std::vector<std::string> &out);

int main(int argc, char *argv[]) {
    if (argc == 1) {
        std::cerr << "Debug mode enabled" << '\n';
        std::cerr << "No extension will be loaded." << '\n';
    }
    else if (argc == 2) {
        std::string extensionFolder(argv[1]);
        GameManager::loadExtension(extensionFolder);
    }
    else {
        std::cerr << "Error: unexpected arguments found. Please try again." << '\n';
        return 1;
    }

    showBanner();
    std::cout << "Enter help for a list of commands" << '\n';

    GameManager* game = GameManager::getInstance();
    CommandManager* commands = new CommandManager();

    game->showConnected();

    while (true) {
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

void showBanner() {
    std::string buffer;
    std::ifstream bannerStream("assets/banner");

    if (!bannerStream.is_open()) return;

    while (getline(bannerStream, buffer)) {
        std::cout << buffer << '\n';
    }

    bannerStream.close();

    std::cout << "\n\n\n\n";
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