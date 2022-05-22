#pragma once

#include <cstdint>

#pragma pack(push, 2)

namespace fractaldrawing {

	struct BitmapFile {
		char header[2]{ 'B','M' };
		int32_t file_size{};
		int32_t reserved{};
		int32_t data_offset{};
	};


}

#pragma pack(pop)



