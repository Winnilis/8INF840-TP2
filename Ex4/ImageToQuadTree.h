#pragma once
#include "quadtree.h"
#include <Magick++.h>
#include "CustomRGBColor.h"

using namespace Magick;
using namespace std;

class ImageToQuadTree
{
public:
	ImageToQuadTree(string imagePath);
	~ImageToQuadTree();
	//Create a tree with the image in attribute
	void makeTree();
	//Create and save an image from the quadtree in attribute
	void createImageFromTree(string imagePath);
	QuadTree<CustomRGBColor>* getQuadTree();
	//Show the quadtree structure
	void displayQuadTree();

private:
	//array of the color of all the pixels in the image
	CustomRGBColor** image;
	//the quadtree generated from the image (in fact the array of color of all the pixels)
	QuadTree<CustomRGBColor>* quadtree;
	//height of the image
	size_t height;
	//width of the image
	size_t width;
	//Return if we make a QuadNode with this 4 QuadTree, will it be monochrome
	bool isMonochrome(QuadTree<CustomRGBColor>* so, QuadTree<CustomRGBColor>* no, QuadTree<CustomRGBColor>* ne, QuadTree<CustomRGBColor>* se);
	QuadTree<CustomRGBColor>* makeTree(size_t height, size_t width, size_t i, size_t j);
	void createImageFromTree(size_t height, size_t width, size_t i, size_t j, Image* image, QuadTree<CustomRGBColor>* quadTree);
};

