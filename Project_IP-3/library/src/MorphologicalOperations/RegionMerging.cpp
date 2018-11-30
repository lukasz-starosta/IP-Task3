#include "MorphologicalProcesser.h"

void MorphologicalProcesser::performMerging(int seed_x, int seed_y, int threshold)
{
	return;
	/*
	1. Find a random unregioned pixel and assume it as the seed
	2. For every pixel it is connected to perform the following:
		2.1. Check if the pixel fulfills a given predicate
		2.2. If so, add it to the region (color the same way) and do point 2 for this pixel now in the center
		2.3. If not, leave the pixel as unregioned and go back to point 1

	Predicate:
	1. Euclidean distance
	*/
}