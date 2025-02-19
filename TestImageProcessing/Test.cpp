#include "../libs/lodepng.h"
#include <MereTDD/Test.h>
#include "../ImageProcessing/ImageFilter.h"

unsigned red = 0, green = 1, blue = 2;

TEST("Image can be made white")
{
	// test simple example that can be checked programatically.
	std::vector<unsigned char> image;
	unsigned int width = 1, height = 1;
	image.resize(width * height * 4);
	ImageFilter::makeWhite(image);
	std::vector<unsigned char> expected = {255,255,255,255};
	CONFIRM(expected, image);

	// visual test that saves the result to an image.
	unsigned error = lodepng::decode(image, width, height, "../images/cameraman.png");
	if (error)
	{
		std::cout << "Decode error " << error << ": " << lodepng_error_text(error) << std::endl;
	}
	ImageFilter::makeWhite(image);
	error = lodepng::encode("cameraman_white.png", image, width, height);
	if (error)
	{
		std::cout << "Encode error " << error << ": " << lodepng_error_text(error) << std::endl;
	}
}

TEST("Red color channel can be extracted from image")
{
	// white pixel
	std::vector<unsigned char> image = { 255, 255, 255, 255 };
	unsigned width = 1, height = 1;
	// red pixel
	std::vector<unsigned char> expected = { 255, 0, 0, 255 };
	ImageFilter::extractColorChannel(red, image);
	CONFIRM(expected, image);
	image.clear();

	// visual test that saves the result to an image.
	unsigned error = lodepng::decode(image, width, height, "../images/cameraman.png");
	if (error)
	{
		std::cout << "Decode error " << error << ": " << lodepng_error_text(error) << std::endl;
	}
	ImageFilter::extractColorChannel(red, image);
	error = lodepng::encode("cameraman_red_channel.png", image, width, height);
	if (error)
	{
		std::cout << "Encode error " << error << ": " << lodepng_error_text(error) << std::endl;
	}
}

TEST("Green color channel can be extracted from image")
{
	// white pixel
	std::vector<unsigned char> image = { 255, 255, 255, 255 };
	unsigned width = 1, height = 1;
	// red pixel
	std::vector<unsigned char> expected = { 0, 255, 0, 255 };
	ImageFilter::extractColorChannel(green, image);
	CONFIRM(expected, image);
	image.clear();

	// visual test that saves the result to an image.
	unsigned error = lodepng::decode(image, width, height, "../images/cameraman.png");
	if (error)
	{
		std::cout << "Decode error " << error << ": " << lodepng_error_text(error) << std::endl;
	}
	ImageFilter::extractColorChannel(green, image);
	error = lodepng::encode("cameraman_green_channel.png", image, width, height);
	if (error)
	{
		std::cout << "Encode error " << error << ": " << lodepng_error_text(error) << std::endl;
	}
}

TEST("Blue color channel can be extracted from image")
{
	// white pixel
	std::vector<unsigned char> image = { 255, 255, 255, 255 };
	unsigned width = 1, height = 1;
	// red pixel
	std::vector<unsigned char> expected = { 0, 0, 255, 255 };
	ImageFilter::extractColorChannel(blue, image);
	CONFIRM(expected, image);
	image.clear();

	// visual test that saves the result to an image.
	unsigned error = lodepng::decode(image, width, height, "../images/cameraman.png");
	if (error)
	{
		std::cout << "Decode error " << error << ": " << lodepng_error_text(error) << std::endl;
	}
	ImageFilter::extractColorChannel(blue, image);
	error = lodepng::encode("cameraman_blue_channel.png", image, width, height);
	if (error)
	{
		std::cout << "Encode error " << error << ": " << lodepng_error_text(error) << std::endl;
	}
}

// Might not be necessary to test, but this kind of test should pass so it is kept
TEST("Color channel extraction works on different image shapes")
{
	// small square image
	std::vector<unsigned char> image = { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 };
	std::vector<unsigned char> expected = { 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255 };
	unsigned height = 2, width = 2;
	ImageFilter::extractColorChannel(blue, image);
	CONFIRM(expected, image);

	// small rectangle
	image = { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 };
	expected = { 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255 };
	height = 2, width = 3;
	ImageFilter::extractColorChannel(blue, image);
	CONFIRM(expected, image);

	// small rectangle
	image = { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 };
	expected = { 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255 };
	height = 3, width = 2;
	ImageFilter::extractColorChannel(blue, image);
	CONFIRM(expected, image);
}

TEST("Padding of 0s can be added to pixel")
{
	std::vector<unsigned char> image = { 255, 255, 255, 255 };
	unsigned width = 1, height = 1, filterSize = 3;
	std::vector<unsigned char> expected = { 0,0,0,0,      0,0,0,0,       0,0,0,0,
										    0,0,0,0, 255, 255, 255, 255, 0,0,0,0,
											0,0,0,0,      0,0,0,0,       0,0,0,0};
	std::vector<unsigned char> paddedImage = ImageFilter::zeroPadded(image, width, height, filterSize);
	CONFIRM(expected, paddedImage);

	filterSize = 5;
	expected = { 0,0,0,0, 0,0,0,0,      0,0,0,0,       0,0,0,0, 0,0,0,0,
				 0,0,0,0, 0,0,0,0,      0,0,0,0,       0,0,0,0, 0,0,0,0,
				 0,0,0,0, 0,0,0,0, 255, 255, 255, 255, 0,0,0,0, 0,0,0,0,
				 0,0,0,0, 0,0,0,0,      0,0,0,0,       0,0,0,0, 0,0,0,0,
				 0,0,0,0, 0,0,0,0,      0,0,0,0,       0,0,0,0, 0,0,0,0};
	paddedImage = ImageFilter::zeroPadded(image, width, height, filterSize);
	CONFIRM(expected, paddedImage);
}

TEST("Padding of 0s can be added to images with different shapes")
{
	// small square image
	std::vector<unsigned char> image = { 255, 255, 255, 255, 255, 255, 255, 255,
										 255, 255, 255, 255, 255, 255, 255, 255 };
	std::vector<unsigned char> expected = { 0,0,0,0,          0,0,0,0,         0,0,0,0,				0,0,0,0,
											0,0,0,0,	255, 255, 255, 255, 255, 255, 255, 255,		0,0,0,0,
											0,0,0,0,	255, 255, 255, 255, 255, 255, 255, 255,		0,0,0,0,
											0,0,0,0,		  0,0,0,0,			0,0,0,0,			0,0,0,0};
	unsigned height = 2, width = 2, filterSize = 3;
	std::vector<unsigned char> paddedImage = ImageFilter::zeroPadded(image, width, height, filterSize);
	CONFIRM(expected, paddedImage);

	// small rectangle
	image = { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
			  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 };
	expected = {0,0,0,0, 0,0,0,0,				0,0,0,0,		0,0,0,0,			0,0,0,0,			0,0,0,0, 0,0,0,0,
				0,0,0,0, 0,0,0,0,				0,0,0,0,		0,0,0,0,			0,0,0,0,			0,0,0,0, 0,0,0,0,
				0,0,0,0, 0,0,0,0,		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,		0,0,0,0, 0,0,0,0,
				0,0,0,0, 0,0,0,0,		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,		0,0,0,0, 0,0,0,0,
				0,0,0,0, 0,0,0,0,				0,0,0,0,		0,0,0,0,			0,0,0,0,			0,0,0,0, 0,0,0,0,
				0,0,0,0, 0,0,0,0,				0,0,0,0,		0,0,0,0,			0,0,0,0,			0,0,0,0, 0,0,0,0};
	height = 2, width = 3, filterSize = 5;
	paddedImage = ImageFilter::zeroPadded(image, width, height, filterSize);
	CONFIRM(expected, paddedImage);

	// small rectangle
	image = { 255, 255, 255, 255, 255, 255, 255, 255,
			  255, 255, 255, 255, 255, 255, 255, 255,
			  255, 255, 255, 255, 255, 255, 255, 255 };
	expected = {0,0,0,0, 0,0,0,0,				0,0,0,0,		0,0,0,0,			0,0,0,0, 0,0,0,0,
				0,0,0,0, 0,0,0,0,				0,0,0,0,		0,0,0,0,			0,0,0,0, 0,0,0,0,
				0,0,0,0, 0,0,0,0,		255, 255, 255, 255, 255, 255, 255, 255,		0,0,0,0, 0,0,0,0,
				0,0,0,0, 0,0,0,0,		255, 255, 255, 255, 255, 255, 255, 255,		0,0,0,0, 0,0,0,0,
				0,0,0,0, 0,0,0,0,		255, 255, 255, 255, 255, 255, 255, 255,		0,0,0,0, 0,0,0,0,
				0,0,0,0, 0,0,0,0,				0,0,0,0,		0,0,0,0,			0,0,0,0, 0,0,0,0,
				0,0,0,0, 0,0,0,0,				0,0,0,0,		0,0,0,0,			0,0,0,0, 0,0,0,0};
	height = 3, width = 2;
	paddedImage = ImageFilter::zeroPadded(image, width, height, filterSize);
	CONFIRM(expected, paddedImage);

	// visual test
	image.clear();
	filterSize = 101; // make sure that padding is visible in the resulting image
	unsigned error = lodepng::decode(image, width, height, "../images/cameraman.png");
	if (error)
	{
		std::cout << "Decode error " << error << ": " << lodepng_error_text(error) << std::endl;
	}
	paddedImage = ImageFilter::zeroPadded(image, width, height, filterSize);
	error = lodepng::encode("cameraman_padded_with_transparent_pixels.png", paddedImage, width + filterSize / 2 * 2, height + filterSize / 2 * 2);
	if (error)
	{
		std::cout << "Encode error " << error << ": " << lodepng_error_text(error) << std::endl;
	}
}

TEST("Replication padding can be added to pixel")
{
	std::vector<unsigned char> image = { 1,1,1,1 };
	unsigned width = 1, height = 1, filterSize = 3;
	std::vector<unsigned char> expected = { 1,1,1,1, 1,1,1,1, 1,1,1,1,
											1,1,1,1, 1,1,1,1, 1,1,1,1,
											1,1,1,1, 1,1,1,1, 1,1,1,1 };
	std::vector<unsigned char> paddedImage = ImageFilter::replicationPadded(image, width, height, filterSize);
	CONFIRM(expected, paddedImage);

	filterSize = 5;
	expected = { 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,
				 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,
				 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,
				 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,
				 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1 };
	paddedImage = ImageFilter::replicationPadded(image, width, height, filterSize);
	CONFIRM(expected, paddedImage);
}

TEST("Replication padding can be added to image")
{
	// 2 pixels
	std::vector<unsigned char> image = { 1,1,1,1, 2,2,2,2 };
	unsigned width = 2, height = 1, filterSize = 3;
	std::vector<unsigned char> expected = { 1,1,1,1, 1,1,1,1, 2,2,2,2, 2,2,2,2,
											1,1,1,1, 1,1,1,1, 2,2,2,2, 2,2,2,2,
											1,1,1,1, 1,1,1,1, 2,2,2,2, 2,2,2,2 };
	std::vector<unsigned char> paddedImage = ImageFilter::replicationPadded(image, width, height, filterSize);
	CONFIRM(expected, paddedImage);

	// small rectangle
	image = { 1,1,1,1, 2,2,2,2, 3,3,3,3,
			  4,4,4,4, 5,5,5,5, 6,6,6,6 };
	expected = { 1,1,1,1, 1,1,1,1, 2,2,2,2, 3,3,3,3, 3,3,3,3,
				 1,1,1,1, 1,1,1,1, 2,2,2,2, 3,3,3,3, 3,3,3,3,
				 4,4,4,4, 4,4,4,4, 5,5,5,5, 6,6,6,6, 6,6,6,6,
				 4,4,4,4, 4,4,4,4, 5,5,5,5, 6,6,6,6, 6,6,6,6 };
	height = 2, width = 3;
	paddedImage = ImageFilter::replicationPadded(image, width, height, filterSize);
	CONFIRM(expected, paddedImage);

	// small rectangle
	image = { 1,1,1,1, 2,2,2,2,
			  3,3,3,3, 4,4,4,4,
			  5,5,5,5, 6,6,6,6 };
	expected = { 1,1,1,1, 1,1,1,1, 2,2,2,2, 2,2,2,2,
		         1,1,1,1, 1,1,1,1, 2,2,2,2, 2,2,2,2,
				 3,3,3,3, 3,3,3,3, 4,4,4,4, 4,4,4,4,
				 5,5,5,5, 5,5,5,5, 6,6,6,6, 6,6,6,6,
				 5,5,5,5, 5,5,5,5, 6,6,6,6, 6,6,6,6 };
	height = 3, width = 2;
	paddedImage = ImageFilter::replicationPadded(image, width, height, filterSize);
	CONFIRM(expected, paddedImage);
}