#include "Hypernode.h"



Hypernode::Hypernode(string _name)
{
	this->name = _name;
}

Hypernode::~Hypernode(){}

bool Hypernode::operator==(const Hypernode & other) const
{
	if (this->id == other.id)
		return true;
	else
		return false;
}

void Hypernode::addNext(Node* newNode)
{
	for (auto it = this->next.begin(); it != this->next.end(); ++it)
		if ((*it) == newNode) // if node already exists then ignore node creation
			return;

	this->next.push_back(newNode);
}

string Hypernode::toString()
{
	return string(to_string(id) + " " + name);
}
