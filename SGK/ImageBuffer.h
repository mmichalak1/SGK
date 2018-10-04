#pragma once
#include <vector>

class ImageBuffer
{
public:
	ImageBuffer(uint16_t width, uint16_t height);
	~ImageBuffer();

	void clearWithColor(uint32_t &color);

	std::vector<uint32_t>* getColors();
	uint16_t getWidth() const;
	uint16_t getHeigth() const;

private:
	std::vector<float> depths;
	std::vector<uint32_t> colors;

	uint16_t m_width;
	uint16_t m_height;

};

