#pragma once
#include <vector>
#include "Hypernode.h"
#include "Graph.h"
#include <algorithm>

using namespace std;

class Hypergraph
{
	int nextId;
	vector<Hypernode*> hnodes;

	// build hnodes from an existing graph
	void loadHnodes(Graph* graph);

	// build hedges from existing hnodes
	void loadHedges();

	//init pagerank value of all nodes
	void InitPagerank(int initVal);
	int Pagerank(Hypernode* hn);

public:
	Hypergraph();
	~Hypergraph();

	void loadFromGraph(Graph* graph);

	Hypernode* getHnode(Node* node);
	Hypernode* getHnode(int id);

	void Indegree();
	void PagerankSimple();
	
	vector<Hypernode*>* getInHnode(Hypernode* hn);


	void print();
};

