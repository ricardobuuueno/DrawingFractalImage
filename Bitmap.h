#pragma once

#include <string>
#include <cstdint>
#include <memory>

#include "NamedType.h"


namespace fractaldrawing {

	using Width = NamedType<int, struct WidthParameter>;
	using Height = NamedType<int, struct HeightParameter>;
	using Color = NamedType<uint8_t, struct ColorParameter>;

	class Bitmap
	{
	private: 
		int m_width{};
		int m_height{};

		std::unique_ptr<uint8_t[]> m_pixels{ nullptr };

	public:
		Bitmap(int w, int h);
		virtual ~Bitmap();

		bool write(const std::string& filename);
		void set_pixel(Width x, Height y, Color red, Color green, Color blue);

	};

}

