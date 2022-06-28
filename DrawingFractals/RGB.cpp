#include "RGB.h"

RGB::RGB(double red, double green, double blue) : r(red), g(green), b(blue)
{
}

RGB operator-(const RGB& first, const RGB& second)
{
	return RGB(first.r - second.r, first.g - second.g, first.b - second.b);
}
