#include "ZoomList.h"


namespace fractaldrawing {

	ZoomList::ZoomList(int w, int h) : m_width(w), m_height(h)
	{
	}

	void ZoomList::add(const Zoom& zoom)
	{
		zooms.push_back(zoom);
		
		m_xcenter += ((zoom.x - m_width / 2) * m_scale);
		m_ycenter += -((zoom.y - m_height / 2) * m_scale);

		m_scale *= zoom.scale;

	}

	std::pair<double, double> ZoomList::doZoom(int x, int y)
	{
		double xfractal = ((x - m_width / 2) * m_scale) + m_xcenter;
		double yfractal = ((y - m_height / 2) * m_scale) + m_ycenter;

		return std::pair<double, double>(xfractal, yfractal);
	}

}
