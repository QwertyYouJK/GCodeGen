#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;

enum screwType {
	FAR,
	MIDDLE,
	CLOSE
};

std::ofstream appendFile(const std::string& filename);
void move(const std::string& filename, const float xPos, const float yPos, const float zPos);
void drill(const std::string& filename, const float radius, const float zDown, const float feedRate, screwType op);
void getTool(const std::string& filename, const int toolNum);
void returnTool(const std::string& filename);
void drillStart(const std::string& filename, const int spinSpeed);
void drillStop(const std::string& filename);
void setAbs(const std::string& filename);
void setInc(const std::string& filename);
void beginSettings(const std::string& filename);
void endFile(const std::string& filename);
void newLine(const std::string& filename);
void wait(const std::string& filename, const int time);
std::vector<std::pair<double, double>> readCoords();
float readHeight();