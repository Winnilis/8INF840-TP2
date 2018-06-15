#pragma once
#include "Graph.h"
#include "Url.h"

int main()
{
	Graph* graph = new Graph();

	graph->loadNodes("test.nodes.txt");
	graph->loadEdges("test.edges.txt");
	//graph->print();

	//

	//----------------------------------------------
	system("pause");
	return 0;
}