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

        void destroy() {
            if (parent != nullptr)
                parent->deleteElement(name);
            else
                delete this;
        }

    public:
        virtual ~FileSystemElement() { }
        
        virtual std::string getTree(std::string prefix, bool last) {
            std::string ans = prefix;
            if (last) {
                ans += "\\-- ";
            }
            else {
                ans += u8"|-- ";
            }
            return ans + toString();
        };

        virtual FileSystemType getType() = 0;

        virtual void deleteElement(std::string elementName) { return; }

        FileSystemElement* getParent() {
            return parent;
        }

        void setParent(FileSystemElement* parentElement) {
            parent = parentElement;
        }

        std::string getPath() {
            if (parent != nullptr) {
                std::string parentPath = parent->getPath();

                if (parentPath.back() != '/') //(parentPath != "/")
                    return parentPath + '/' + name;
                else
                    return parentPath + name;
            }
            else if (name.front() != '/')
                return '/' + name;
            else
                return name;
        }

        std::string getName() {
            return name;
        }

        std::string toString() {
            return name;
        }
};
