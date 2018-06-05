#pragma once
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Node
{
	int id;
	int out;
	string url;
	vector<Node*> next;

public:
	Node(int id, int out, string url);
	~Node();

	bool operator==(const Node& other) const;

	int getId() { return id; }
	int getOut() { return out; }
	string getUrl() { return url; }
	vector<Node*>* getNext(){ return &next; }

	// add a new given node as a next node
	// if the node is already in the next list, it isn't added again
	void addNext(Node* newNode);

	string toString();
};
