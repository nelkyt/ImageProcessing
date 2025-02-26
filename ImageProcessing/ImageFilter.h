#pragma once
#include <vector>
#include <iostream>
#include <math.h>

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
	std::vector<unsigned char> zeroPadded(std::vector<unsigned char> &image, size_t width, size_t height, size_t kernelSize)
	{
		// the filter matrix will overlap at most by half its size to the outside of the image
		size_t paddingSize = kernelSize / 2,
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

	/* Copies original image into a larger image padded with replicated values from the edge of the image */
	std::vector<unsigned char> replicationPadded(std::vector<unsigned char>& image, size_t width, size_t height, size_t kernelSize)
	{
		// the filter matrix will overlap at most by half its size to the outside of the image
		size_t paddingSize = kernelSize / 2,
			paddedWidth = width + 2 * paddingSize, // padding is added to both left and right
			paddedHeight = height + 2 * paddingSize; // padding is added above and below
		std::vector<unsigned char> paddedImage(4 * paddedWidth * paddedHeight, 0);

		for (size_t y = 0; y < paddedHeight; ++y)
		{
			for (size_t x = 0; x < paddedWidth; ++x)
			{
				for (size_t c = 0; c < 4; ++c)
				{
					// Makes sure that only pixels in range of the original image can be accessed.
					// In the padding region, automatically clamps to nearest edge pixel in the image.
					
					// variables need to be converted to signed types like int during calculation
					// since size_t with value 0 - paddingSize cannot be calculated
					size_t imageX = std::min(std::max((int)x - (int)paddingSize, 0), (int)width - 1);
					size_t imageY = std::min(std::max((int)y - (int)paddingSize, 0), (int)height - 1);

					size_t paddedIndex = 4 * (y * paddedWidth + x) + c;
					size_t imageIndex = 4 * (imageY * width + imageX) + c;
					paddedImage[paddedIndex] = image[imageIndex];
				}
			}
		}
		return paddedImage;
	}

	std::vector<unsigned char> convertValuesToUnsignedChar(std::vector<float> vector) {
		std::vector<unsigned char> converted(vector.size(), 0);
		for (size_t i = 0; i < vector.size(); ++i)
		{
			converted[i] = round(vector[i]);
		}
		return converted;
	}

	std::vector<unsigned char> convolute(std::vector<unsigned char>& image, std::vector<float> &kernel, size_t width, size_t height, size_t kernelSize)
	{
		std::vector<unsigned char> paddedImage = replicationPadded(image, width, height, kernelSize);
		std::vector<float> result(4 * width * height, 0.0f);
		size_t paddingSize = kernelSize / 2;
		size_t paddedWidth = width + paddingSize * 2;

		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				for (int c = 0; c < 4; ++c)
				{
					size_t resultIndex = 4 * (width * y + x) + c;
					for (int kernelY = 0; kernelY < kernelSize; ++kernelY)
					{
						for (int kernelX = 0; kernelX < kernelSize; ++kernelX)
						{
							size_t paddedX = x + paddingSize;
							size_t paddedY = y + paddingSize;
							size_t paddedKernelY = paddedY - paddingSize + kernelY;
							size_t paddedKernelX = paddedX - paddingSize + kernelX;

							size_t paddedIndex = 4 * (paddedWidth * paddedKernelY + paddedKernelX) + c;
							int kernelIndex = kernelY * kernelSize + kernelX;

							result[resultIndex] += paddedImage[paddedIndex] * kernel[kernelIndex];
						}
					}
				}
			}
		}
		return convertValuesToUnsignedChar(result);
	}

	std::vector<unsigned char> medianBlur(std::vector<unsigned char>& image, size_t width, size_t height, size_t kernelSize)
	{
		std::vector<float> kernel(kernelSize * kernelSize, 1.0f / (float)(kernelSize * kernelSize));
		return convolute(image, kernel, width, height, kernelSize);
	}
};