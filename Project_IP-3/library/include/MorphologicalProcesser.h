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

	int structuringElementVariant;

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

public:
	MorphologicalProcesser(std::string imageName, int option, int structuringElementVariant);
	~MorphologicalProcesser();

	void processImage();
};