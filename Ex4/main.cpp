#pragma once
#include "ImageToQuadTree.h"

int main(int /*argc*/, char ** argv)
{
	string imageToLoadPath;
	string imageToSavePath;
	// Initialize ImageMagick install location for Windows
	InitializeMagick(*argv);
	cout << "Path of the picture to load : ";
	cin >> imageToLoadPath;
	ImageToQuadTree* image = new ImageToQuadTree(imageToLoadPath);
	image->makeTree();
	//image->displayQuadTree();
	cout << "Path of the picture to save : ";
	cin >> imageToSavePath;
	image->createImageFromTree(imageToSavePath);
	system("pause");
}