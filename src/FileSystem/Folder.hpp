#pragma once
#include <vector>
#include <iostream>
#include "FileSystemElement.hpp"
#include "File.hpp"

class Folder : public FileSystemElement {
    private:
        std::vector<FileSystemElement*> children;
    public:
        Folder(std::string folderName) : FileSystemElement(folderName) {  }

        ~Folder() {
            for (auto c : children) {
                delete c;
            }
        }

        bool isFolder() {
            return true;
        }

        std::vector<FileSystemElement*> getChildren() {
            return children;
        }

        std::string listChildren() {
            std::string ans, offset;

            for (auto c : children) {
                ans += offset + c->toString() + '\n';
            }

            return ans;
        }

        std::string showTree() {
            std::string ans = ".";

            for (int i = 0; i < (int)children.size(); i++) {
                ans += '\n';
                if (i == (int)children.size() - 1) {
                    ans += children[i]->showTree("", true);
                }
                else {
                    ans += children[i]->showTree("", false);
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

            ans += toString();

            for (int i = 0; i < (int)children.size(); i++) {
                ans += '\n';
                if (i == (int)children.size() - 1) {
                    ans += children[i]->showTree(prefix, true);
                }
                else {
                    ans += children[i]->showTree(prefix, false);
                }
            }

            return ans;
        }

        void insertElement(FileSystemElement *elem) {
            children.push_back(elem);
            elem->setParent(this);
        }
};
