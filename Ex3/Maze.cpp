#include "Maze.h"

Maze::Maze(int height, int width)
{
	this->height = height;
	this->width = width;

	initializeArray();
}

Maze::Maze(const Maze& maze)
{
	width = maze.width;
	height = maze.height;

	initializeArray();
	copyMaze(maze);
}

Maze::~Maze()
{
	eraseArray();
}

const Maze& Maze::operator=(const Maze& maze)
{
	if (this != &maze)
	{
		eraseArray();

		width = maze.width;
		height = maze.height;

		initializeArray();
		copyMaze(maze);
	}

	return *this;
}

void Maze::initializeArray()
{
	array = new int*[height];

	for (int i = 0; i < height; ++i)
	{
		array[i] = new int[width];

		for (int j = 0; j < width; ++j)
		{
			array[i][j] = 0b1111;
		}
	}
}

void Maze::eraseArray()
{
	if (array != 0)
	{
		for (int i = 0; i < height; ++i)
		{
			delete[] array[i];
			array[i] = 0;
		}

		delete[] array;
		array = 0;
	}
}

void Maze::copyMaze(const Maze& maze)
{
	if (this->height == maze.height && this->width == maze.width)
	{
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				this->array[i][j] = maze.array[i][j];
			}
		}
	}
}

