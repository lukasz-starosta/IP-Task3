#include "MorphologicalProcesser.h"

void MorphologicalProcesser::performDilation()
{
	struct Window
	{
		short int x0;
		short int x1;
		short int y0;
		short int y1;
	};

	Window window;

	for (unsigned short int x = 0; x < width; x++)
	{
		window.x0 = x - 1;
		window.x1 = x + 1;

		if (window.x0 < 0)
		{
			window.x0 = 0;
		}
		else if (window.x1 > width - 1)
		{
			window.x1 = width - 1;
		}

		for (unsigned short int y = 0; y < height; y++)
		{
			window.y0 = y - 1;
			window.y1 = y + 1;
			if (window.y0 < 0)
			{
				window.y0 = 0;
			}
			else if (window.y1 > height - 1)
			{
				window.y1 = height - 1;
			}

			for (short i = window.x0; i <= window.x1; i++)
			{
				for (short j = window.y0; j <= window.y1; j++)
				{
					//implement the logic of dilation here
					for (unsigned char channel = 0; channel < 3; channel++)
					{
						image(i, j, channel) = 255;
					}

				}
			}
		}
	}
}