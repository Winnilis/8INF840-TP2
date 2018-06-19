#pragma once

#include <iostream>
#include <cassert>
#include <stack>
#include <initializer_list>

// a k-d tree containing objets of type T and of dimension K
// K is assumed to be strictly positive
template <typename T, unsigned int K>
class KdTree
{

	// STRUCTRURES

public:

	class KdData
	{
	public:
		KdData(const T data[K]);
		KdData(std::initializer_list<const T> data);
		KdData(const KdData& src);
		~KdData();

		// return the i-th componant of the data
		// undefined behaviour if i >= K
		const T& operator[](unsigned int i) const;

		bool operator=(const KdData& other) const;

		bool operator==(const KdData& other) const;

		// OSTREAM OVERLOAD

		friend std::ostream& operator<<(std::ostream& os, const KdData& kdData)
		{
			os << '{';
			for (int i = 0; i < K - 1; ++i)
			{
				os << kdData[i];
				os << ';';
			}
			os << kdData[K - 1] << '}';
			return os;
		}

	private:
		T * data;
	};


private:

	struct KdNode
	{
		KdNode(const KdData& data);
		~KdNode() = default;

		KdData data;

		// leftChild[discriminant] <= data[discriminant]
		KdNode* leftChild;

		// rightChild[discriminant] > data[discriminant]
		KdNode* rightChild;
	};

	// CONSTRUCTOR / DESTRUCTOR

public:

	// 
	KdTree();
	~KdTree();

	// OPERATIONS

public:

	// return weather a value exists or not
	bool find(const KdData& value) const;

	// find the nearest value
	// undifined behavior if the tree is empty
	KdData nearest(const KdData& value) const;

	bool isEmpty() const;

	// insert a value if it doesn't exist already
	bool insert(const KdData& value);

	// remove a value
	// return true if the value cound be found
	bool remove(const KdData& value);

	friend std::ostream & operator<<(std::ostream & os, const KdTree<T, K>& kdTree)
	{
		struct StackElem
		{
			unsigned int level;
			typename KdTree<T, K>::KdNode* node;
		};

		if (!kdTree.isEmpty())
		{
			std::stack<StackElem> stack;
			stack.push({ 0, kdTree.root });

			while (!stack.empty())
			{
				StackElem elem = stack.top();
				stack.pop();

				if (elem.level > 0)
				{
					for (int i = 0; i < elem.level-1; ++i)
					{
						os << "   ";
					}
					os << "|__";
				}

				if (elem.node != 0)
				{
					stack.push({ elem.level + 1, elem.node->rightChild });
					stack.push({ elem.level + 1, elem.node->leftChild });

					os << elem.node->data;
				}

				os << std::endl;
			}
		}
		return os;
	}

private:

	struct SearchResult
	{
		KdNode* node;
		KdNode* parent;
	};

	// find the node with the given value
	// return 0 if no such node exists
	SearchResult _find(const KdData& value) const;

	// find the nearest node to the given value
	// return 0 if the tree is empty
	KdNode* _nearest(const KdData& value) const;

	// return the discriminant of a given level
	// (level mod K)
	static unsigned int discriminant(unsigned int level);

	// return the signed distance between a and b in the discriminant dimension
	// (positive if a > b, negative if a < b, 0 otherwise)
	static T compare(const KdData& a, const KdData& b, unsigned int discriminant);

	// return the squared distance between datas
	static T distance2(const KdData& a, const KdData& b);

	// FIELDS

private:
	KdNode * root;
};

template<typename T, unsigned int K>
KdTree<T, K>::KdData::KdData(const T data[K])
{
	this->data = new T[K];
	for (int i = 0; i < K; ++i)
	{
		this->data[i] = data[i];
	}
}

template<typename T, unsigned int K>
KdTree<T, K>::KdData::KdData(std::initializer_list<const T> data)
{
	if (data.size() != K)
	{
		throw "KdTree::KdData : incorrect array size";
	}

	this->data = new T[K];

	int i = 0;
	for (T d : data)
	{
		this->data[i] = d;
		++i;
	}
}

template<typename T, unsigned int K>
KdTree<T, K>::KdData::KdData(const KdData & src) :
	KdData(src.data)
{}
	

template<typename T, unsigned int K>
KdTree<T, K>::KdData::~KdData()
{
	delete[] data;
}

template<typename T, unsigned int K>
inline const T & KdTree<T, K>::KdData::operator[](unsigned int i) const
{
	assert(i < K);
	return data[i];
}

template<typename T, unsigned int K>
bool KdTree<T, K>::KdData::operator=(const KdData & other) const
{
	for (int i = 0; i < K; ++i)
	{
		if (data[i] != other[i])
		{
			return false;
		}
	}
	return true;
}

template<typename T, unsigned int K>
bool KdTree<T, K>::KdData::operator==(const KdData & other) const
{
	for (int i = 0; i < K; ++i)
	{
		if (data[i] != other[i])
		{
			return false;
		}
	}
	return true;
}

template<typename T, unsigned int K>
KdTree<T, K>::KdNode::KdNode(const KdData & data) :
	data(data),
	leftChild(0),
	rightChild(0)
{}

template<typename T, unsigned int K>
KdTree<T, K>::KdTree() :
	root(0)
{
	if (K == 0)
	{
		throw "KdTree : K must be strictly positive";
	}
}

template<typename T, unsigned int K>
KdTree<T, K>::~KdTree()
{
	std::stack<KdNode*> stack;
	stack.push(root);

	while (!stack.empty())
	{
		KdNode* curr = stack.top();
		stack.pop();

		if (curr != 0)
		{
			stack.push(curr->leftChild);
			stack.push(curr->rightChild);
			delete curr;
		}
	}
}

template<typename T, unsigned int K>
bool KdTree<T, K>::find(const KdData & value) const
{
	return _find(value).node != 0;
}

template<typename T, unsigned int K>
typename KdTree<T, K>::KdData KdTree<T, K>::nearest(const KdData & value) const
{
	assert(!isEmpty());
	return _nearest(value)->data;
}

template<typename T, unsigned int K>
inline bool KdTree<T, K>::isEmpty() const
{
	return root == 0;
}

template<typename T, unsigned int K>
bool KdTree<T, K>::insert(const KdData & value)
{
	if (isEmpty())
	{
		root = new KdNode(value);
		return true;
	}
	else
	{
		KdNode* curr = root;
		unsigned int level = 0;

		while (curr != 0)
		{
			if (curr->data == value)
			{
				// the value already exist
				curr = 0;
				return false;
			}
			else
			{
				T comparison = compare(curr->data, value, discriminant(level));
				if (comparison >= 0)
				{
					// the value to insert is in the left subtree
					if (curr->leftChild != 0)
					{
						curr = curr->leftChild;
					}
					else
					{
						curr->leftChild = new KdNode(value);
						curr = 0;
						return true;
					}
				}
				else
				{
					// the value to insert is in the left subtree
					if (curr->rightChild != 0)
					{
						curr = curr->rightChild;
					}
					else
					{
						curr->rightChild = new KdNode(value);
						curr = 0;
						return true;
					}
				} 
			}
			level++;
		}
	}

	// this should never happen
	return false;
}

template<typename T, unsigned int K>
bool KdTree<T, K>::remove(const KdData & value)
{
	SearchResult search = _find(value);
	if (search.node == 0)
	{
		return false;
	}
	else
	{
		// disconnect nodes from tree to reinsert them after
		if (search.parent != 0)
		{
			if (search.parent->leftChild == search.node)
			{
				search.parent->leftChild = 0;
			}
			else
			{
				search.parent->rightChild = 0;
			}
		}
		else
		{
			root = 0;
		}

		std::stack<KdNode*> stack;
		stack.push(search.node->leftChild);
		stack.push(search.node->rightChild);
		delete search.node;

		while (!stack.empty())
		{
			KdNode* node = stack.top();
			stack.pop();

			if (node != 0)
			{
				//reinsert node
				insert(node->data);

				stack.push(node->leftChild);
				stack.push(node->rightChild);

				delete node;
			}
		}

		return true;
	}
}

template<typename T, unsigned int K>
typename KdTree<T, K>::SearchResult KdTree<T, K>::_find(const KdData & value) const
{
	KdNode* parent = 0;
	KdNode* curr = root;
	int level = 0;

	while (curr != 0 && !(curr->data == value))
	{
		T comparison = compare(curr->data, value, discriminant(level));

		if (comparison >= 0)
		{
			parent = curr;
			curr = curr->leftChild;
		}
		else if (comparison < 0)
		{
			parent = curr;
			curr = curr->rightChild;
		}

		++level;
	}

	return { curr, parent };
}

template<typename T, unsigned int K>
typename KdTree<T, K>::KdNode * KdTree<T, K>::_nearest(const KdData & value) const
{
	struct StackElem
	{
		KdNode* node;
		int level;
	};

	if (isEmpty())
	{
		// no element
		return 0;
	}
	else
	{
		KdNode* nearest = root;
		T nearestDist2 = distance2(root->data, value);

		std::stack<StackElem> stack;
		stack.push({root, 0});

		while (!stack.empty())
		{
			StackElem elem = stack.top();
			stack.pop();

			if (elem.node != 0)
			{
				// check distance squared

				T dist2 = distance2(elem.node->data, value);
				if (dist2 < nearestDist2)
				{
					nearest = elem.node;
					nearestDist2 = dist2;
				}

				// push potential nearest childrens

				T distAlongDiscriminant = compare(elem.node->data, value, discriminant(elem.level));
				if (pow(distAlongDiscriminant, 2) >= nearestDist2)
				{
					// only one potential nearer child
					if (distAlongDiscriminant > 0)
					{
						stack.push({ elem.node->leftChild, elem.level + 1 });
					}
					else
					{
						stack.push({ elem.node->rightChild, elem.level + 1 });
					}
				}
				else
				{
					// both children are potentially nearer
					stack.push({ elem.node->leftChild, elem.level + 1 });
					stack.push({ elem.node->rightChild, elem.level + 1 });
				}
			}

		}
		return nearest;
	}
}

template<typename T, unsigned int K>
unsigned int KdTree<T, K>::discriminant(unsigned int level)
{
	return level % K;
}

template<typename T, unsigned int K>
inline T KdTree<T, K>::compare(const KdData & a, const KdData & b, unsigned int discriminant)
{
	return a[discriminant] - b[discriminant];
}

template<typename T, unsigned int K>
T KdTree<T, K>::distance2(const KdData & a, const KdData & b)
{
	T sum = 0;
	for (int i = 0; i < K; ++i)
	{
		sum += pow(compare(a, b, i), 2);
	}
	return sum;
}

