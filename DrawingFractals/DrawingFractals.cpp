// DrawingFractals.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "Bitmap.h"
#include "Mandelbrot.h"

using namespace std;

int main()
{
	int const WIDTH = 800;
	int const HEIGHT = 600;

	Bitmap bitmap(WIDTH, HEIGHT);

	double min = 999999;
	double max = -999999;

	vector<int> histogram(Mandelbrot::MAX_ITERATIONS + 1, 0);
	vector<int> fractal(WIDTH * HEIGHT, 0);

	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			double xFractal{ (x - WIDTH / 2 - 200) * (2.0 / HEIGHT) };
			double yFractal{ (y - HEIGHT / 2) * (2.0 / HEIGHT) };

			int iterations = Mandelbrot::getIterations(xFractal, yFractal);
			
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
			uint8_t green{ (uint8_t)(hue * 255) };
			uint8_t blue{ 0 };

			bitmap.setPixel(x, y, red, green, blue);
		}
	}

	bitmap.write("test.bmp");

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
