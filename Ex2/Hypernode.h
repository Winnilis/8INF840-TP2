#pragma once
#include <string>
#include <vector>
#include "Url.h"
#include "Node.h"

using namespace std;

enum granulation { page, domain, host };

class Hypernode
{
	int id;
	int indegree;
	int pagerank;

	string name;

	//node included in the hypernode
	vector<Node*>* elements;

	vector<Hypernode*>* next;


public:
	Hypernode(int id, string name);
	~Hypernode();

	int getId() { return id; }
	int getIndegree() { return indegree; }

	string getName() { return name; }
	vector<Node*>* getElements() { return elements; }
	vector<Hypernode*>* getNext() { return next; }

	// add node to the element list and its next list to the hnode list
	void addElement(Node* node);

	// if node isn't in next list yet, add it
	void addNext(Hypernode* hnode);

	void increaseIndegree();

	string toString();

	// Pagerank
	void setPagerank(int val) { pagerank = val; }
	int getPagerank() { return pagerank; }
	void increasePagerank(int val) { pagerank += val; }
};

