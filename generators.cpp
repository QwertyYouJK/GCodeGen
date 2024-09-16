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
	outFile << "G00 " << "X" << (int)(xPos * 1000) << " Y" << (int)(yPos * 1000) << " Z" << (int)(zPos * 1000) << "\n";
	outFile.close();
}

void spiral(const std::string& filename, const float radius, const float zDown, const float feedRate) {

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
	outFile << "M03 S" << spinSpeed << "\n";
	outFile.close();
}

void drillStop(const std::string& filename) {
	auto outFile = appendFile(filename);
	outFile << "M05\n";
	outFile.close();
}

void setAbs(const std::string& filename) {
	auto outFile = appendFile(filename);
	outFile << "G90 (absolute)\n";
	outFile.close();
}

void setInc(const std::string& filename) {
	auto outFile = appendFile(filename);
	outFile << "G91 (relative)\n";
	outFile.close();
}

void beginSettings(const std::string& filename) {
	std::ofstream outFile(filename);
	outFile << "%\n";
	outFile << "O01\n";
	outFile << "G21 (millimeter unit)\n";
	outFile << "G90 (abs)\n";
	outFile.close();
}

void endFile(const std::string& filename) {
	auto outFile = appendFile(filename);
	outFile << "M30 (end)\n";
	outFile << "%";
	outFile.close();
}