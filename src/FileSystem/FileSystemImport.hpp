#pragma once
#include "Folder.hpp"
#include "File.hpp"

Folder* regularFileSystem() {
    Folder* root = new Folder("/");
    Folder* home = new Folder("home");
    Folder* log = new Folder("log");
    Folder* bin = new Folder("bin");
    Folder* sys = new Folder("sys");
    Folder* notes = new Folder("notes");
    File* noteFile = new File("notes.txt", "1. Take out the trash");
    notes->insertElement(noteFile);
    home->insertElement(notes);
    root->insertElement(home);
    root->insertElement(log);
    root->insertElement(bin);
    root->insertElement(sys);
    return root;
}
