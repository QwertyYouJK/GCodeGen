#include "generators.h"

constexpr float MIN_Y = -165.0;
constexpr int RPM = 4500;
constexpr float MAX_Z = 86.5;

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
        std::cout << "G code file generated successfully\n";
    }
    else if (command == "drill-screws") {
        try {
            // read coordinates from a coords file
            auto coords = readCoords();
            // write G code file
            beginSettings(filename);
            // loop drill through all screws
            for (const auto i : coords) {
                move(filename, i.first, i.second, 25);
                drillStart(filename, 8000);
                setInc(filename);
                drill(filename, 3, 0.5, 75);
                drillStop(filename);
                newLine(filename);
                setAbs(filename);
            }
            //drillStop(filename);
            endFile(filename);
            std::cout << "G code file generated successfully\n";

        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    else if (command == "test") {
        try {
            auto coords = readCoords();


        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        
    }
    else {
        std::cout << "Command not recognised! Try: move-table/drill-screws/test\n";
    }
}

/*
move table:
beginSettings() -> move() -> wait() -> endFile()

check hdd in frame (not used)
take pictures and detection (not used)

drill screws generate:
beginSettings() -> drillStart() -> loop{move() -> spiral() -> move()} -> drillStop() -> endFile()


*/