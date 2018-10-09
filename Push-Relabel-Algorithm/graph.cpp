#include "graph.h"

/*	Graph Feature:
	- s is source node, no edge from v to s
	- t is destination node, no edge from t to v
	- no loop
*/

// construction function to initialize Graph
Graph::Graph(int nodeNum)
{
	// number of the nodes
	this->nodeNum = nodeNum; 

	int i, j;
	// initial the node info
	for(i = 0; i < nodeNum; i++)
	{
		node[i] = 0;
	}
	
	// initialize the edge info
	for(i  = 0; i < nodeNum; i++)
	{
		for(j = 0; j < nodeNum; j++)
		{
			// INF denotes no connected edge
			edge[i][j] = 0;
		}
	}
}

// interface to get nodeNum
int Graph::getNodeNum()
{
	return nodeNum;
}

// interface to set node name
void Graph::setNode(char* nodeName)
{
	for(int i = 0; i < nodeNum; i++)
	{
		this->node[i] = nodeName[i];
	}
}


// interface to get node name
char Graph::getNode(int nodeIndex)
{
	return node[nodeIndex];
}

// interface to set edge of the graph
void Graph::setEdge(char source, char destination, int value)
{
	int sourNum=0, destNum=0;
	for(int i = 0; i < nodeNum; i++)
	{
		if(source == node[i])
		{
			sourNum = i;
		}
		if(destination == node[i])
		{
			destNum = i;
		}
	}
	edge[sourNum][destNum] = value;
}

// interface to set edge of the graph
void Graph::setEdge(int source, int destination, int value)
{
	edge[source][destination] = value;
}


// interface to get value of a specified edge
int Graph::getEdge(int source, int destination)
{
	return edge[source][destination];
}
