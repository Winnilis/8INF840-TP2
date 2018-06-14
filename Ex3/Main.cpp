#include <iostream>
#include <io.h>
#include <fcntl.h>

#include "Maze.h"

using namespace std;

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
		wcout << "Choice: ";
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
			wcout << "Wrong input! Try again." << endl << endl;
			break;
		}
	}
	while (choice < 1 || choice > 2);

	Maze maze(height, width, generationType);
	wcout << maze;

	cin.get();
	cin.get();
}