#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

std::ofstream openFile(const std::string& filename);
void move(const std::string& filename, const float xPos, const float yPos);
void move(const std::string& filename, const float zPos);
void move(const std::string& filename, const float xPos, const float yPos, const float feedRate);
void rotate(const std::string& filename, const float xCen, const float yCen, const float zDown, const float feedRate);
void getTool(const std::string& filename, const int toolNum);
void returnTool(const std::string& filename);
void drillStart(const std::string& filename, const float spinSpeed);
void drillStop(const std::string& filename);
void setting(const std::string& filename);
void setAbs(const std::string& filename);
void setInc(const std::string& filename);
void end(const std::string& filename);
