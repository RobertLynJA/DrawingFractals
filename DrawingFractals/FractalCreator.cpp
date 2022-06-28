#include "FractalCreator.h"

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

			double hue = 0;

			if (iterations != Mandelbrot::MAX_ITERATIONS)
			{
				for (int i = 0; i <= iterations; i++)
				{
					hue += (double)m_histogram[i] / m_total;
				}
			}

			uint8_t red{ (uint8_t)(startColor.r + colorDiff.r * hue) };
			uint8_t green{ (uint8_t)(startColor.g + colorDiff.g * hue) };
			uint8_t blue{ (uint8_t)(startColor.b + colorDiff.b * hue) };

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
