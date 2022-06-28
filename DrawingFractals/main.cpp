#include "Zoom.h"
#include "FractalCreator.h"

using namespace std;

int main()
{
	int const WIDTH = 800;
	int const HEIGHT = 600;

	FractalCreator fractalCreator(WIDTH, HEIGHT);

	fractalCreator.addZoom(Zoom(295, HEIGHT - 202, 0.1));
	fractalCreator.addZoom(Zoom(312, HEIGHT - 304, 0.1));

	fractalCreator.writeBitmap("test.bmp");
	
	return 0;
}