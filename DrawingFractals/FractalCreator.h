#pragma once
#include <string>
#include <vector>
#include "Zoom.h"
#include "Mandelbrot.h"
#include "ZoomList.h"
#include "Bitmap.h"
#include "RGB.h"

class FractalCreator
{
private: 
	std::vector<int> m_histogram;
	std::vector<int> m_fractal;
	Bitmap m_bitmap;
	ZoomList m_zoomList;
	int m_width;
	int m_height;
	int m_total{ 0 };

	std::vector<int> m_ranges;
	std::vector<RGB> m_colors;
	std::vector<int> m_rangeTotals;

	bool m_bGotFirstRange{ false };

	void calculateIteration();
	void drawFractal();
	void calculateTotalIterations();
	void calculateRangeTotals();
	void writeBitmap(std::string name);

public:
	FractalCreator(int width, int height);
	~FractalCreator();
	void addRange(double rangeEnd, const RGB& rgb);
	void addZoom(const Zoom& zoom);
	void run(std::string filename);

};

