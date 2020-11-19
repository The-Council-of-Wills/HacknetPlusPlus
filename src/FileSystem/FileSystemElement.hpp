#pragma once
#include <string>

class FileSystemElement {
    protected:
        std::string name;
        FileSystemElement* parent = nullptr;

        FileSystemElement(std::string elementName) {
            name = elementName;
        }
    public:
        virtual ~FileSystemElement() {  }

        virtual std::string showTree(std::string prefix, bool last) = 0;
        virtual bool isFolder() = 0;

        FileSystemElement* getParent() {
            return parent;
        }

        void setParent(FileSystemElement* parentElement) {
            parent = parentElement;
        }

        std::string toString() {
            return name;
        }
};
