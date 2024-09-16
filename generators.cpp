#include "generators.h"

std::ofstream openFile(const std::string& filename) {
	std::ofstream outFile(filename);
	if (!outFile) {
		std::cerr << "Error creating file!\n";
		return {};
	}
	return outFile;
}

void move(const std::string& filename, const float xPos, const float yPos) {
	auto outFile = openFile(filename);
	outFile << "G00 " << "X" << xPos << ".0 " << "Y" << yPos << ".0\n";
	outFile.close();
}

void move(const std::string& filename, const float zPos) {
	auto outFile = openFile(filename);
	outFile << "G00 " << "Z" << zPos << ".0\n";
	outFile.close();
}

void move(const std::string& filename, const float xPos, const float yPos, const float feedRate) {
	auto outFile = openFile(filename);
	outFile << "G01 " << "X" << xPos << ".0 " << "Y" << yPos << ".0" << "F" << feedRate << ".0\n";
	outFile.close();
}

void rotate(const std::string& filename, const float xCen, const float yCen, const float zDown, const float feedRate) {

}

void getTool(const std::string& filename, const int toolNum) {

}

void returnTool(const std::string& filename) {

}

void drillStart(const std::string& filename, const float spinSpeed) {

}

void drillStop(const std::string& filename) {

}

void setting(const std::string& filename) {

}

void setAbs(const std::string& filename) {

}

void setInc(const std::string& filename) {

}

void end(const std::string& filename) {

}