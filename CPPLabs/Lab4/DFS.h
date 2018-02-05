#ifndef _GRAPH_SEARCH_H_
#define _GRAPH_SEARCH_H_

#include <functional>
#include <vector>
#include <queue>
#include <typeinfo>

template<	typename NeighboursPolicy,
			typename DoWithEachNode,
			typename NodeType,
			typename MarkPolicy,   
			typename MarkReturn    >
class GraphSearch
{
public:
	//Depth First Search
	static void DFS( NeighboursPolicy getNeighbours,
		  			 DoWithEachNode doSmt,
		 			 NodeType &StartingNode,
		  			 MarkPolicy MarkNode, 
		  			 MarkReturn Marked ) 
	{
		auto NodeArray = getNeighbours(StartingNode);
		MarkNode(StartingNode);
		doSmt( StartingNode );
		for ( auto elem : NodeArray )
		{
			if ( !Marked(*elem) )
			{
				DFS( getNeighbours, doSmt, *elem, MarkNode, Marked );
			}
		}
		return;
	}
	
	static void BFS ( NeighboursPolicy getNeighbours,
		  			  DoWithEachNode doSmt,
		 			  NodeType &StartingNode,
		  			  MarkPolicy MarkNode, 
		  			  MarkReturn Marked ) 
	{
		std::cout << "BFS search : " << std::endl;
		std::queue<NodeType> Q;
		Q.push(StartingNode);
		while ( !Q.empty() )
		{
			NodeType currentNode = Q.front();
			Q.pop();
			MarkNode(currentNode);
			doSmt(currentNode);
			auto neighbours = getNeighbours(currentNode);
			for ( auto elem : neighbours )
			{
				if ( !Marked(*elem) )
				{ 
					Q.push(*elem); 
					MarkNode(*elem);
				}
			}
		}
		return;
	}
};

#endif