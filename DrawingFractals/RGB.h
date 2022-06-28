#pragma once
struct RGB
{
	double r;
	double g;
	double b;

	RGB(double red, double green, double blue);
};

RGB operator-(const RGB& first, const RGB& second);
