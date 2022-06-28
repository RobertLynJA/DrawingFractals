#pragma once
#include <string>
#include "Zoom.h"

class FractalCreator
{
public:
	FractalCreator(int width, int height);
	~FractalCreator();

	void calculateIteration();
	void drawFractal();
	void addZoom(const Zoom& zoom);
	void writeBitmap(std::string name);
};

