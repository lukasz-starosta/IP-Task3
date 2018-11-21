#pragma once
#include "Processer.h"
#include <string>

class MorphologicalProcesser : public Processer
{
private:
	enum Options
	{
		dilation = 29, erosion, opening, closing, hmt
	};

	const unsigned char COLOR_BLACK = 0;
	const unsigned char COLOR_WHITE = (unsigned char)255;

	int structuringElementVariant = (int)value;

	// Does not involve the elements from xi up
	const unsigned int basicStructuringElements[10][3][3] = {

		{	{0, 0, 0},
			{0, 1, 1},
			{0, 0, 0}
		},
		{	{0, 0, 0},
			{0, 1, 0},
			{0, 1, 0}
		},
		{	{1, 1, 1},
			{1, 1, 1},
			{1, 1, 1}
		},
		{	{0, 1, 0},
			{1, 1, 1},
			{0, 1, 0}
		},
		{	{0, 0, 0},
			{0, 1, 1},
			{0, 1, 0}
		},
		{	{0, 0, 0},
			{0, 0, 1},
			{0, 1, 0}
		},
		{	{0, 0, 0},
			{1, 1, 1},
			{0, 0, 0}
		},
		{	{0, 0, 0},
			{1, 0, 1},
			{0, 0, 0}
		},
		{	{0, 0, 0},
			{1, 1, 0},
			{1, 0, 0}
		},
		{	{0, 1, 1},
			{0, 1, 0},
			{0, 0, 0}
		}};

	void printBasicStructuringElements();
	void performDilation();
	void performErosion();


	// Methods developed initially with the Window (they produced different results than these, which were presented on the lectures)
	void performDilationWithWindow();
	void performErosionWithWindow();
	struct Window
	{
		short int x0;
		short int x1;
		short int y0;
		short int y1;

		// If the window is at (0,0) we want only some of the pixels taken from the variant - (1, 1), (1, 2), (2, 1), (2, 2). thus the window modifier
		unsigned short int modifier_x;
		unsigned short int modifier_y;

		unsigned short int iterator_x;
		unsigned short int iterator_y;
	};

public:
	MorphologicalProcesser(std::string imageName, int option, int structuringElementVariant);
	~MorphologicalProcesser();

	void processImage();
};