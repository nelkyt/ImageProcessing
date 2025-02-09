#include "../libs/lodepng.h"
#include <MereTDD/Test.h>
#include "../ImageProcessing/ImageFilter.h"


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