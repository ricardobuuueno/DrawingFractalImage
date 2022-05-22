#pragma once

namespace fractaldrawing {

	struct Zoom {
		int y{};
		int x{};
		double scale{};

		Zoom(int x, int y, double scale) : x(x), y(y), scale(scale) {}
	};

}