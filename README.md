# ImageProcessing

The main purpose of this project is to practice image processing using C++. I also wanted to try using test driven development in at least one of my projects.

## External libraries and materials

This project uses an external library called "lodepng" by Ivandeve to load files. The original code can be found from [this repository](https://github.com/lvandeve/lodepng) along with its license. I chose this library, because it is very simple to add to projects as only two files need to be added.

The test image used in this project is "[cameraman](https://dome.mit.edu/handle/1721.3/195767)" owned by MIT and has a Creative Commons Attribution Non-Commercial license.

The testing library used in this project is a modified version of the test library created for the "Test Driven Development with C++" book by Abdul Wahid Tanner. [Here is a link to the repository](https://github.com/PacktPublishing/Test-Driven-Development-with-CPP?tab=MIT-1-ov-file) which also includes the license of the software.

## Examples
### Extracting color channels
![red color channel extracted](https://github.com/nelkyt/ImageProcessing/blob/master/TestImageProcessing/cameraman_red_channel.png) ![green color channel extracted](https://github.com/nelkyt/ImageProcessing/blob/master/TestImageProcessing/cameraman_green_channel.png) ![blue color channel extracted](https://github.com/nelkyt/ImageProcessing/blob/master/TestImageProcessing/cameraman_blue_channel.png)
### Median blur
| Kernel size 3 | Kernel size 5 | Kernel size 9 |
|---------------|---------------|---------------|
|![median blur kernel 3](https://github.com/nelkyt/ImageProcessing/blob/master/TestImageProcessing/cameraman_median_blurred_kernel_size_3.png) | ![median blur kernel 5](https://github.com/nelkyt/ImageProcessing/blob/master/TestImageProcessing/cameraman_median_blurred_kernel_size_5.png) | ![median blur kernel 9](https://github.com/nelkyt/ImageProcessing/blob/master/TestImageProcessing/cameraman_median_blurred_kernel_size_9.png) |
