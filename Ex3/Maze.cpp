﻿#include <vector>
#include <algorithm>
#include <ctime>

#include "Maze.h"

Maze::Maze(const Maze& maze)
{
	width = maze.width;
	height = maze.height;

	initializeArray();
	copyArray(maze);
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
		copyArray(maze);
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

void Maze::generateMaze()
{
	vector<pair<int, int>> cellList;
	int directions[4] = { 0b1000, 0b0100, 0b0010, 0b0001 };

	srand((int) time(0));

	int startingHeight = rand() % height;
	int startingWidth = rand() % width;
	cellList.push_back(pair<int, int>(startingHeight, startingWidth));

	bool isExitCreated = false;

	while (!cellList.empty())
	{
		vector<pair<int, int>>::iterator randomCellIterator;

		switch (type)
		{
		case RANDOM:
			randomCellIterator = cellList.begin() + rand() % cellList.size();
			break;
		case BACKTRACKING:
			randomCellIterator = cellList.end() - 1;
			break;
		}

		pair<int, int> position = *randomCellIterator;

		bool hasValidNeighbourBeenFound = false;

		random_shuffle(begin(directions), end(directions));
		for (int direction : directions)
		{
			pair<int, int> newPosition = getNeighbourPosition(position, direction);
			if (newPosition.first >= 0
				&& newPosition.second >= 0
				&& newPosition.first < this->height
				&& newPosition.second < this->width
				&& array[newPosition.first][newPosition.second] == 0b1111)
			{
				hasValidNeighbourBeenFound = true;
				cellList.push_back(newPosition);

				array[position.first][position.second] ^= direction;
				array[newPosition.first][newPosition.second] ^= getOppositeDirection(direction);

				break;
			}
			else if (!isExitCreated
				&& (newPosition.first < 0
					|| newPosition.second < 0
					|| newPosition.first >= this->height
					|| newPosition.second >= this->width))
			{
				isExitCreated = true;
				hasValidNeighbourBeenFound = true;
				array[position.first][position.second] ^= direction;
			}
		}

		if (!hasValidNeighbourBeenFound)
		{
			cellList.erase(randomCellIterator);
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

void Maze::copyArray(const Maze& maze)
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

pair<int, int> Maze::getNeighbourPosition(pair<int, int> position, int direction)
{
	pair<int, int> newPosition(position);

	switch (direction)
	{
	case 0b1000:
		--newPosition.second;
		break;
	case 0b0100:
		++newPosition.first;
		break;
	case 0b0010:
		++newPosition.second;
		break;
	case 0b0001:
		--newPosition.first;
		break;
	}

	return newPosition;
}

int Maze::getOppositeDirection(int direction)
{
	switch (direction)
	{
	case 0b1000:
		return 0b0010;
	case 0b0100:
		return 0b0001;
	case 0b0010:
		return 0b1000;
	case 0b0001:
		return 0b0100;
	default:
		return -1;
	}
}

int Maze::revertHorizontalBits(int direction)
{
	return (direction & 0b0101) | ((((direction & 0b1010) << 2 | (direction & 0b1010) >> 2) & 0b1111));
}

wostream& operator<<(wostream& stream, const Maze& maze)
{
	for (int i = 0; i < maze.height; ++i)
	{
		for (int j = 0; j < maze.width; ++j)
		{
			stream << maze.array[i][j] << "\t";
		}
		stream << "\n";
	}

	for (int i = 0; i < maze.height + 1; ++i)
	{
		for (int j = 0; j < maze.width + 1; ++j)
		{
			int baseCharacter = 0b0000;

			if (i > 0)
			{
				if (j > 0)
				{
					int tmpValue = Maze::revertHorizontalBits(maze.array[i - 1][j - 1] & 0b0110);
					baseCharacter = baseCharacter | ((tmpValue << 1 | tmpValue >> 3) & 0b1111);
				}

				if (j < maze.width)
				{
					int tmpValue = Maze::revertHorizontalBits(maze.array[i - 1][j] & 0b1100);
					baseCharacter = baseCharacter | ((tmpValue >> 1 | tmpValue << 3) & 0b1111);
				}
			}

			if (i < maze.height)
			{
				if (j > 0)
				{
					int tmpValue = Maze::revertHorizontalBits(maze.array[i][j - 1] & 0b0011);
					baseCharacter = baseCharacter | ((tmpValue >> 1 | tmpValue << 3) & 0b1111);
				}

				if (j < maze.width)
				{
					int tmpValue = Maze::revertHorizontalBits(maze.array[i][j] & 0b1001);
					baseCharacter = baseCharacter | ((tmpValue << 1 | tmpValue >> 3) & 0b1111);
				}
			}

			switch (baseCharacter)
			{
			case 0:
				stream << " ";
				break;
			case 1:
				stream << " ";
				break;
			case 2:
				stream << " ";
				break;
			case 3:
				stream << L"\u2514";
				break;
			case 4:
				stream << " ";
				break;
			case 5:
				stream << L"\u2502";
				break;
			case 6:
				stream << L"\u250C";
				break;
			case 7:
				stream << L"\u251C";
				break;
			case 8:
				stream << " ";
				break;
			case 9:
				stream << L"\u2518";
				break;
			case 10:
				stream << L"\u2500";
				break;
			case 11:
				stream << L"\u2534";
				break;
			case 12:
				stream << L"\u2510";
				break;
			case 13:
				stream << L"\u2524";
				break;
			case 14:
				stream << L"\u252C";
				break;
			case 15:
				stream << L"\u253C";
				break;
			}
		}

		stream << L"\n";
	}

	return stream;
}
