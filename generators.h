#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;

std::ofstream appendFile(const std::string& filename);

// Enter coords in mm
void move(const std::string& filename, const float xPos, const float yPos, const float zPos);

// Enter coords in mm
// radius is radius of screw head
// zDown is go down how many mm
// feedRate is how fast you spin
void drill(const std::string& filename, const float radius, const float zDown, const float feedRate);

void getTool(const std::string& filename, const int toolNum);
void returnTool(const std::string& filename);

// Enter spinSpeed in rpm
void drillStart(const std::string& filename, const int spinSpeed);
void drillStop(const std::string& filename);
void setAbs(const std::string& filename);
void setInc(const std::string& filename);
void beginSettings(const std::string& filename);
void endFile(const std::string& filename);

void newLine(const std::string& filename);

// Enter time in seconds
void wait(const std::string& filename, const int time);
std::vector<std::pair<double, double>> readCoords();
float readHeight();