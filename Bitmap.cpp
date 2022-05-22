#include "Bitmap.h"

#include "BitmapInfo.h"
#include "BitmapFile.h"

#include <fstream>



namespace fractaldrawing {

	Bitmap::Bitmap(int w, int h)
		: m_width(w), m_height(h), m_pixels(new uint8_t[w * h * 3]{})
	{

	}

	Bitmap::~Bitmap()
	{

	}

	bool Bitmap::write(const std::string& filename)
	{
		BitmapFile fh;
		BitmapInfo ih;

		fh.file_size = sizeof(BitmapFile) + sizeof(BitmapInfo) + m_width * m_height * 3;
		fh.data_offset = sizeof(BitmapFile) + sizeof(BitmapInfo);

		ih.width = m_width;
		ih.height = m_height;

		std::ofstream ofs{ filename, std::ios::out | std::ios::binary };
		if (!ofs) {
			return false;
		}

		ofs.write(reinterpret_cast<char*>(&fh), sizeof(fh));
		ofs.write(reinterpret_cast<char*>(&ih), sizeof(ih));
		ofs.write(reinterpret_cast<char*>(m_pixels.get()), m_width * m_height * 3);

		ofs.close();

		return true;
	}

	void Bitmap::set_pixel(Width x, Height y, Color red, Color green, Color blue)
	{
		uint8_t* pixel = m_pixels.get();

		pixel += (y.get() * 3) * m_width + (x.get() * 3);

		pixel[0] = blue.get();
		pixel[1] = green.get();
		pixel[2] = red.get();
	}

}