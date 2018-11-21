#include "MorphologicalProcesser.h"

void MorphologicalProcesser::performDilation()
{
	cimg_library::CImg<unsigned char> imageCopy = image;

	unsigned short int window_x;
	unsigned short int window_y;

	for (unsigned short int x = 1; x < width - 1; x++)
	{
		for (unsigned short int y = 1; y < height - 1; y++)
		{
			if (image(x, y, 0) != COLOR_BLACK)
			{
				continue;
			}

			for (window_y = 0; window_y < 3; window_y++)
			{
				for (window_x = 0; window_x < 3; window_x++)
				{
					if (basicStructuringElements[structuringElementVariant][window_y][window_x])
					{
						// The -1 is because when we're at (x, y) we consider the window starting from coordinates (x-1, y-1) and ending at coordinates (x+1, y+1)
						short int pixelPosition_x = x - 1 + window_x;
						short int pixelPosition_y = y - 1 + window_y;

						for (unsigned char channel = 0; channel < 3; channel++)
						{
							imageCopy(pixelPosition_x, pixelPosition_y, channel) = COLOR_BLACK;
						}
					}
				}
			}
		}
	}

	image = imageCopy;
}

void MorphologicalProcesser::performErosion()
{
	cimg_library::CImg<unsigned char> imageCopy = image;

	unsigned short int window_x;
	unsigned short int window_y;

	for (unsigned short int x = 1; x < width - 1; x++)
	{
		for (unsigned short int y = 1; y < height - 1; y++)
		{
			bool isFullyContained = true;
			for (window_y = 0; window_y < 3; window_y++)
			{
				for (window_x = 0; window_x < 3; window_x++)
				{
					unsigned char pixelInVariant = basicStructuringElements[structuringElementVariant][window_y][window_x];

					// If the corresponding pixel in variant is black
					if (pixelInVariant)
					{
						// The -1 is because when we're at (x, y) we consider the window starting from coordinates (x-1, y-1) and ending at coordinates (x+1, y+1)
						short int pixelPosition_x = x - 1 + window_x;
						short int pixelPosition_y = y - 1 + window_y;

						if (image(pixelPosition_x, pixelPosition_y, 0) != COLOR_BLACK)
						{
							isFullyContained = false;
						}
					}

					if (!isFullyContained) break;
				}
				if (!isFullyContained) break;
			}
			if (!isFullyContained)
			{
				for (unsigned char channel = 0; channel < 3; channel++)
				{
					imageCopy(x, y, channel) = COLOR_WHITE;
				}
			}
		}
	}

	image = imageCopy;
}

/*
 *This method can be used instead of the simpler dilation - it introduces a window
 */
void MorphologicalProcesser::performDilationWithWindow()
{

	cimg_library::CImg<unsigned char> imageCopy = image;

	Window window;

	for (unsigned short int x = 0; x < width; x++)
	{
		window.x0 = x - 1;
		window.x1 = x + 1;
		window.modifier_x = 0;

		if (window.x0 < 0)
		{
			window.x0 = 0;
			window.modifier_x = 1;
		}
		else if (window.x1 > width - 1)
		{
			window.x1 = width - 1;
		}

		for (unsigned short int y = 0; y < height; y++)
		{

			window.y0 = y - 1;
			window.y1 = y + 1;
			window.modifier_y = 0;

			if (window.y0 < 0)
			{
				window.y0 = 0;
				window.modifier_y = 1;
			}
			else if (window.y1 > height - 1)
			{
				window.y1 = height - 1;
			}

			if (image(x, y, 0) == COLOR_BLACK)
			{
				for (window.iterator_y = 0; window.iterator_y <= window.y1 - window.y0; window.iterator_y++)
				{
					for (window.iterator_x = 0; window.iterator_x <= window.x1 - window.x0; window.iterator_x++)
					{
						if (basicStructuringElements[structuringElementVariant][window.iterator_y + window.modifier_y][window.iterator_x + window.modifier_x])
						{
							short int pixelPosition_x = window.x0 + window.iterator_x;
							short int pixelPosition_y = window.y0 + window.iterator_y;

							for (unsigned char channel = 0; channel < 3; channel++)
							{
								imageCopy(pixelPosition_x, pixelPosition_y, channel) = COLOR_BLACK;
							}
						}
					}
				}
			}
		}
	}

	image = imageCopy;
}

/*
 *This method can be used instead of the simpler erosion - it introduces a window
 */
void MorphologicalProcesser::performErosionWithWindow()
{
	cimg_library::CImg<unsigned char> imageCopy = image;

	Window window;

	for (unsigned short int x = 0; x < width; x++)
	{
		window.x0 = x - 1;
		window.x1 = x + 1;
		window.modifier_x = 0;

		if (window.x0 < 0)
		{
			window.x0 = 0;
			window.modifier_x = 1;
		}
		else if (window.x1 > width - 1)
		{
			window.x1 = width - 1;
		}

		for (unsigned short int y = 0; y < height; y++)
		{

			window.y0 = y - 1;
			window.y1 = y + 1;
			window.modifier_y = 0;

			if (window.y0 < 0)
			{
				window.y0 = 0;
				window.modifier_y = 1;
			}
			else if (window.y1 > height - 1)
			{
				window.y1 = height - 1;
			}

			bool isFullyContained = true;
			for (window.iterator_y = 0; window.iterator_y <= window.y1 - window.y0; window.iterator_y++)
			{
				for (window.iterator_x = 0; window.iterator_x <= window.x1 - window.x0; window.iterator_x++)
				{
					unsigned char pixelInVariant = basicStructuringElements[structuringElementVariant][window.iterator_y + window.modifier_y][window.iterator_x + window.modifier_x];
					// If the corresponding pixel in variant is black
					if (pixelInVariant)
					{
						short int pixelPosition_x = window.x0 + window.iterator_x;
						short int pixelPosition_y = window.y0 + window.iterator_y;

						if (image(pixelPosition_x, pixelPosition_y, 0) != COLOR_BLACK)
						{
							isFullyContained = false;
						}
					}


					if (!isFullyContained) break;
				}
				if (!isFullyContained) break;
			}

			if (!isFullyContained)
			{
				for (unsigned char channel = 0; channel < 3; channel++)
				{
					imageCopy(x, y, channel) = COLOR_WHITE;
				}
			}


		}
	}

	image = imageCopy;
}