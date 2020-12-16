#pragma once
#include "FileSystemElement.hpp"
#include "../lib/sol/sol.hpp"

class Executable : public FileSystemElement {
    std::string scriptName;

    public: 
        Executable(std::string name, std::string scriptName) : scriptName{ scriptName }, FileSystemElement(name) { }

        FileSystemType getType() { return FileSystemType::Executable; }

        std::string getScript() { return scriptName; }

        /*
        void run(sol::state* lua, std::vector<std::string> args) {
            sol::load_result script = lua->load_file(scriptName);
            sol::environment local(lua, sol::create, lua->globals());
            sol::set_environment(, script);

            if (!script.valid()) {
                sol::error err = script;
                std::cerr << "There was an error parsing file: " << scriptName << '\n';
                std::cerr << err.what() << '\n';
            }

            script(args);
        }
        */
};