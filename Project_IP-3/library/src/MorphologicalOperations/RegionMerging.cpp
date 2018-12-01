#include "MorphologicalProcesser.h"
#include <iostream>
#include <queue>

using namespace std;

void MorphologicalProcesser::performMerging(int seedX, int seedY, int threshold)
{
	imageCopy = image;
	queue<Coordinates> seedPoints;

	seedPoints.push({ seedX, seedY });

	while (!seedPoints.empty())
	{
		Coordinates seedPixel = seedPoints.front();
		seedPoints.pop();
		vector<Coordinates> surroundingPixels = getSurroundingPixels(seedPixel.x, seedPixel.y, seedX, seedY, threshold);
		for (int i = 0; i < surroundingPixels.size(); i++)
		{
			seedPoints.push(surroundingPixels[i]);
		}
	}

	image = imageCopy;
}

//void MorphologicalProcesser::mergePixels(int x, int y, int seed_x, int seed_y, int threshold)
//{
//	for (short int i = x > 1 ? x - 1 : 0; i <= x + 1 && i < width; i++)
//	{
//		for (short int j = y > 1 ? y - 1 : 0; j <= y + 1 && j < height; j++)
//		{
//			if (isInRegion(i, j)) continue;
//
//			if (isPixelWithinThreshold(seed_x, seed_y, i, j, threshold))
//			{
//				colorRed(x, y);
//				mergePixels(i, j, seed_x, seed_y, threshold);
//			}
//		}
//	}
//}

vector<MorphologicalProcesser::Coordinates>  MorphologicalProcesser::getSurroundingPixels(int x, int y, int seedX, int seedY, int threshold)
{
	vector<Coordinates> validPixels;

	for (short int i = x > 1 ? x - 1 : 0; i <= x + 1 && i < width; i++)
	{
		for (short int j = y > 1 ? y - 1 : 0; j <= y + 1 && j < height; j++)
		{
			if (isInRegion(i, j)) continue;

			if (isPixelWithinThreshold(seedX, seedY, i, j, threshold))
			{
				colorRed(x, y);
				validPixels.push_back({ i, j });
			}
		}
	}

	return validPixels;
}

bool MorphologicalProcesser::isInRegion(int x, int y)
{
	bool isRed = imageCopy(x, y, 0) == (unsigned char)255 &&
		imageCopy(x, y, 1) == 0 &&
		imageCopy(x, y, 2) == 0;

	return isRed;
}

bool MorphologicalProcesser::isPixelWithinThreshold(int x1, int y1, int x2, int y2, int threshold)
{
	double distance = getEuclideanDistance(image(x1, y1, 0), image(x1, y1, 1), image(x1, y1, 2), image(x2, y2, 0), image(x2, y2, 1), image(x2, y2, 2));
	return distance <= threshold;
}

double MorphologicalProcesser::getEuclideanDistance(int r1, int g1, int b1, int r2, int b2, int g2)
{
	return sqrt(pow(r2 - r1, 2) + pow(g2 - g1, 2) + pow(b2 - b1, 2));
}

void MorphologicalProcesser::colorRed(int x, int y)
{
	imageCopy(x, y, 0) = (unsigned char)255;
	imageCopy(x, y, 1) = 0;
	imageCopy(x, y, 2) = 0;
}

