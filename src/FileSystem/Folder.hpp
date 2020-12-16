#pragma once
#include <vector>
#include <iostream>
#include <map>
#include "FileSystemElement.hpp"
#include "File.hpp"
#include "../lib/sol/sol.hpp"

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

        /*
        static void registerUsertype(sol::state& lua) {
            sol::usertype<Folder> usertype = lua.new_usertype<Folder>("Folder", sol::constructors<Folder(std::string)>());

            // TODO: add getOrCreateFolder, getOrCreateFile, getElement and getChildren
            
            
            usertype.set_function("getTree", &Folder::getTree);
            usertype.set_function("getType", &Folder::getType);
            usertype.set_function("getParent", &Folder::getParent);
            usertype.set_function("setParent", &Folder::setParent);
            usertype.set_function("getName", &Folder::getName);
            usertype.set_function("toString", &Folder::toString);
            
        }
        */

        FileSystemType getType() {
            return FileSystemType::Folder;
        }

        FileSystemElement* getElement(std::string elementName) {
            if (children.count(elementName))
                return children[elementName];
            return nullptr;
        }

        Folder* getOrCreateFolder(std::string elementName) {
            Folder* temp = (Folder*)getElement(elementName);
            if (temp != nullptr) return temp;
            temp = new Folder(elementName);
            insertElement(temp);
            return temp;
        }

        // Probably better named: "openFile"
        File* getOrCreateFile(std::string elementName) {
            File* temp = (File*)getElement(elementName);
            if (temp != nullptr) return temp;
            temp = new File(elementName);
            insertElement(temp);
            return temp;
        }
        
        std::vector<FileSystemElement*> getChildren() {
            std::vector<FileSystemElement*> ans;
            for (auto c : children) {
                ans.push_back(c.second);
            }
            return ans;
        }

        sol::as_table_t<std::vector<FileSystemElement*>> getChildrenTable() {
            return sol::as_table(getChildren());
        }

        std::string listChildren() {
            std::string ans;

            for (auto c : children) {
                if (c.second->getType() == FileSystemType::Folder) {
                    ans += '/' + c.second->getName() + '\n';
                }
                else ans += c.second->getName() + '\n';
            }

            return ans;
        }

        std::string getTree() {
            std::string ans = ".";

            for (auto iter = children.begin(); iter != children.end(); iter++) {
                ans += '\n';
                FileSystemElement* elem = iter->second;
                if (std::next(iter) == children.end()) {
                    ans += elem->getTree("", true);
                }
                else {
                    ans += elem->getTree("", false);
                }
            }

            return ans;
        }

        std::string getTree(std::string prefix, bool last) {
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
                    ans += elem->getTree(prefix, true);
                }
                else {
                    ans += elem->getTree(prefix, false);
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
