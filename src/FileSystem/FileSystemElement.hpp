#pragma once
#include <string>
#include "../lib/sol/sol.hpp"

enum class FileSystemType {
    Folder,
    File,
    Executable
};

class FileSystemElement {
    protected:
        std::string name;
        FileSystemElement* parent = nullptr;

        FileSystemElement(std::string name) : name{name} { }
    public:
        virtual ~FileSystemElement() {  }

        virtual std::string getTree(std::string prefix, bool last) {
            std::string ans = prefix;
            if (last) {
                ans += u8"└── ";
            }
            else {
                ans += u8"├── ";
            }
            return ans + toString();
        };
        virtual FileSystemType getType() = 0;

        FileSystemElement* getParent() {
            return parent;
        }

        void setParent(FileSystemElement* parentElement) {
            parent = parentElement;
        }

        std::string getName() {
            return name;
        }

        std::string toString() {
            return name;
        }
};
