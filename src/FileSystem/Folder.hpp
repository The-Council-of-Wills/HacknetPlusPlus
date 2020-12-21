#pragma once
#include <vector>
#include <iostream>
#include <map>
#include "FileSystemElement.hpp"
#include "File.hpp"
#include "Executable.hpp"

class Folder : public FileSystemElement {
    private:
        std::map<std::string, FileSystemElement*> children;
        sol::state* lua;

        FileSystemElement* getElement(std::string elementName) {
            if (children.count(elementName))
                return children[elementName];
            return nullptr;
        }

    public:
        Folder(std::string folderName) : FileSystemElement(folderName) {  }

        ~Folder() override {
            for (auto c : children) {
                delete c.second;
            }
        }

        static void registerUsertype(sol::state& lua) {
            sol::usertype<Folder> folderType = lua.new_usertype<Folder>("Folder",
                sol::constructors<Folder(std::string)>(),
                sol::base_classes, sol::bases<FileSystemElement>());

            folderType.set_function("getName", &Folder::getName);
            folderType.set_function("getTree", sol::resolve<std::string()>(&Folder::getTree));
            folderType.set_function("getType", &Folder::getType);
            folderType.set_function("setParent", &Folder::setParent);
            folderType.set_function("openFolder", &Folder::openFolder);
            folderType.set_function("openFile", &Folder::openFile);
            folderType.set_function("getElement", &Folder::evaluatePathObject);
            folderType.set_function("getChildren", &Folder::getChildrenTable);

            folderType.set_function("getFiles", &Folder::getFilesTable);
            //folderType.set_function("getFile", &Folder::getFile);

            folderType.set_function("getFolders", &Folder::getFoldersTable);
            //folderType.set_function("getFile", &Folder::getFolder);

            folderType.set_function("delete", &Folder::destroy);
        }

        FileSystemType getType() {
            return FileSystemType::Folder;
        }

        Folder* openFolder(std::string elementName) {
            Folder* temp = (Folder*) evaluatePath(elementName);
            if (temp != nullptr) return temp;
            temp = new Folder(elementName);
            insertElement(temp);
            return temp;
        }

        File* openFile(std::string elementName) {
            File* temp = (File*) evaluatePath(elementName);
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

        void deleteElement(std::string elementName) override {
            if (children.count(elementName)) {
                if (children[elementName] != nullptr)
                    delete children[elementName];
                children.erase(elementName);
            }
        }

        FileSystemElement* evaluatePath(std::vector<std::string> path) {
            if (!path.empty()) {
                std::string pathFront = path.front();
                path.erase(path.begin());

                if ((pathFront == "" || pathFront == "..") && this->getParent() != nullptr)
                    return ((Folder*) this->getParent())->evaluatePath(path);
                else if (pathFront == "." || pathFront == "" || pathFront == "..")
                    return this->evaluatePath(path);
                else {
                    FileSystemElement* element = getElement(pathFront);

                    if (element != nullptr)
                        if (element->getType() == FileSystemType::Folder)
                            return ((Folder*)element)->evaluatePath(path);
                        else // WARNING: if another FileSystemElement class is added, this could lead to errors.
                            return element;

                    return nullptr;
                }
            }
            else return this;
        }

        FileSystemElement* evaluatePath(std::string path) {
            std::vector<std::string> pathVector;
            std::string actual = "";

            for (char c : path) {
                if (c != '/') {
                    actual += c;
                }
                else {
                    pathVector.push_back(actual);
                    actual = "";
                }
            }

            if (actual != "")
                pathVector.push_back(actual);

            return evaluatePath(pathVector);
        }

        sol::object evaluatePathObject(sol::this_state s, std::string path) {
            FileSystemElement* element = evaluatePath(path);

            if (element != nullptr)
                if (element->getType() == FileSystemType::File)
                    return sol::make_object(s, (File*)element);
                else if (element->getType() == FileSystemType::Folder)
                    return sol::make_object(s, (Folder*)element);
                else if (element->getType() == FileSystemType::Executable)
                    return sol::make_object(s, (Executable*)element);

            return sol::nil;
        }

};
