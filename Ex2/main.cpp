#pragma once
#include "Graph.h"
#include "Url.h"
#include <chrono>
#include "Hypergraph.h"
#include "Utils.h"


using namespace std;


int main()
{
	//----------------------------------------------
	//	BUILDING GRAPH (1 node = 1 page)
	//----------------------------------------------
	Graph* graph = new Graph();

	// load nodes
	graph->loadNodes("sante.nodes.txt");

	// load edges
	graph->loadEdges("sante.edges.txt");

	// indegree calc on simple graph
	graph->Indegree();
	graph->PagerankSimple();

	cout << "GRAPH :\n";
	graph->print();

	//----------------------------------------------
	//	BUILDING HYPERGRAPH (1 node = 1 page)
	//----------------------------------------------
	Hypergraph* hypergraph = new Hypergraph();

	// load hypergraph from previous graph
	hypergraph->loadFromGraph(graph);

	//indegree calc
	hypergraph->Indegree();

	// pagerank calc
	hypergraph->PagerankSimple();

	cout << "HYPERGRAPH :\n";
	hypergraph->print();






	//----------------------------------------------
	system("pause");
	return 0;
}