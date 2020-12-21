#pragma once
#include "FileSystemElement.hpp"

class Executable : public FileSystemElement {
    std::string scriptName;

    public: 
        Executable(std::string name, std::string scriptName) : scriptName{ scriptName }, FileSystemElement(name) { }
        
        static void registerUsertype(sol::state& lua) {
            sol::usertype<Executable> executableType = lua.new_usertype<Executable>("Executable",
                //sol::constructors<Executable(std::string, std::string)>(), // May cause unwanted execution.
                sol::base_classes, sol::bases<FileSystemElement>());

            executableType.set_function("getName", &Executable::getName);
            executableType.set_function("getType", &Executable::getType);
            executableType.set_function("setParent", &Executable::setParent);

            executableType.set_function("delete", &Executable::destroy);
        }

        FileSystemType getType() { return FileSystemType::Executable; }

        std::string getScript() { return scriptName; }
};