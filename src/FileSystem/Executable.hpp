#pragma once
#include "FileSystemElement.hpp"
#include "../lib/sol/sol.hpp"

class Executable : public FileSystemElement {
    private:
        sol::state lua;
        sol::load_result script;
    public: 
        Executable(std::string name, std::string scriptName) : FileSystemElement(name) {
            lua.open_libraries(sol::lib::base);
            script = lua.load_file(scriptName);

            if (!script.valid()) {
                sol::error err = script;
                std::cerr << "There was an error parsing file: " << scriptName << '\n';
                std::cerr << err.what() << '\n';
            }
        }

        FileSystemType getType() {
            return FileSystemType::Executable;
        }

        void run(std::vector<std::string> args) {
            script(args);
        }
};