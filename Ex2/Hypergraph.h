#pragma once
#include <vector>
#include "Hypernode.h"

using namespace std;

class Hypergraph
{
	vector<Hypernode*> hnodes;

public:
	Hypergraph();
	~Hypergraph();
};

