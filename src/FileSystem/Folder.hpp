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
            return listChildren(0);
        }

        std::string listChildren(int depth) {
            std::string ans, offset;
            for (int i = 0; i < depth; i++) {
                offset += '|';
            }

            for (auto c : children) {
                ans += offset + c->toString() + '\n';
            }

            return ans;
        }

        std::string showTree() {
            return showTree("");
        }

        std::string showTree(const std::string &prefix)  {
            std::string ans = prefix + toString();

            for (auto c : children) {
                ans += '\n';
                ans += c->showTree(prefix + '|');
            }
            return ans;
        }

        void insertElement(FileSystemElement *elem) {
            children.push_back(elem);
            elem->setParent(this);
        }
};
