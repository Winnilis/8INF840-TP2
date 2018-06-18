#include "ImageToQuadTree.h"

ImageToQuadTree::ImageToQuadTree(string imagePath)
{
	Image my_image;
	try {
		// Read a file into image object
		my_image.read(imagePath);
	}
	catch (Exception &error_)
	{
		cout << "Caught exception: " << error_.what() << endl;
	}

	my_image.magick("png");
	my_image.modifyImage();
	//Get width of the image
	width = my_image.columns();
	//Get height of the image
	height = my_image.rows();
	image = new CustomRGBColor*[height];

	//get all the pixels in a area starting at the pixel 0,0, with "width" width and "height" height
	Quantum* pixels = my_image.getPixels(0, 0, width, height);
	for (size_t row = 0; row < height; row++)
	{
		image[row] = new CustomRGBColor[width];
		for (size_t column = 0; column < width; column++)
		{
			//get the color in RGB of the pixel at pos(row, col);
			ColorRGB px = my_image.pixelColor(column, row);
			//fill the array with the color of the pixel
			image[row][column] = CustomRGBColor(px.red(), px.green(), px.blue());
		}
	}
}

ImageToQuadTree::~ImageToQuadTree()
{
}

bool ImageToQuadTree::isMonochrome(QuadTree<CustomRGBColor>* so, QuadTree<CustomRGBColor>* no, QuadTree<CustomRGBColor>* ne, QuadTree<CustomRGBColor>* se)
{
	return (so->isLeaf() && no->isLeaf() && ne->isLeaf() && se->isLeaf() &&
		so->value() == no->value() &&
		so->value() == ne->value() &&
		so->value() == se->value());
}

void ImageToQuadTree::makeTree()
{
	quadtree = makeTree(height, width, 0, 0);
}

void ImageToQuadTree::createImageFromTree(string imagePath)
{
	//we create a new white image format : height x width pixels
	Image image(Geometry(width, height), "white");
	image.type(TrueColorAlphaType);
	image.modifyImage();
	createImageFromTree(height, width, 0, 0, &image, quadtree);
	//save image
	image.write(imagePath);
}

QuadTree<CustomRGBColor>* ImageToQuadTree::getQuadTree()
{
	return quadtree;
}

void ImageToQuadTree::displayQuadTree()
{
	display(quadtree);
}

QuadTree<CustomRGBColor>* ImageToQuadTree::makeTree(size_t height, size_t width, size_t i, size_t j)
{
	//if we have 1 pixel
	if (height == 1	&& width == 1)
	{
		//we create a new leaf with the color of the pixel
		return new QuadLeaf<CustomRGBColor>(image[i][j]);
	}
	size_t halfHeight;
	size_t halfWidth;
	//offsets to manage the case if the height or width is not a multiple of 2
	int offsetH =0;
	int offsetW = 0;
	if (height != 1)
	{
		halfHeight = height / 2;
		if (height % 2 != 0)
		{
			offsetH = 1;
		}
	}
	else 
	{
		halfHeight = height;
	}
	if (width != 1)
	{
		halfWidth = width / 2;
		if (width % 2 != 0)
		{
			offsetW = 1;
		}
	}
	else
	{
		halfWidth = width;
	}
	//create 4 subQuadTree
	QuadTree<CustomRGBColor>* so = makeTree(halfHeight + offsetH, halfWidth, i + halfHeight, j);
	QuadTree<CustomRGBColor>* no = makeTree(halfHeight, halfWidth, i, j);
	QuadTree<CustomRGBColor>* ne = makeTree(halfHeight, halfWidth + offsetW, i, j + halfWidth);
	QuadTree<CustomRGBColor>* se = makeTree(halfHeight + offsetH, halfWidth +offsetW, i + halfHeight, j + halfWidth);

	//the current node is monochrome (ie 4 subquadtree have the same color)
	if (isMonochrome(so, no, ne, se))
	{
		//we create instead a leaf
		return new QuadLeaf<CustomRGBColor>(so->value());
	}
	return new QuadNode<CustomRGBColor>(so, no, ne, se);
}

void ImageToQuadTree::createImageFromTree(size_t height, size_t width, size_t i, size_t j, Image* image, QuadTree<CustomRGBColor>* quadTree)
{
	if (quadTree->isLeaf())
	{
		//get the color of the leaf
		CustomRGBColor colorRGB = quadTree->value();
		double red = colorRGB.getRed();
		double green = colorRGB.getGreen();
		double blue = colorRGB.getBlue();
		//visit all the pixels covered by the leaf
		for (size_t row = i; row < i + height; row++)
		{
			for (size_t col = j; col < j + width; col++)
			{
				ColorRGB px = ColorRGB(red, green, blue);
				//change their color to the color of the leaf
				image->pixelColor(col, row, px);
			}
		}
		//save changes
		image->syncPixels();
		return;
	}
	size_t halfHeight;
	size_t halfWidth;
	//offsets to manage the case if the height or width is not a multiple of 2
	int offsetH = 0;
	int offsetW = 0;
	if (height != 1)
	{
		halfHeight = height / 2;
		if (height % 2 != 0)
		{
			offsetH = 1;
		}
	}
	else
	{
		halfHeight = height;
	}
	if (width != 1)
	{
		halfWidth = width / 2;
		if (width % 2 != 0)
		{
			offsetW = 1;
		}
	}
	else
	{
		halfWidth = width;
	}
	//Generate image from the 4 subQuadTree
	createImageFromTree(halfHeight + offsetH, halfWidth, i + halfHeight, j, image, quadTree->son(0)); //SO
	createImageFromTree(halfHeight, halfWidth, i, j, image, quadTree->son(1)); //NO
	createImageFromTree(halfHeight, halfWidth + offsetW, i, j + halfWidth, image, quadTree->son(2)); //NE
	createImageFromTree(halfHeight + offsetH, halfWidth + offsetW, i + halfHeight, j + halfWidth,image, quadTree->son(3)); //SE
	
}
