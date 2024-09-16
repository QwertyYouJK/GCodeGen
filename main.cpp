#include "generators.h"

int main() {
	std::vector<std::pair<int, int>> coordinates;
	std::string input;
	std::string filename = "coordinates.custom";

	std::cout << "Enter x-y coordinates (e.g., 3 4). Type 'done' to finish." << std::endl;

	while (true) {
		std::cout << "Enter coordinate: ";
		std::getline(std::cin, input);

		if (input == "done") {
			break;
		}

		std::stringstream ss(input);
		int x, y;
		if (ss >> x >> y) {
			coordinates.push_back(std::make_pair(x, y));
		}
		else {
			std::cout << "Invalid input. Please enter coordinates in the format 'x y'." << std::endl;
		}
	}

	// Write coordinates to a file in a custom format
	std::ofstream outFile(filename);
	if (!outFile) {
		std::cerr << "Error creating file!" << std::endl;
		return 1;
	}

	for (const auto& coord : coordinates) {
		outFile << "X: " << coord.first << ", Y: " << coord.second << std::endl;
	}

	outFile.close();

	// Read the file to verify its content
	std::ifstream inFile(filename);
	if (!inFile) {
		std::cerr << "Error opening file for reading!" << std::endl;
		return 1;
	}

	std::cout << "Contents of " << filename << ":" << std::endl;
	std::string line;
	while (std::getline(inFile, line)) {
		std::cout << line << std::endl;
	}

	inFile.close();
	return 0;
}