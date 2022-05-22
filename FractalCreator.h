#pragma once

#include "Zoom.h"
#include "Mandelbrot.h"

#include <string>
#include <memory>
#include <vector>

#include "Bitmap.h"
#include "ZoomList.h"
#include "RGB.h"

namespace fractaldrawing {

	class FractalCreator
	{
	private:
		int m_width;
		int m_height;
		std::unique_ptr<int[]> m_histogram;
		std::unique_ptr<int[]> m_fractal;
		Bitmap m_bitmap;
		ZoomList m_zoomlist;
		int m_total{};

		void calculateIteration();
		void calculateTotalIterations();
		void calculateRangeTotals();
		void drawFractal();
		void writeBitmap(std::string name);
		int getRange(int iterations) const;

		std::vector<int> m_ranges;
		std::vector<RGB> m_colors;
		std::vector<int> m_rangesTotal;

		bool m_bGotFirstRange{ false };

	public:
		explicit FractalCreator(int width, int height);
		~FractalCreator();

		void addRange(double rangeEnd, const RGB& rgb);
		void addZoom(const Zoom& zoom);
		void run(std::string name);
		
	};

}

