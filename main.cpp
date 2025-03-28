#include <Windows.h>
#include <iostream>
#include <fstream>
#include "ConsoleApplicationForWorkingWithBmpFiles.h"

int main()
{
	int point1[2];
	int point2[2];
	ConsoleApplicationForWorkingWithBmpFiles app = ConsoleApplicationForWorkingWithBmpFiles();
	app.openFile();
	app.display();
	point1[0] = 0;
	point1[1] = 0;
	point2[0] = (app.getSize()[0] - 1);
	point2[1] = (app.getSize()[1] - 1);
	app.drawLine(point1, point2);
	std::swap(point2[1], point1[1]);
	app.drawLine(point1, point2);
	std::cout << "\n";
	app.display();
	app.saveFile();
	return 0;
}