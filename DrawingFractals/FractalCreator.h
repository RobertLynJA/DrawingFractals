#pragma once
#include <string>
#include <vector>
#include "Zoom.h"
#include "Mandelbrot.h"
#include "ZoomList.h"
#include "Bitmap.h"

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

	void calculateIteration();
	void drawFractal();
	void calculateTotalIterations();

public:
	FractalCreator(int width, int height);
	~FractalCreator();

	void addZoom(const Zoom& zoom);
	void writeBitmap(std::string name);
};

