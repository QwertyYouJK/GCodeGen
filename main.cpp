#include "GCodeGen.h"

constexpr float MIN_Y = 300.0;
constexpr int RPM = 4500;
constexpr float MAX_Z = 300;
constexpr float SCREW_HEAD_RADIUS = 1.5;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Arguments: [./program.exe] [command]\n";
        std::cout << "command: move-table/drill-screws\n";
        return 1;
    }
    
    std::string command = argv[1];
    std::string filename = "coords.nc";
    
    if (command == "move-table") {
        // move table to the front to take picture
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
            move(filename, i.first, i.second, 50); // change number to right above screw
            drillStart(filename, RPM);
            setInc(filename);
            drill(filename, SCREW_HEAD_RADIUS, 2.5, feedRate, opt); // change number to how deep to drill (put this in increments of 0.5)
            drillStop(filename);
            newLine(filename);
            setAbs(filename);
        }
        setAbs(filename);
        // move to Y=170 and wait; run gripper
        move(filename, 0, 170, 300);
        wait(filename, 600);
        endFile(filename);
        std::cout << "G code file generated successfully\n";
    }
    else if (command == "test") {
        // for testing
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