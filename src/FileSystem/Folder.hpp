#pragma once
#include <vector>
#include <iostream>
#include <map>
#include "FileSystemElement.hpp"
#include "File.hpp"

class Folder : public FileSystemElement {
    private:
        std::map<std::string, FileSystemElement*> children;
    public:
        Folder(std::string folderName) : FileSystemElement(folderName) {  }

        ~Folder() {
            for (auto c : children) {
                delete c.second;
            }
        }

        bool isFolder() {
            return true;
        }

        FileSystemElement* getElement(std::string elementName) {
            if (children.count(elementName))
                return children[elementName];
            return nullptr;
        }

        std::vector<FileSystemElement*> getChildren() {
            std::vector<FileSystemElement*> ans;
            for (auto c : children) {
                ans.push_back(c.second);
            }
            return ans;
        }

        std::string listChildren() {
            std::string ans;

            for (auto c : children) {
                if (c.second->isFolder()) {
                    ans += '/' + c.second->getName() + '\n';
                }
                else ans += c.second->getName() + '\n';
            }

            return ans;
        }

        std::string showTree() {
            std::string ans = ".";

            for (auto iter = children.begin(); iter != children.end(); iter++) {
                ans += '\n';
                FileSystemElement* elem = iter->second;
                if (std::next(iter) == children.end()) {
                    ans += elem->showTree("", true);
                }
                else {
                    ans += elem->showTree("", false);
                }
            }

            return ans;
        }

        std::string showTree(std::string prefix, bool last) {
            std::string ans = prefix;
            std::string newPrefix = prefix;
            if (last) {
                ans += u8"└── ";
                prefix += "    ";
            }
            else {
                ans += u8"├── ";
                prefix += u8"│   ";
            }

            ans += getName();

            for (auto iter = children.begin(); iter != children.end(); iter++) {
                ans += '\n';
                FileSystemElement* elem = iter->second;
                if (std::next(iter) == children.end()) {
                    ans += elem->showTree(prefix, true);
                }
                else {
                    ans += elem->showTree(prefix, false);
                }
            }

            return ans;
        }

        void insertElement(FileSystemElement *elem) {
            std::string elementName = elem->getName();
            children[elementName] = elem;
            elem->setParent(this);
        }

        void deleteElement(std::string elementName) {
            delete children[elementName];
            children.erase(elementName);
        }
};
