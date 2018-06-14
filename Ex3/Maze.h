#pragma once
class Maze
{
public:
	Maze(int height, int width);
	Maze(const Maze& maze);
	~Maze();
	const Maze& operator=(const Maze& maze);

private:
	int height;
	int width;

	int** array = 0;

	void initializeArray();
	void eraseArray();
	void copyMaze(const Maze& maze);
};

