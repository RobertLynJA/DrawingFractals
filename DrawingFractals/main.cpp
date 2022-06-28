#include <iostream>
#include <vector>
#include <math.h>
#include "Bitmap.h"
#include "Mandelbrot.h"
#include "ZoomList.h"
#include "FractalCreator.h"

using namespace std;

int main()
{
	int const WIDTH = 800;
	int const HEIGHT = 600;

	Bitmap bitmap(WIDTH, HEIGHT);

	double min = 999999;
	double max = -999999;

	ZoomList zoomList(WIDTH, HEIGHT);

	zoomList.add(Zoom(WIDTH / 2, HEIGHT / 2, 4.0 / WIDTH));
	zoomList.add(Zoom(295, HEIGHT - 202, 0.1));
	zoomList.add(Zoom(312, HEIGHT - 304, 0.1));

	vector<int> histogram(Mandelbrot::MAX_ITERATIONS + 1, 0);
	vector<int> fractal(WIDTH * HEIGHT, 0);

	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			auto coords = zoomList.doZoom(x, y);

			int iterations = Mandelbrot::getIterations(coords.first, coords.second);
			
			fractal[y * WIDTH + x] = iterations;

			histogram[iterations]++;			
		}
	}

	histogram.pop_back(); //Remove max iterations.

	int total = 0;

	for (auto val: histogram) 
	{
		total += val;
	}

	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			int iterations = fractal[y * WIDTH + x];

			double hue = 0;

			if (iterations != Mandelbrot::MAX_ITERATIONS) 
			{
				for (int i = 0; i <= iterations; i++)
				{
					hue += (double)histogram[i] / total;
				}
			}

			uint8_t red{ 0 };
			uint8_t green{ (uint8_t)pow(255, hue)};
			uint8_t blue{ 0 };

			bitmap.setPixel(x, y, red, green, blue);
		}
	}

	bitmap.write("test.bmp");

	return 0;
}