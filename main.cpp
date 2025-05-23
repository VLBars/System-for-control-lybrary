#include "LibraryManager.h"
#include <clocale>

int main() {
    setlocale(LC_ALL, "Russian"); 
    LibraryManager libraryManager;
    libraryManager.run();
    return 0;
}