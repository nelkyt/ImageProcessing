#pragma once
#include <vector>
#include <iostream>

namespace ImageFilter
{
	/* Modifies the entire image to be white */
	void makeWhite(std::vector<unsigned char> &image)
	{
		for (size_t i = 0; i < image.size(); ++i)
		{
			image[i] = 255;
		}
	}

	/* Keeps only the values of the red color channel of the image. */
	void extractRedChannel(std::vector<unsigned char>& image, size_t width, size_t height)
	{
		for (size_t y = 0; y < height; ++y)
		for (size_t x = 0; x < width; ++x)
		{
			// the red and alpha channels are left as they are
			image[4 * width * y + 4 * x + 1] = 0; // set green channel to 0
			image[4 * width * y + 4 * x + 2] = 0; // set blue channel to 0
		}
	}

	/* Keeps only the values of the green color channel of the image. */
	void extractGreenChannel(std::vector<unsigned char>& image, size_t width, size_t height)
	{
		for (size_t y = 0; y < height; ++y)
			for (size_t x = 0; x < width; ++x)
			{
				// the green and alpha channels are left as they are
				image[4 * width * y + 4 * x + 0] = 0; // set red channel to 0
				image[4 * width * y + 4 * x + 2] = 0; // set blue channel to 0
			}
	}

	/* Keeps only the values of the blue color channel of the image. */
	void extractBlueChannel(std::vector<unsigned char>& image, size_t width, size_t height)
	{
		for (size_t y = 0; y < height; ++y)
			for (size_t x = 0; x < width; ++x)
			{
				// the blue and alpha channels are left as they are
				image[4 * width * y + 4 * x + 0] = 0; // set red channel to 0
				image[4 * width * y + 4 * x + 1] = 0; // set green channel to 0
			}
	}
};