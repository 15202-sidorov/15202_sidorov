#include <iostream>

#include "PointerGraph.h"
#include "DFS.h"

int main()
{
	std::vector<Node<int>> init;
	for (int i = 0; i < 10; i++)
	{
		Node<int> node(i);
		init.push_back(node);
	}

	Node<int>::connect(&init[1], &init[5]);
	Node<int>::connect(&init[2], &init[6]);
	Node<int>::connect(&init[6], &init[8]);
	Node<int>::connect(&init[1], &init[6]);
	Node<int>::connect(&init[2], &init[9]);

	//PointerGraph<int> graph(init);
	std::cout << "DFS search : " << std::endl;
	GraphSearch<std::vector<Node<int> *>(const Node<int>&),
				void (const Node<int> &),
				Node<int>,
				void (Node<int>&),
				bool (const Node<int>&) > :: 
	DFS(PointerGraph<int>::getNeighbours,
		PointerGraph<int>::getData,
		init[1],
		PointerGraph<int>::markNode,
		PointerGraph<int>::marked);	

	for (int i = 0; i < 10; i++)
	{
		init[i].mark(false);
	}

	
	GraphSearch<std::vector<Node<int> *>(const Node<int>&),
				void (const Node<int> &),
				Node<int>,
				void (Node<int>&),
				bool (const Node<int>&) > :: 
	BFS(PointerGraph<int>::getNeighbours,
		PointerGraph<int>::getData,
		init[1],
		PointerGraph<int>::markNode,
		PointerGraph<int>::marked);	



	return 0;
}