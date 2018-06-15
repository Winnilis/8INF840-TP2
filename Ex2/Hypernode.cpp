#include "Hypernode.h"

Hypernode::Hypernode(int _id, string _name)
{
	this->id = _id;
	this->name = _name;
	this->elements = new vector<Node*>();
	this->next = new vector<Hypernode*>();
	this->indegree = 0;
	this->pagerank = 1;
}

Hypernode::~Hypernode()
{
	this->id = -1;
	this->name.clear();
	this->elements->clear();
	this->next->clear();
	this->indegree = 0;
	this->pagerank = 1;
}

void Hypernode::addElement(Node * node)
{
	this->elements->push_back(node);
}

void Hypernode::addNext(Hypernode * hnode)
{
	this->next->push_back(hnode);
}

void Hypernode::increaseIndegree()
{
	indegree++;
}

string Hypernode::toString()
{
	string result = to_string(this->id) + " " + this->name + " (" + to_string(this->elements->size()) + " elements :";

	for (auto e = this->elements->begin(); e != this->elements->end(); ++e)
	{
		result += " ";
		result += to_string((*e)->getId());
	}

	result += ") -->";

	for (auto n = this->next->begin(); n != this->next->end(); ++n)
	{
		result += " ";
		result += to_string((*n)->getId());
	}

	result += (" \t/  \t IN=" + to_string(indegree) + "\t PR=" + to_string(pagerank));

	return result;
}
