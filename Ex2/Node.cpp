#include "Node.h"



Node::Node(int _id, int _out, string _url)
{
	this->id = _id;
	this->out = _out;
	Url url(_url);
	this->url = url;
}

Node::~Node(){}

bool Node::operator==(const Node & other) const
{
	if (this->id == other.id)
		return true;
	else
		return false;
}

void Node::addNext(Node* newNode)
{
	for (auto it = this->next.begin(); it != this->next.end(); ++it)
	{
		if ((*it)->getId() == newNode->getId()) // if node already exists then ignore node creation
			return;
	}

	this->next.push_back(newNode);
}

string Node::toString()
{
	string str = to_string(this->id) + " " + to_string(out) + " " + url.toString() + " -->";

	if (!this->next.empty())
	{
		for (auto it = this->next.begin(); it != this->next.end(); ++it)
		{
			str += " ";
			str += to_string((*it)->getId());
		}
	}

	str += " /\n";

	return str;
}
