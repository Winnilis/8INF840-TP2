#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Url.h"

using namespace std;

class Node
{
	int id;
	int out;
	Url url;
	vector<Node*> next;

	// ranking
	int indegree;
	int pagerank;

public:
	Node(int id, int out, string url);
	~Node();

	bool operator==(const Node& other) const;

	int getId() { return id; }
	int getOut() { return out; }
	Url* getUrl() { return &url; }
	vector<Node*>* getNext(){ return &next; }

	// add a new given node as a next node
	// if the node is already in the next list, it isn't added again
	void addNext(Node* newNode);

	string toString();

	// Indegree
	int getIndegree() { return indegree; }
	void increaseIndegree() { indegree++; }

	// Pagerank
	void setPagerank(int val) { pagerank = val; }
	int getPagerank() { return pagerank; }
	void increasePagerank(int val) { pagerank += val; }
};

