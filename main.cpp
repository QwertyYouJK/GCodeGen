#include "generators.h"

int main() {
    int argc = 3;
    const char* argv[] = { "program.exe", "200", "200" };
    
    if (argc == 1) {
        std::cout << "No command-line arguments passed.\n";
        return 1;
    }

    int xPos = atoi(argv[1]);
    int yPos = atoi(argv[2]);
    std::string filename = "coords.nc";

    beginSettings(filename);
    move(filename, xPos, yPos, 50);
    endFile(filename);
}