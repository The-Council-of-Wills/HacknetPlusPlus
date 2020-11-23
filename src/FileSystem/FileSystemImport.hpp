#pragma once
#include <sstream>
#include "Folder.hpp"
#include "File.hpp"

Folder* regularFileSystem() {
    Folder* root = new Folder("/");
    Folder* home = new Folder("home");
    Folder* log = new Folder("log");
    Folder* bin = new Folder("bin");
    Folder* sys = new Folder("sys");
    root->insertElement(home);
    root->insertElement(log);
    root->insertElement(bin);
    root->insertElement(sys);
    return root;
}

FileSystemElement* evaluatePath(FileSystemElement* curr, std::string path) {
    if (path[0] == '/') {
        while (curr->getParent() != nullptr)
            curr = curr->getParent();
    }

    std::stringstream pathStream(path);
    std::string buffer;
    bool foundFile = false;
    while (getline(pathStream, buffer, '/')) {
        if (buffer.empty() || buffer == ".") continue;
        if (curr == nullptr) return nullptr;
        if (curr->isFolder()) {
            if (buffer == "..") {
                curr = curr->getParent();
            }
            else {
                Folder* currFolder = (Folder *)curr;
                curr = currFolder->getElement(buffer);
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
