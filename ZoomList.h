#pragma once

#include <vector>
#include <utility>

#include "Zoom.h"

namespace fractaldrawing {

	class ZoomList
	{
	private:

		int m_width{};
		int m_height{};

		double m_xcenter{};
		double m_ycenter{};
		double m_scale{1.0};

		std::vector<Zoom> zooms{};

	public:
		ZoomList(int w, int h);
		void add(const Zoom& zoom);
		std::pair<double,double> doZoom(int x, int y);

	};

}

