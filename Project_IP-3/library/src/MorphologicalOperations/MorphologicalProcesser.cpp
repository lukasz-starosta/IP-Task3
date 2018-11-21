#include <MorphologicalProcesser.h>

// Temporary includes
#include <iostream>

using namespace std;

MorphologicalProcesser::MorphologicalProcesser(string imageName, int option, int structuringElementVariant)
	: Processer(imageName, option, structuringElementVariant)
{
}

MorphologicalProcesser::~MorphologicalProcesser()
{
}

// When in doubt whether the basic structuring elements are correct
void MorphologicalProcesser::printBasicStructuringElements()
{
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				cout << basicStructuringElements[i][y][x] << " ";
			}
			cout << endl;
		}

		cout << endl << endl;
	}
}

void MorphologicalProcesser::processImage()
{
	cimg_library::CImg<unsigned char> initialImage;
	try
	{
		initialImage.load(imageName.c_str());
	}
	catch (cimg_library::CImgException)
	{
		cout << endl << "Image could not be loaded. Please check whether the filename is correct." << endl;
		return;
	}

	if (!initialImage) return;
	
	image = initialImage;
	height = image.height();
	width = image.width();

	switch (option)
	{
		case dilation:
			performDilation();
			break;
		case erosion:
			break;
		case opening:
			break;
		case closing:
			break;
		case hmt:
			break;
		default: break;
	}

	image.display("Morphology preview", false);
}