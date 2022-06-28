#include "FractalCreator.h"
#include <cassert>

FractalCreator::FractalCreator(int width, int height) : m_width(width), m_height(height),
	m_histogram(Mandelbrot::MAX_ITERATIONS + 1, 0), m_fractal(width * height, 0),
	m_bitmap(width, height), m_zoomList(width, height)
{
	addZoom(Zoom(width / 2, height / 2, 4.0 / width));
}

FractalCreator::~FractalCreator()
{
}

void FractalCreator::run(std::string filename)
{	
	calculateIteration();
	calculateTotalIterations();
	calculateRangeTotals();
	drawFractal();

	writeBitmap(filename);
}

void FractalCreator::calculateRangeTotals()
{
	int rangeIndex = 0;

	for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++)
	{
		int pixels = m_histogram[i];

		if (i >= m_ranges[rangeIndex + 1])
		{
			rangeIndex++;
		}

		m_rangeTotals[rangeIndex] += pixels;
	}
}

int FractalCreator::getRange(int iterations) const
{
	int range = 0;

	for (int i = 0; i < m_ranges.size(); i++)
	{
		range = i;

		if (m_ranges[i] > iterations)
		{
			break;
		}
	}

	range--;

	assert(range > -1);
	assert(range < m_ranges.size());

	return range;
}

void FractalCreator::addRange(double rangeEnd, const RGB &rgb)
{
	m_ranges.push_back(rangeEnd * Mandelbrot::MAX_ITERATIONS);
	m_colors.push_back(rgb);

	if (m_bGotFirstRange) {
		m_rangeTotals.push_back(0);
	}

	m_bGotFirstRange = true;
}

void FractalCreator::calculateIteration()
{
	for (int x = 0; x < m_width; x++)
	{
		for (int y = 0; y < m_height; y++)
		{
			auto coords = m_zoomList.doZoom(x, y);

			int iterations = Mandelbrot::getIterations(coords.first, coords.second);

			m_fractal[y * m_width + x] = iterations;

			m_histogram[iterations]++;
		}
	}

	m_histogram.pop_back(); //Remove max iterations.
}

void FractalCreator::drawFractal()
{
	RGB startColor(0, 0, 0);
	RGB endColor(0, 0, 255);
	RGB colorDiff = endColor - startColor;

	for (int x = 0; x < m_width; x++)
	{
		for (int y = 0; y < m_height; y++)
		{
			int iterations = m_fractal[y * m_width + x];

			int range = getRange(iterations);
			int rangeTotal = m_rangeTotals[range];
			int rangeStart = m_ranges[range];

			RGB& startColor = m_colors[range];
			RGB& endColor = m_colors[range + 1];
			RGB colorDiff = endColor - startColor;

			double hue = 0;
			uint8_t red{ 0 };
			uint8_t green{ 0 };
			uint8_t blue{ 0 };

			if (iterations != Mandelbrot::MAX_ITERATIONS)
			{
				int totalPixels = 0;

				for (int i = rangeStart; i <= iterations; i++)
				{
					totalPixels += m_histogram[i];
				}

				red = startColor.r + colorDiff.r * (double)totalPixels / rangeTotal;
				green = startColor.g + colorDiff.g * (double)totalPixels / rangeTotal;
				blue = startColor.b + colorDiff.b * (double)totalPixels / rangeTotal;
			}

			m_bitmap.setPixel(x, y, red, green, blue);
		}
	}
}

void FractalCreator::addZoom(const Zoom& zoom)
{
	m_zoomList.add(zoom);
}

void FractalCreator::writeBitmap(std::string name)
{
	m_bitmap.write(name);
}

void FractalCreator::calculateTotalIterations()
{
	m_total = 0;

	for (auto val : m_histogram)
	{
		m_total += val;
	}
}
