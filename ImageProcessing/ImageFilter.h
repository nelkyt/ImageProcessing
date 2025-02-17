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
};