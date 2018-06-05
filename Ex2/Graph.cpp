#include "Graph.h"



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

	getline(f, line); //head of the table

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

	f.close();

	if (size != count)
		cout << "WARNING : the number of nodes loaded is different than the number of nodes specified in the file ! (nodes might have been saved in an incorrect format ; check your file)\n";

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

	getline(f, line); //head of the table

	while (!f.eof())
	{
		node1 = -1; 
		node2 = -1; 

		f >> node1;
		f >> node2;

		if (node1 != -1 && node2 != -1)
		{
			addEdge(node1, node2);
			count++;
		}
	}

	f.close();

	if (size != count)
		cout << "WARNING : the number of nodes loaded is different than the number of nodes specified in the file ! (nodes might have been saved in an incorrect format ; check your file)\n";

	return count;
}

void Graph::addNode(int id, int out, string url)
{
	Node* node = new Node(id, out, url);

	if(!exists(node))
		this->nodes.push_back(node);
}

void Graph::addEdge(int node1, int node2)
{
	if (!exists(node1) || !exists(node2))
		cout << "WARNING : one of the following node does not exist (" << node1 << "," << node2 << "). Unable to create edge.";
	else {
		getNode(node1)->addNext(getNode(node2));
	}
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
	if(!exists(nodeId))
		return nullptr;
	
	for (auto it = nodes.begin(); it != nodes.end(); ++it)
	{
		if ((*it)->getId() == nodeId)
			return (*it);
	}
}

void Graph::print()
{
	for (auto it = nodes.begin(); it != nodes.end(); ++it)
	{
		cout << (*it)->toString();
	}
}
