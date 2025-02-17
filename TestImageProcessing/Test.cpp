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

	// small square image
	image = { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 };
	expected = { 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255 };
	height = 2, width = 2;
	ImageFilter::extractColorChannel(red, image);
	CONFIRM(expected, image);

	// small rectangle
	image = { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 };
	expected = { 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255 };
	height = 2, width = 3;
	ImageFilter::extractColorChannel(red, image);
	CONFIRM(expected, image);

	// small rectangle
	image = { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 };
	expected = { 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255 };
	height = 3, width = 2;
	ImageFilter::extractColorChannel(red, image);
	CONFIRM(expected, image);

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

	// small square image
	image = { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 };
	expected = { 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255 };
	height = 2, width = 2;
	ImageFilter::extractColorChannel(green, image);
	CONFIRM(expected, image);

	// small rectangle
	image = { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 };
	expected = { 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255 };
	height = 2, width = 3;
	ImageFilter::extractColorChannel(green, image);
	CONFIRM(expected, image);

	// small rectangle
	image = { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 };
	expected = { 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255 };
	height = 3, width = 2;
	ImageFilter::extractColorChannel(green, image);
	CONFIRM(expected, image);

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

	// small square image
	image = { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 };
	expected = { 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255 };
	height = 2, width = 2;
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