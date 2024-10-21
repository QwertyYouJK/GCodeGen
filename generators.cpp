#include "generators.h"

std::ofstream appendFile(const std::string& filename) {
	std::ofstream outFile(filename, std::ios::app);
	if (!outFile) {
		std::cerr << "Error creating file!\n";
		return {};
	}
	return outFile;
}

void move(const std::string& filename, const float xPos, const float yPos, const float zPos) {
	auto outFile = appendFile(filename);
	outFile << "G00 " << "X" << (int)(xPos * 1000) << " Y" << (int)(yPos * 1000) << " Z" << (int)(zPos * 1000);
	outFile << "\t(move to coords: " << xPos << ", " << yPos << ", " << zPos << ")\n";
	outFile.close();
}

void drill(const std::string& filename, const float radius, const float zDown, const float feedRate) {
	auto outFile = appendFile(filename);
	// move offset
	outFile << "G00 X-3000\n";
	// set centre 3mm to the right and helical down
	outFile << "(Spin and move 0.5mm down each step)\n";
	for (int i = 0; i < 8; i++) {
		outFile << "G02 I" << (int)(radius * 1000) << " Z" << (int)(zDown * -1000) << " F" << (int)(feedRate * 1000) << "\n";
	}
	// move back up
	outFile << "G00 Z100.0\n";
	outFile.close();
}

void getTool(const std::string& filename, const int toolNum) {
	auto outFile = appendFile(filename);
	outFile << "M06 T" << toolNum << "\n";
	outFile.close();
}

void returnTool(const std::string& filename) {
	auto outFile = appendFile(filename);
	outFile << "M06 T0\n";
	outFile.close();
}

void drillStart(const std::string& filename, const int spinSpeed) {
	auto outFile = appendFile(filename);
	outFile << "M03 S" << spinSpeed;
	outFile << "\t\t\t(Start spindle with " << spinSpeed << " rpm)\n";
	outFile.close();
}

void drillStop(const std::string& filename) {
	auto outFile = appendFile(filename);
	outFile << "M05 \t\t\t\t(Stop spindle)\n";
	outFile.close();
}

void setAbs(const std::string& filename) {
	auto outFile = appendFile(filename);
	outFile << "G90 \t\t\t\t(absolute)\n";
	outFile.close();
}

void setInc(const std::string& filename) {
	auto outFile = appendFile(filename);
	outFile << "G91 \t\t\t\t(relative)\n";
	outFile.close();
}

void beginSettings(const std::string& filename) {
	std::ofstream outFile(filename);
	outFile << "%\n";
	outFile << "O01\n";
	outFile << "G21 \t\t\t\t(micron unit)\n";
	outFile << "G90 \t\t\t\t(abs)\n";
	outFile.close();
}

void endFile(const std::string& filename) {
	auto outFile = appendFile(filename);
	outFile << "M30 \t\t\t\t(end)\n";
	outFile << "%";
	outFile.close();
}

void newLine(const std::string& filename) {
	auto outFile = appendFile(filename);
	outFile << "\n";
	outFile.close();
}

void wait(const std::string& filename, const int time) {
	auto outFile = appendFile(filename);
	outFile << "G04 X" << time << ".0 \t\t\t(wait)\n";
	outFile.close();
}

std::vector<std::pair<double, double>> readCoords() {
	std::vector<std::pair<double, double>> coords;
	auto currentPath = fs::current_path();
	std::cout << "Current path: " << currentPath << '\n';

	// Change directory to previous folder
	fs::path newPath = currentPath / "..";

	// If new path exists, change to previous folder
	if (fs::exists(newPath)) {
		fs::current_path(newPath);
		std::cout << "Changed to path: " << fs::current_path() << std::endl;

		// Open screwCoords.txt
		std::ifstream file("screwCoords.txt"); 
		if (file.is_open()) {
			std::string line;
			while (std::getline(file, line)) {
				std::istringstream iss(line);
				double num1, num2;

				// Extract the two numbers
				if (iss >> num1 >> num2) {
					// Force 2 dp
					double num1_2dp = std::round(num1 * 100.0) / 100.0;
					double num2_2dp = std::round(num2 * 100.0) / 100.0;

					// Store the numbers as a pair
					std::pair<double, double> numbers(num1_2dp, num2_2dp);

					// Output the pair
					std::cout << "Pair: (" << numbers.first << ", " << numbers.second << ")" << std::endl;

					coords.push_back(numbers);
				}
				else {
					std::cerr << "Error: Could not parse line: " << line << std::endl;
				}
			}
			file.close();
		}
		else {
			std::cerr << "Could not open the file in the new path." << std::endl;
		}
	}
	return coords;
}

//float readHeight() {
//
//}