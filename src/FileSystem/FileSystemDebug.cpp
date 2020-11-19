#include <bits/stdc++.h>
#include "File.hpp"
#include "Folder.hpp"


int main() {
    Folder root("/");
    Folder *home = new Folder("home");
    Folder *log = new Folder("log");
    Folder *bin = new Folder("bin");
    Folder *sys = new Folder("sys");
    Folder *notes = new Folder("notes");
    File *testFile = new File("testfile.txt", "thiswontbeseen");
    notes->insertElement(testFile);
    home->insertElement(notes);
    root.insertElement(home);
    root.insertElement(log);
    root.insertElement(bin);
    root.insertElement(sys);
    std::cout << root.showTree() << '\n';
}
