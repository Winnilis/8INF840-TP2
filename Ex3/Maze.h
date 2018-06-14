#pragma once

#include <string>

using namespace std;

enum GenerationType
{
	RANDOM, BACKTRACKING
};

class Maze
{
public:
	Maze(int height, int width, GenerationType type)
		: height(height), width(width), type(type)
	{
		initializeArray();
		generateMaze();
	}

	Maze(const Maze& maze);
	~Maze();
	const Maze& operator=(const Maze& maze);

	friend wostream& operator<< (wostream& stream, const Maze& maze);

private:
	int height;
	int width;
	GenerationType type;

	int** array = 0;

	void initializeArray();
	void generateMaze();
	void eraseArray();
	void copyArray(const Maze& maze);

	static pair<int, int> getNeighbourPosition(pair<int, int> position, int direction);
	static int getOppositeDirection(int direction);
	static int revertHorizontalBits(int direction);
};
