#include "generators.h"

constexpr float MIN_Y = -165.0;
constexpr int RPM = 4500;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Arguments: [./program.exe] [command]\n";
        return 1;
    }
    
    std::string command = argv[1];
    std::string filename = "coords.nc";

    if (command == "move-table") {
        beginSettings(filename);
        setInc(filename);
        move(filename, 0, MIN_Y, 0);
        wait(filename, 10);
        endFile(filename);
    }
    else if (command == "drill-screws") {
        // read coordinates from coords file

        // write G code file
        beginSettings(filename);
        drillStart(filename, RPM);
        // put for loop for all screws
        drillStop(filename);
        endFile(filename);
    }

    std::cout << "G code file generated successfully\n";
}

/*
move table:
beginSettings() -> move() -> wait() -> endFile()

check hdd in frame (not used)
take pictures and detection (not used)

drill screws generate:
beginSettings() -> drillStart() -> loop{move() -> spiral() -> move()} -> drillStop() -> endFile()


*/