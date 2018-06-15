#include "Hypergraph.h"



void Hypergraph::loadHnodes(Graph * graph)
{
	for (auto it = graph->getNodes()->begin(); it != graph->getNodes()->end(); ++it)
	{
		Hypernode* hn = getHnode(*it);

		if (hn == nullptr)
		{
			hn = new Hypernode(nextId++, (*it)->getUrl()->getHost());
			this->hnodes.push_back(hn);
		}

		hn->addElement(*it);
	}
}

void Hypergraph::loadHedges()
{
	for (auto hn = this->hnodes.begin(); hn != this->hnodes.end(); ++hn) //for each hnode in hgraph
		for (auto e = (*hn)->getElements()->begin(); e != (*hn)->getElements()->end(); ++e) //iterating through all elements of hn
			for (auto n = (*e)->getNext()->begin(); n != (*e)->getNext()->end(); ++n) //iterting through each "next" element of e
			{
				Hypernode* hnode = getHnode(*n);
				if (hnode->getId() != (*hn)->getId()) //if hnode of next isn't the current hnode container, then add it to next list
					(*hn)->addNext(hnode);
			}
}

void Hypergraph::InitPagerank(int initVal)
{
	for (auto it = hnodes.begin(); it != hnodes.end(); ++it)
		(*it)->setPagerank(initVal);
}

vector<Hypernode*>* Hypergraph::getInHnode(Hypernode * _hn)
{
	vector<Hypernode*>* result = new vector<Hypernode*>();

	for (auto hn = hnodes.begin(); hn != hnodes.end(); ++hn)
		for (auto next = (*hn)->getNext()->begin(); next != (*hn)->getNext()->end(); ++next)
			if ((*next)->getId() == _hn->getId())
				result->push_back(*hn);

	if (!result->empty())
	{
		sort(result->begin(), result->end());
		result->erase(unique(result->begin(), result->end()), result->end());
	}

	return result;
}

int Hypergraph::Pagerank(Hypernode * hn)
{
	int result = 0;
	vector<Hypernode*>* inNodes = this->getInHnode(hn);

	if (inNodes->empty())
	{
		hn->setPagerank(1);
		return 1;
	}
	else {
		for (auto it = inNodes->begin(); it != inNodes->end(); ++it)
		{
			result += Pagerank(*it);
		}

		hn->setPagerank(result);
		return result;
	}
}

void Hypergraph::PagerankSimple()
{
	// 1. init all pagerank values
	InitPagerank(-1);

	// 2. iterates
	for (auto hn = hnodes.begin(); hn != hnodes.end(); ++hn)
	{
		if ((*hn)->getPagerank() == -1)
			Pagerank(*hn);
	}


	// 3. end of the algo
}

Hypergraph::Hypergraph()
{
	this->nextId = 0;
}

Hypergraph::~Hypergraph()
{
	this->nextId = 0;
	this->hnodes.clear();
}

void Hypergraph::loadFromGraph(Graph* graph)
{
	cout << "Start building hypergraph from graph\n";
	auto start = chrono::high_resolution_clock::now();

	// load all hnodes
	this->loadHnodes(graph);

	// build all hyperedges
	this->loadHedges();

	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> time = end - start;
	cout << "Hypergraph built in " << time.count() << "s\n\n";
}

Hypernode * Hypergraph::getHnode(Node * node)
{
	for (auto it = hnodes.begin(); it != hnodes.end(); ++it)
		if ((*it)->getName() == node->getUrl()->getHost())
			return (*it);

	return nullptr;
}

Hypernode * Hypergraph::getHnode(int id)
{
	for (auto it = hnodes.begin(); it != hnodes.end(); ++it)
		if ((*it)->getId() == id)
			return (*it);

	return nullptr;
}

void Hypergraph::Indegree()
{
	Hypernode* hypern = nullptr;
	cout << "Starting indegree calculation...\n";
	auto start = chrono::high_resolution_clock::now();

	for (auto hn = hnodes.begin(); hn != hnodes.end(); ++hn) //iterating through all hnodes of the hgraph
		for (auto e = (*hn)->getElements()->begin(); e != (*hn)->getElements()->end(); ++e)
			for (auto n = (*e)->getNext()->begin(); n != (*e)->getNext()->end(); ++n) //itarating through the next list of the current hnode
			{
				hypern = getHnode(*n);
				if (hypern != nullptr && (hypern->getId() != (*hn)->getId())) //si le hnoeud auquel appartient l'élément pointé n'est pas l'hypernoeud courant on peut le compter comme arc externe
					hypern->increaseIndegree();

			}

	auto end = chrono::high_resolution_clock::now();
	cout << "End of ingree calculation (" << (end - start).count() << "s)\n\n";
}

void Hypergraph::print()
{
	for (auto it = hnodes.begin(); it != hnodes.end(); ++it)
		cout << (*it)->toString() << "\n";

	cout << "\n";
}
