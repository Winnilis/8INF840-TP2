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
	string name;

	//pages pointed by the hypernode
	vector<Node*> next;
	//node included in the hypernode
	vector<Node*> elements;

public:
	Hypernode(int id, string name);
	Hypernode(int id, Node* firstNode);
	~Hypernode();

	bool operator==(const Hypernode& other) const;

	int getId() { return id; }
	vector<Node*>* getNext() { return &next; }
	vector<Node*>* getElements() { return &elements; }

	// add a new given node as a next node
	// if the node is already in the next list, it isn't added again
	void addNext(Node* newNode);

	string toString();
};

