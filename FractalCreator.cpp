#include "FractalCreator.h"
#include <cassert>


namespace fractaldrawing {
	
	FractalCreator::FractalCreator(int width, int height)
		: m_width(width), 
		  m_height(height), 
		  m_histogram(new int[Mandelbrot::MAX_ITERATIONS]{ 0 }), 
		  m_fractal(new int[m_width * m_height]{ 0 }), 
		  m_bitmap(width, height),
		  m_zoomlist(width, height)
	{
		m_zoomlist.add(Zoom(m_width / 2, m_height / 2, 4.0 / m_width));
	}

	FractalCreator::~FractalCreator()
	{
	}

	void FractalCreator::addRange(double rangeEnd, const RGB& rgb)
	{
		m_ranges.push_back(static_cast<int>(rangeEnd * Mandelbrot::MAX_ITERATIONS));
		m_colors.push_back(rgb);

		if (m_bGotFirstRange) {
			m_rangesTotal.push_back(0);
		}

		m_bGotFirstRange = true;

	}

	void FractalCreator::addZoom(const Zoom& zoom)
	{
		m_zoomlist.add(zoom);
	}

	void FractalCreator::run(std::string name)
	{

		calculateIteration();

		calculateTotalIterations();

		calculateRangeTotals();

		drawFractal();

		writeBitmap(name);
	}

	void FractalCreator::calculateIteration()
	{
		for (int y = 0; y < m_height; ++y)
		{
			for (int x = 0; x < m_width; ++x)
			{
				auto [xf, yf] = m_zoomlist.doZoom(x, y);

				int iterations = Mandelbrot::getIterations(xf, yf);

				if (iterations != Mandelbrot::MAX_ITERATIONS) {
					m_histogram[iterations]++;
				}

				m_fractal[y * m_width + x] = iterations;

			}
		}
	}

	void FractalCreator::calculateTotalIterations()
	{
		for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; ++i) {
			m_total += m_histogram[i];
		}
	}

	void FractalCreator::calculateRangeTotals()
	{
		int rangeIndex{};

		for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; ++i) {
			int pixels{ m_histogram[i] };

			if (i >= m_ranges[rangeIndex + 1]) {
				++rangeIndex;
			}

			m_rangesTotal[rangeIndex] += pixels;
		}

	}

	void FractalCreator::drawFractal()
	{

		for (int y = 0; y < m_height; ++y)
		{
			for (int x = 0; x < m_width; ++x)
			{
				int iterations = m_fractal[y * m_width + x];

				int range = getRange(iterations);
				int rangeTotal = m_rangesTotal[range];
				int rangeStart = m_ranges[range];

				RGB& startColor = m_colors[range];
				RGB& endColor = m_colors[range + 1];
				RGB colorDiff = endColor - startColor;

				uint8_t red{};
				uint8_t green{};
				uint8_t blue{};

				if (iterations != Mandelbrot::MAX_ITERATIONS) {

					int totalPixels{ 0 };

					for (int i = rangeStart; i <= iterations; ++i) {
						totalPixels += m_histogram[i];
					}

					red = static_cast<uint8_t>(startColor.r + (colorDiff.r * ((double)totalPixels / rangeTotal)));
					green = static_cast<uint8_t>(startColor.g + (colorDiff.g * ((double)totalPixels / rangeTotal)));
					blue = static_cast<uint8_t>(startColor.b + (colorDiff.b * ((double)totalPixels / rangeTotal)));
				}

				m_bitmap.set_pixel(Width{ x }, Height{ y }, Color{ red }, Color{ green }, Color{ blue });
			}
		}
	}

	void FractalCreator::writeBitmap(std::string name)
	{
		m_bitmap.write(name);
	}

	int FractalCreator::getRange(int iterations) const
	{
		int range{};

		for (int i = 1; i < m_ranges.size(); ++i) {
			range = i;
			if (m_ranges[i] > iterations) {
				break;
			}
		}

		--range;

		assert(range > -1);
		assert(range < m_ranges.size());

		return range;
	}

}