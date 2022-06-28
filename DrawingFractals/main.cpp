#include "Zoom.h"
#include "FractalCreator.h"
#include "RGB.h"

#include <iostream>

using namespace std;

int main()
{
	int const WIDTH = 800;
	int const HEIGHT = 600;

	FractalCreator fractalCreator(WIDTH, HEIGHT);
	fractalCreator.run("test.bmp");
	
	return 0;
}