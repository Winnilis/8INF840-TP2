#pragma once
#include "Node.h"
#include <fstream>
#include <sstream>
#include <iostream>;
#include <chrono>;
#include <algorithm>

using namespace std;

class Graph
{
	vector<Node*> nodes;

	//init pagerank value of all nodes
	void InitPagerank(int initVal);
	int Pagerank(Node* node);

public:
	Graph();
	~Graph();

	vector<Node*>* getNodes() { return &nodes; }

	// return the number of nodes really added (might be different of the number in the file if nodes are in an incorrect format
	int loadNodes(const char* filepath);

	// return the number of edges added
	int loadEdges(const char* filepath);

	// create a node and add it to the graph
	void addNode(int id, int out, string url);

	// create an edge
	void addEdge(int node1, int node2);

	//add node2 to node1 next list
	void addEdge(Node* node1, Node* node2);
	
	// return true if the node if already in the graph list
	bool exists(Node* node);
	bool exists(int nodeId);

	// return ptr on the node or NULL if the node does not exist
	Node* getNode(int nodeId);

	// return a list of all nodes pointing to n
	vector<Node*>* getInNodes(Node* n);

	// print all nodes of the graph
	void print();

	void Indegree();
	void PagerankSimple();
};

