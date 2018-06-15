#include "Utils.h"

using namespace std;



void printNodeList(vector<Node*>* v)
{
	for (auto it = v->begin(); it != v->end(); ++it)
		cout << (*it)->getId() << " ";
}

void printHNodeList(vector<Hypernode*>* v)
{
	for (auto it = v->begin(); it != v->end(); ++it)
		cout << (*it)->getId() << " ";
}
