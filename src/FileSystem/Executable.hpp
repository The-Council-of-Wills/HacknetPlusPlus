#pragma once
#include "FileSystemElement.hpp"
#include "../Commands/Command.hpp"

class Executable : public FileSystemElement, public Command {
    protected:
        Executable(std::string name) : FileSystemElement(name) { }
    public: 
        virtual ~Executable() { };

        std::string showTree(std::string prefix, bool last) {
            std::string ans = prefix;
            if (last) {
                ans += u8"└── ";
            }
            else {
                ans += u8"├── ";
            }
            return ans + toString();
        }

        FileSystemType getType() {
            return FileSystemType::Executable;
        }
};