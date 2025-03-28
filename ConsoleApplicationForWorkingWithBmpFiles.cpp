#include "ConsoleApplicationForWorkingWithBmpFiles.h"
#include <fstream>
#include <string>
#include <iostream>
#include <Windows.h>

ConsoleApplicationForWorkingWithBmpFiles::ConsoleApplicationForWorkingWithBmpFiles()
{
	white.red = 255;
	white.green = 255;
	white.blue = 255;
	white.alpha = 255;
	black.red = 0;
	black.green = 0;
	black.blue = 0;
	black.alpha = 255;
}

ConsoleApplicationForWorkingWithBmpFiles::~ConsoleApplicationForWorkingWithBmpFiles()
{
	delete[] data;
}

int* ConsoleApplicationForWorkingWithBmpFiles::getSize()
{
	int size[2];
	size[0] = (int)bmpFileInfo.biWidth;
	size[1] = (int)bmpFileInfo.biHeight;
	return size;
};

std::string ConsoleApplicationForWorkingWithBmpFiles::checkColor(int x, int y)
{
	int index;
	index = ((bmpFileInfo.biHeight - 1 - y) * bmpFileInfo.biWidth + x) * bmpFileInfo.biBitCount / 8;
	if (data[index] == white.blue &&
		data[index + 1] == white.green &&
		data[index + 2] == white.red)
	{
		return "white";
	}
	if (data[index] == black.blue &&
		data[index + 1] == black.green &&
		data[index + 2] == black.red)
	{
		return "black";
	}
	return "other";
}

void ConsoleApplicationForWorkingWithBmpFiles::drawPoint(int x, int y)
{
	int index;
	index = ((bmpFileInfo.biHeight - 1 - y) * bmpFileInfo.biWidth + x) * bmpFileInfo.biBitCount / 8;
	data[index] = black.blue;
	data[index + 1] = black.green;
	data[index + 2] = black.red;
	if (bmpFileInfo.biBitCount == 32)
	{
		data[index + 3] = black.alpha;
	}
}

void ConsoleApplicationForWorkingWithBmpFiles::drawLine(const int(&point1)[2], const int(&point2)[2])
{
	int x1;
	int x2;
	int y1;
	int y2;
	int deltaX;
	int deltaY;
	int directionX;
	int directionY;
	int error;

	x1 = point1[0];
	x2 = point2[0];
	y1 = point1[1];
	y2 = point2[1];
	directionX = x1 < x2 ? 1 : -1;
	directionY = y1 < y2 ? 1 : -1;
	deltaX = abs(x1 - x2);
	deltaY = abs(y1 - y2);
	error = deltaX - deltaY;

	do
	{
		drawPoint(x1, y1);
		int error2;
		error2 = error * 2;

		if (error2 > -deltaY)
		{
			error -= deltaY;
			x1 += directionX;
		}
		if (error2 < deltaX)
		{
			error += deltaX;
			y1 += directionY;
		}
	} while ((x1 != x2) || (y1 != y2));
	drawPoint(x1, y1);
}

void ConsoleApplicationForWorkingWithBmpFiles::display()
{
	for (int i = 0; i < bmpFileInfo.biHeight; ++i)
	{
		for (int j = 0; j < bmpFileInfo.biWidth; ++j)
		{
			if (checkColor(j, i) == "white")
			{
				std::cout << "_";
			}
			else if (checkColor(j, i) == "black")
			{
				std::cout << "@";
			}
			else
			{
				std::cout << "!";
			}
		}
		std::cout << "\n";
	}
}

void ConsoleApplicationForWorkingWithBmpFiles::openFile()
{
	std::string fileName;
	std::ifstream file;
	do
	{
		system("cls");
		std::cout << "Enter input BMP file name: ";
		std::cin >> fileName;
		file.open(fileName, std::ios::in | std::ios::binary);
	} while (!file.is_open());
	file.read((char*)&bmpFileHeader, sizeof(BITMAPFILEHEADER));
	file.read((char*)&bmpFileInfo, sizeof(BITMAPINFOHEADER));
	file.seekg(bmpFileHeader.bfOffBits);
	data = new unsigned char[bmpFileInfo.biSizeImage];
	file.read((char*)data, bmpFileInfo.biSizeImage * sizeof(char));
	file.close();
}

void ConsoleApplicationForWorkingWithBmpFiles::saveFile()
{
	std::string fileName;
	std::ofstream file;
	do
	{
		std::cout << "\nEnter output BMP file name: ";
		std::cin >> fileName;
		file.open(fileName, std::ios::out | std::ios::binary);

	} while (!file.is_open());
	file.write((char*)&bmpFileHeader, sizeof(BITMAPFILEHEADER));
	file.write((char*)&bmpFileInfo, sizeof(BITMAPINFOHEADER));
	file.write((char*)data, bmpFileInfo.biSizeImage * sizeof(char));
	file.close();
	std::cout << "File saved";
}