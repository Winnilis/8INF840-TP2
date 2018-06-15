#pragma once

#include <string>
#include <vector>

using namespace std;

enum GenerationType
{
	RANDOM, BACKTRACKING
};

enum SolvingMethod
{
	BFS, A_STAR
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

	vector<pair<int, int>> solveMaze(pair<int, int> startingPoint, pair<int, int> endingPoint, SolvingMethod method);

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
