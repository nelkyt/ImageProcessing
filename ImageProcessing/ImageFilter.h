#pragma once
#include <vector>
#include <iostream>

namespace ImageFilter
{
	void makeWhite(std::vector<unsigned char> &image)
	{
		for (unsigned i = 0; i < image.size(); i++)
		{
			image[i] = 255;
		}
	}
};