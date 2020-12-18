#pragma once
#include <vector>
#include <iostream>
#include <map>
#include "FileSystemElement.hpp"
#include "File.hpp"

class Folder : public FileSystemElement {
    private:
        std::map<std::string, FileSystemElement*> children;
        sol::state* lua;

    public:
        Folder(std::string folderName) : FileSystemElement(folderName) {  }

        ~Folder() {
            for (auto c : children) {
                delete c.second;
            }
        }

        static void registerUsertype(sol::state& lua) {

            sol::usertype<Folder> folderType = lua.new_usertype<Folder>("Folder",
                sol::constructors<Folder(std::string)>(),
                sol::base_classes, sol::bases<FileSystemElement>());

            folderType.set_function("getTree", sol::resolve<std::string()>(&Folder::getTree));
            folderType.set_function("getType", &Folder::getType);
            folderType.set_function("setParent", &Folder::setParent);
            folderType.set_function("openFolder", &Folder::getOrCreateFolder);
            folderType.set_function("openFile", &Folder::openFile);
            folderType.set_function("getElement", &Folder::getElementObject);
            folderType.set_function("getChildren", &Folder::getChildrenTable);

            folderType.set_function("getFiles", &Folder::getFilesTable);
            //folderType.set_function("getFile", &Folder::getFile);

            folderType.set_function("getFolders", &Folder::getFoldersTable);
            //folderType.set_function("getFile", &Folder::getFolder);
        }

        FileSystemType getType() {
            return FileSystemType::Folder;
        }

        FileSystemElement* getElement(std::string elementName) {
            if (children.count(elementName))
                return children[elementName];
            return nullptr;
        }

        sol::object getElementObject(sol::this_state s, std::string elementName) {
            FileSystemElement* element = getElement(elementName);

            if (element == nullptr)
                return sol::nil;
            else if (element->getType() == FileSystemType::File)
                return sol::make_object(s, (File*)element);
            else if (element->getType() == FileSystemType::Folder)
                return sol::make_object(s, (Folder*)element);
            else
                return sol::nil;
        }

        Folder* getOrCreateFolder(std::string elementName) {
            Folder* temp = (Folder*)getElement(elementName);
            if (temp != nullptr) return temp;
            temp = new Folder(elementName);
            insertElement(temp);
            return temp;
        }

        File* openFile(std::string elementName) {
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

        std::vector<File*> getFiles() {
            std::vector<File*> ret;

            for (auto child : children)
                if (child.second->getType() == FileSystemType::File)
                    ret.push_back((File*) child.second);

            return ret;
        }

        sol::as_table_t<std::vector<File*>> getFilesTable() {
            return sol::as_table(getFiles());
        }

        /*
        File* getFile(std::string name) {
            if (children[name]->getType() == FileSystemType::File)
                return (File*)children[name];
            else return nullptr;
        }
        */

        std::vector<Folder*> getFolders() {
            std::vector<Folder*> ret;

            for (auto child : children)
                if (child.second->getType() == FileSystemType::Folder)
                    ret.push_back((Folder*) child.second);

            return ret;
        }

        sol::as_table_t<std::vector<Folder*>> getFoldersTable() {
            return sol::as_table(getFolders());
        }

        /*
        Folder* getFolder(std::string name) {
            if (children[name]->getType() == FileSystemType::Folder)
                return (Folder*)children[name];
            else return nullptr;
        }
        */

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

        static FileSystemElement* evaluatePath(Folder* curr, std::string path) {
            if (path[0] == '/') {
                while (curr->getParent() != nullptr)
                    curr = (Folder*) curr->getParent();
            }

            std::stringstream pathStream(path);
            std::string buffer;
            bool foundFile = false;
            while (getline(pathStream, buffer, '/')) {
                if (buffer.empty() || buffer == ".") continue;
                if (curr == nullptr) return nullptr;
                if (curr->getType() == FileSystemType::Folder) {
                    if (buffer == "..") {
                        curr = (Folder*) curr->getParent();
                    }
                    else {
                        Folder* currFolder = (Folder *)curr;
                        curr = (Folder*) currFolder->getElement(buffer);
                    }
                }
                else if (foundFile) {
                    return nullptr;
                }
                else {
                    foundFile = true;
                }
            }

            return curr;
        }

        FileSystemElement* evaluatePath(std::string path) {
            return Folder::evaluatePath(this, path);
        }
};
