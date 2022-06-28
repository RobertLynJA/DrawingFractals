#include "Zoom.h"
#include "FractalCreator.h"

#include <iostream>

using namespace std;

int main()
{
	int const WIDTH = 800;
	int const HEIGHT = 600;

	FractalCreator fractalCreator(WIDTH, HEIGHT);

	fractalCreator.addRange(0.0, RGB(0, 0, 0));
	fractalCreator.addRange(0.3, RGB(255, 0, 0));
	fractalCreator.addRange(0.5, RGB(255, 255, 0));
	fractalCreator.addRange(1.0, RGB(255, 255, 255));

	fractalCreator.addZoom(Zoom(295, 202, 0.1));
	fractalCreator.addZoom(Zoom(312, 304, 0.1));

	fractalCreator.run("test.bmp");
	
	return 0;
}