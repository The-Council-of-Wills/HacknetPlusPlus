#pragma once
#include "FileSystemElement.hpp"

class Executable : public FileSystemElement {
    std::string scriptName;

    public: 
        Executable(std::string name, std::string scriptName) : scriptName{ scriptName }, FileSystemElement(name) { }

        FileSystemType getType() { return FileSystemType::Executable; }

        std::string getScript() { return scriptName; }
};