#pragma once
#include <string>

class FileSystemElement {
    protected:
        std::string name;
        FileSystemElement(std::string elementName) {
            name = elementName;
        }
    public:
        virtual ~FileSystemElement() {  }

        virtual std::string showTree(const std::string &prefix) = 0;

        std::string toString() {
            return name;
        }
};
