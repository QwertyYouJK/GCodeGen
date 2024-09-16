#include "generators.h"

int main(int argc, char* argv[]) {
  
    if (argc != 3) {
        std::cout << "Command: [./program.exe] [xPos] [yPos]\n";
        return 1;
    }

    int xPos = atoi(argv[1]);
    int yPos = atoi(argv[2]);
    std::string filename = "coords.nc";

    beginSettings(filename);
    move(filename, xPos, yPos, 50);
    endFile(filename);
}