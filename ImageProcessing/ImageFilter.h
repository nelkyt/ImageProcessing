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

	/* Keeps only the extracted color channel and sets the others to zero. Alpha channel remains untouched. */
	void extractColorChannel(unsigned colorChannel, std::vector<unsigned char>& image)
	{
		unsigned removableChannels[2];
		if (colorChannel == 0)
		{
			removableChannels[0] = 1;
			removableChannels[1] = 2;
		}
		else if (colorChannel == 1)
		{
			removableChannels[0] = 0;
			removableChannels[1] = 2;
		}
		else
		{
			removableChannels[0] = 0;
			removableChannels[1] = 1;
		}

		for (size_t i = 0; i < image.size() / 4; ++i)
		{
			image[4 * i + removableChannels[0]] = 0;
			image[4 * i + removableChannels[1]] = 0;
		}
	}

	/* Copies original image into a larger image padded with 0s according to the filter width */
	std::vector<unsigned char> createPaddedImage(std::vector<unsigned char> &image, size_t width, size_t height, size_t filterSize)
	{
		// the filter matrix will overlap at most by half its size to the outside of the image
		size_t paddingSize = filterSize / 2,
		paddedWidth = width + 2 * paddingSize, // padding is added to both left and right
		paddedHeight = height + 2 * paddingSize; // padding is added above and below
		std::vector<unsigned char> paddedImage(4 * paddedWidth * paddedHeight, 0);

		for (size_t y = 0; y < height; ++y)
		{
			size_t paddedY = y + paddingSize;
			for (size_t x = 0; x < width; ++x)
			{
				size_t paddedX = x + paddingSize;
				for (size_t c = 0; c < 4; ++c)
				{
					size_t paddedIndex = 4 * (paddedY * paddedWidth + paddedX) + c;
					size_t imageIndex =  4 * (y * width + x) + c;
					paddedImage[paddedIndex] = image[imageIndex];
				}
			}
		}
		return paddedImage;
	}
};