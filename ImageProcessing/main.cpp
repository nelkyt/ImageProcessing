#include "../libs/lodepng.h"
#include <iostream>

int main()
{
	// try to use the library in the simplest way possible: load image from file and save the same image to a different file.
	lodepng::State state;
	std::vector<unsigned char> image;
	unsigned width, height;
	unsigned error = lodepng::decode(image, width, height, "../images/cameraman.png");
	if (error)
	{
		std::cout << "Decode error " << error << ": " << lodepng_error_text(error) << std::endl;
	}
	else
	{
		std::cout << "Image loaded successfully! " << "width: " << width << " height: " << height << std::endl;
	}
	error = lodepng::encode("cameraman_copy.png", image, width, height);
	if (error)
	{
		std::cout << "Encode error " << error << ": " << lodepng_error_text(error) << std::endl;
	}
	else
	{
		std::cout << "Image encoded successfully!" << std::endl;
	}
}