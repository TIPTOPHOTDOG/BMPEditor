#pragma once
#include <Windows.h>
#include <iostream>

struct color {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;
};

class ConsoleApplicationForWorkingWithBmpFiles
{
private:
	BITMAPFILEHEADER bmpFileHeader;
	BITMAPINFOHEADER bmpFileInfo;
	color white;
	color black;
	unsigned char* data;
	std::string checkColor(int x, int y);
	void drawPoint(int x, int y);
public:
	ConsoleApplicationForWorkingWithBmpFiles();
	~ConsoleApplicationForWorkingWithBmpFiles();
	int* getSize();
	void drawLine(const int(&point1)[2], const int(&point2)[2]);
	void display();
	void openFile();
	void saveFile();
};