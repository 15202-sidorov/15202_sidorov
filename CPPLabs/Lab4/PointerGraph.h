#ifndef _POINTER_GRAPH_H_
#define _POINTER_GRAPH_H_

#include <vector>


template< typename Type >
class Node
{
public:
	Node(Type d) : Data(d){};
	Node() = delete;
	void AddNeighbour(Node<Type> *NeighbourNode)
	{
		neighbours.push_back(NeighbourNode);
	}

	Node<Type> *PopNeighbour(){ return neighbours.pop_back(); }

	void setData(Type d){ Data = d; }

	Type getData() const { return Data; }
	
	std::vector<Node<Type> *> getNeighbours() const { return neighbours; }

	bool marked() const { return label; }

	void mark( bool p = true ){ label = p; }

	static void connect(Node<Type>* a, Node<Type>* b)
	{
		a->AddNeighbour(b);
		b->AddNeighbour(a);
		return;
	}

protected:
	std::vector<Node<Type> *> neighbours;
	Type Data;
	bool label = false;
};


template< typename Type >
class PointerGraph
{
public:
	PointerGraph(std::vector<Node<Type>> initArr)
	{
		for (int i = 0; i < initArr.size(); i++)
		{
			NodesArr.push_back(initArr[i]);
		}
	}	

	void unmarkNodes()
	{
		for (Node<Type> elem : NodesArr)
		{
			elem.markNode(false);
		}
	}

	static void markNode(Node<Type> &node) { node.mark(); }

	static std::vector<Node<Type> *> 
		getNeighbours(const Node<Type> &node) { return node.getNeighbours(); }

	static bool marked(const Node<Type> &node) { return node.marked(); } 

	static void getData(const Node<Type> &node) 
		{ std::cout << node.getData() << std::endl; }

private:
	std::vector<Node<Type>> NodesArr;

};

#endif