#include "Graph.h"



void Graph::InitPagerank(int initVal)
{
	for (auto it = nodes.begin(); it != nodes.end(); ++it)
		(*it)->setPagerank(initVal);
}

int Graph::Pagerank(Node * n)
{
	int result = 0;
	vector<Node*>* inNodes = this->getInNodes(n);

	if (inNodes->empty())
	{
		n->setPagerank(1);
		return 1;
	}
	else {
		for (auto it = inNodes->begin(); it != inNodes->end(); ++it)
		{
			result += Pagerank(*it);
		}

		n->setPagerank(result);
		return result;
	}
}

Graph::Graph(){}

Graph::~Graph(){
	this->nodes.clear();
}

int Graph::loadNodes(const char * filepath)
{
	ifstream f;
	f.open(filepath);

	int size, count=0;
	string line, idstr, outstr, url;

	getline(f, line); // number of nodes to be loaded
	size = stoi(line);
	cout << size << " nodes to be loaded\nLoading...\n";

	getline(f, line); //head of the table

	auto startParsing = chrono::high_resolution_clock::now();
	while (!f.eof())
	{
		line.clear();
		idstr.clear();
		outstr.clear();
		url.clear();

		getline(f, line);

		stringstream ss(line);
		getline(ss, idstr, ' ');
		getline(ss, outstr, ' ');
		getline(ss, url);

		//cout << "[" << idstr << "][" << outstr << "][" << url << "]\n";
		if (!idstr.empty()) {
			this->addNode(stoi(idstr), stoi(outstr), url);
			count++;
		}
	}
	auto endParsing = chrono::high_resolution_clock::now();

	f.close();

	if (size != count)
		cout << "WARNING : the number of nodes loaded is different than the number of nodes specified in the file ! (nodes might have been saved in an incorrect format ; check your file)\n";

	chrono::duration<double> execTime = endParsing - startParsing;
	cout << count << " nodes loaded in " << execTime.count() << "s\n\n";

	return count;
}

int Graph::loadEdges(const char * filepath)
{
	ifstream f;
	f.open(filepath);

	string line;
	int size, count=0, node1, node2;

	getline(f, line); // number of edges to be loaded
	size = stoi(line);
	cout << size << " edges to be loaded\nLoading...\n";

	getline(f, line); //head of the table

	auto startParsing = chrono::high_resolution_clock::now();
	while (!f.eof())
	{
		node1 = -1; 
		node2 = -1; 

		f >> node1;
		f >> node2;

		if (node1 != -1 && node2 != -1)
		{
			this->addEdge(node1, node2);
			count++;
		}
	}
	auto endParsing = chrono::high_resolution_clock::now();

	f.close();

	if (size != count)
		cout << "WARNING : the number of nodes loaded is different than the number of nodes specified in the file ! (edges might have been saved in an incorrect format ; check your file)\n";

	chrono::duration<double> execTime = endParsing - startParsing;
	cout << count << " edges loaded in " << execTime.count() << "s\n\n";

	return count;
}

void Graph::addNode(int id, int out, string url)
{
	Node* node = new Node(id, out, url);

	this->nodes.push_back(node);
}

void Graph::addEdge(int node1, int node2)
{
	Node* n1 = getNode(node1);
	if (n1 == nullptr)
	{
		cout << "WARNING : " << node1 << "does not exist. Unable to create edge (" << node1 << "," << node2 << "\n";
		return;
	}

	Node* n2 = getNode(node2);
	if (n2 == nullptr)
	{
		cout << "WARNING : " << node2 << "does not exist. Unable to create edge (" << node1 << "," << node2 << "\n";
		return;
	}

	n1->addNext(n2);
}

void Graph::addEdge(Node * node1, Node * node2)
{
	if (node1 != nullptr && node2 != nullptr)
		node1->addNext(node2);
}


bool Graph::exists(Node* node)
{
	for (auto it = nodes.begin(); it != nodes.end(); ++it)
		if ((*it)->getId() == node->getId())
			return true;

	return false;
}

bool Graph::exists(int nodeId)
{
	for (auto it = nodes.begin(); it != nodes.end(); ++it)
		if ((*it)->getId() == nodeId)
			return true;

	return false;
}

Node * Graph::getNode(int nodeId)
{	
	for (auto it = nodes.begin(); it != nodes.end(); ++it)
	{
		if ((*it)->getId() == nodeId)
			return (*it);
	}

	return nullptr;
}

vector<Node*>* Graph::getInNodes(Node * n)
{
	vector<Node*>* result = new vector<Node*>();
	
	for (auto node = nodes.begin(); node != nodes.end(); ++node)
		for (auto next = (*node)->getNext()->begin(); next != (*node)->getNext()->end(); ++next)
			if ((*next)->getId() == n->getId())
				result->push_back(*node);
	
	if (!result->empty())
	{
		sort(result->begin(), result->end());
		result->erase(unique(result->begin(), result->end()), result->end());
	}

	return result;
}

void Graph::print()
{
	for (auto it = nodes.begin(); it != nodes.end(); ++it)
		cout << (*it)->toString() << "\n";

	cout << "\n";
}

void Graph::Indegree()
{
	cout << "Starting indegree calculation...\n";
	auto start = chrono::high_resolution_clock::now();

	for (auto node = nodes.begin(); node != nodes.end(); ++node)
		for (auto n = (*node)->getNext()->begin(); n != (*node)->getNext()->end(); ++n)
			(*n)->increaseIndegree();

	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double> time = end - start;
	cout << "Indregree calculation completed in " << time.count() << "s\n\n";
}

void Graph::PagerankSimple()
{
	// 1. init all pagerank values
	InitPagerank(-1);

	// 2. iterates
	for (auto n = nodes.begin(); n != nodes.end(); ++n)
	{
		if ((*n)->getPagerank() == -1)
			Pagerank(*n);
	}


	// 3. end of the algo
}
