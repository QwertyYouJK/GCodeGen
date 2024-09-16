#include "generators.h"

int main(int argc, char* argv[]) {
  
    if (argc != 3) {
        std::cout << "Command: [./program.exe] [xPos] [yPos]\n";
        return 1;
    }

    float xPos = atof(argv[1]);
    float yPos = atof(argv[2]);
    std::string filename = "coords.nc";

    beginSettings(filename);
    move(filename, xPos, yPos, 50);
    endFile(filename);

    std::cout << "G code file generated successfully\n";
}