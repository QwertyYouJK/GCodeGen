#include "GCodeGen.h"

constexpr float MIN_Y = -165.0;
constexpr int RPM = 4500;
constexpr float MAX_Z = 86.5;
constexpr float SCREW_HEAD_RADIUS = 1.5;

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
        // read coordinates from a coords file
        auto coords = readCoords();
        if (coords.empty()) {
            std::cout << "No screws detected!\n";
            return 1;
        }
        // write G code file
        beginSettings(filename);
        double feedRate;
        // loop drill through all screw coords
        for (const auto i : coords) {
            screwType opt;
            if (i.second >= 165.0) {
                std::cout << "Far screw\n";
                opt = FAR;
                feedRate = 150.0;
            }
            else if (i.second < 165.0 && i.second > 125) {
                std::cout << "Middle screw\n";
                opt = MIDDLE;
                feedRate = 97.0;
            }
            else if (i.second <= 125.0) {
                std::cout << "Close screw\n";
                opt = CLOSE;
                feedRate = 150.0;
            }
            move(filename, i.first, i.second, 500);
            move(filename, i.first, i.second, 12); // change number to right above HDD
            drillStart(filename, RPM);
            setInc(filename);
            drill(filename, SCREW_HEAD_RADIUS, 3, feedRate, opt); // change first number to how deep to drill, third number for feedRate
            drillStop(filename);
            newLine(filename);
            setAbs(filename);
        }
        endFile(filename);
        std::cout << "G code file generated successfully\n";
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