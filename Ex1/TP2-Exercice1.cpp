#include <cstdlib>

#include "KdTree.h"

using namespace std;

KdTree<int, 2> tree;

void mainMenu();
void createNodeMenu();
void findNodeMenu();
void nearestNodeMenu();
void removeNodeMenu();
typename KdTree<int, 2>::KdData inputValueMenu();

typename KdTree<int, 2>::KdData inputValueMenu()
{
	int value[2];
	cout << "Value[0] = ";
	cin >> value[0];
	cout << "Value[1] = ";
	cin >> value[1];

	return KdTree<int, 2>::KdData(value);
}

void createNodeMenu()
{
	cout << "CREATE NODE----------------------------------" << endl;
	KdTree<int, 2>::KdData value = inputValueMenu();
	bool result = tree.insert(value);
	if (result)
	{
		cout << "Created node " << value << endl;
	}
	else
	{
		cout << value << " already exists" << endl;
	}
	mainMenu();
}

void findNodeMenu()
{
	cout << "FIND NODE------------------------------------" << endl;
	KdTree<int, 2>::KdData value = inputValueMenu();
	bool found = tree.find(value);
	if (found)
	{
		cout << value << " was found" << endl;
	}
	else
	{
		cout << value << " was not found" << endl;
	}
	mainMenu();
}

void nearestNodeMenu()
{
	cout << "NEAR NODE------------------------------------" << endl;
	KdTree<int, 2>::KdData value = inputValueMenu();
	KdTree<int, 2>::KdData result = tree.nearest(value);
	cout << value << " is nearest to " << result << endl;
	mainMenu();
}

void removeNodeMenu()
{
	cout << "REMOVE NODE----------------------------------" << endl;
	KdTree<int, 2>::KdData value = inputValueMenu();
	bool removed = tree.remove(value);
	if (removed)
	{
		cout << value << " was removed" << endl;
	}
	else
	{
		cout << value << " was not found" << endl;
	}
	mainMenu();
}

void mainMenu()
{
	cout << "MAIN MENU------------------------------------" << endl;

	cout << tree;

	cout << "1 -- Create a node" << endl
		<< "2 -- Remove a node" << endl
		<< "3 -- Find a node" << endl
		<< "4 -- Find a node near" << endl
		<< "5 -- Exit" << endl;

	unsigned int i;
	cin >> i;

	while (i < 1 || i > 5)
	{
		cout << "Unknown option" << endl;
		cin >> i;
	}

	switch (i)
	{
	case 1:
		createNodeMenu();
		break;
	case 2:
		removeNodeMenu();
		break;
	case 3:
		findNodeMenu();
		break;
	case 4:
		nearestNodeMenu();
		break;
	default:
		break;
	}
}


int main()
{
	tree.insert({40, 45});
	tree.insert({ 15, 70 });
	tree.insert({ 70, 10 });
	tree.insert({ 69, 50 });
	tree.insert({ 66, 85 });
	tree.insert({ 85, 90 });

	mainMenu();

    return 0;
}