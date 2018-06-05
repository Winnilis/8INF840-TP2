#pragma once
#include "Node.h"
#include <fstream>
#include <sstream>
#include <iostream>;

using namespace std;

class Graph
{
	vector<Node*> nodes;

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

	// return true if the node if already in the graph list
	bool exists(Node* node);
	bool exists(int nodeId);

	// return ptr on the node or NULL if the node does not exist
	Node* getNode(int nodeId);

	// print all nodes of the graph
	void print();
};

