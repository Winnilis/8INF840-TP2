#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <ctime>

#include "Maze.h"

using namespace std;

void printPath(vector<pair<int, int>> path)
{
	wcout << "### Path from start to end ###\n\n";

	wcout << "[" << (*path.begin()).first << " ; " << (*path.begin()).second << "]\n";
	for (vector<pair<int, int>>::iterator it = path.begin() + 1; it != path.end(); ++it)
	{
		wcout << "=> [" << (*it).first << " ; " << (*it).second << "]\n";
	}
	wcout << "\n\n";
}

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);

	int height, width = -1;

	do
	{
		wcout << "### MAZE GENERATION ###\n";
		wcout << " # Height: ";
		cin >> height;

		wcout << " # Width: ";
		cin >> width;

		if (height < 2 || width < 2)
		{
			wcout << " # Wrong dimensions, the maze must be at lease 2x2!\n\n";
		}
	}
	while (height < 2 || width < 2);

	int choice;
	GenerationType generationType;
	do
	{
		wcout << " # Please select a generation type:" << endl;
		wcout << " # | [1] random" << endl;
		wcout << " # | [2] with backtracking" << endl;
		wcout << " # Choice: ";
		cin >> choice;
		wcout << endl;

		switch (choice)
		{
		case 1:
			generationType = RANDOM;
			break;
		case 2:
			generationType = BACKTRACKING;
			break;
		default:
			wcout << " # Wrong input! Try again." << endl << endl;
			break;
		}
	}
	while (choice < 1 || choice > 2);

	Maze maze(height, width, generationType);
	wcout << maze;

	do
	{
		wcout << " # Do you want to select a starting and exit point, or do you want random ones?" << endl;
		wcout << " # | [1] custom" << endl;
		wcout << " # | [2] random" << endl;
		wcout << " # Choice: ";
		cin >> choice;
		wcout << endl;

		if (choice < 1 || choice > 2)
		{
			wcout << " # Wrong input! Try again." << endl << endl;
		}
	} while (choice < 1 || choice > 2);

	pair<int, int> start, end;

	if (choice == 1)
	{
		int tmpHeight, tmpWidth;

		do
		{
			wcout << " # Starting height: ";
			cin >> tmpHeight;

			wcout << " # Starting width: ";
			cin >> tmpWidth;

			start = pair<int, int>(tmpHeight, tmpWidth);

			if (tmpHeight < 0 || tmpHeight >= height || tmpWidth < 0 || tmpWidth >= width)
			{
				wcout << " # Wrong coordinates, they must be inside the maze\n\n";
			}
		}
		while (tmpHeight < 0 || tmpHeight >= height || tmpWidth < 0 || tmpWidth >= width);

		do
		{
			wcout << " # Ending height: ";
			cin >> tmpHeight;

			wcout << " # Ending width: ";
			cin >> tmpWidth;

			end = pair<int, int>(tmpHeight, tmpWidth);

			if (tmpHeight < 0 || tmpHeight >= height || tmpWidth < 0 || tmpWidth >= width)
			{
				wcout << " # Wrong coordinates, they must be inside the maze\n\n";
			}
			else if (start == end)
			{
				wcout << " # Wrong coordinates, they must be different from the starting ones\n\n";
			}

		}
		while (tmpHeight < 0 || tmpHeight >= height || tmpWidth < 0 || tmpWidth >= width || start == end);
	}
	else
	{
		srand((int) time(0));
		start = pair<int, int>(rand() % 10, rand() % 10);
		do
		{
			end = pair<int, int>(rand() % 10, rand() % 10);
		}
		while (end == start);
	}

	wcout << "### Chosen coordinates ###\n";
	wcout << " # Start: [" << start.first << ";" << start.second << "]\n";
	wcout << " # End: [" << end.first << ";" << end.second << "]\n\n";

	cin.get();
	cin.get();

	wcout << "###################\n";
	wcout << "### BFS solving ###\n";
	wcout << "###################\n\n";

	vector<pair<int, int>> bfs_solution = maze.solveMaze(start, end, BFS);

	cin.get();

	printPath(bfs_solution);

	cin.get();

	wcout << "##################\n";
	wcout << "### A* solving ###\n";
	wcout << "##################\n\n";

	vector<pair<int, int>> a_star_solution = maze.solveMaze(start, end, A_STAR);

	cin.get();

	printPath(a_star_solution);

	cin.get();
}