#pragma once
#include <string>

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

        virtual std::string showTree(std::string prefix, bool last) = 0;
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
