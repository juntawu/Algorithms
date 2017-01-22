#include "ford_fulkerson_v2.h"

// construction function to initialize Graph
Graph::Graph(int nodeNum)
{
	// number of the nodes
	this->nodeNum = nodeNum; 
	flow = 0;

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



// interface to set edge of the graph
void Graph::setEdge(char source, char destination, int value)
{
	// "source" and "destination" are character of the nodes
	// should be transferd to indeces of the node array
	int sourNum, destNum;
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

// interface to set node name
void Graph::setNode(char* nodeName)
{
	for(int i = 0; i < nodeNum; i++)
	{
		this->node[i] = nodeName[i];
	}
}


// get the max flow
int Graph::getFlow()
{
	return flow;
}

// print the intermediate steps of Ford-Flukerson algorithm
void Graph::printPath()
{
	for(int i = 0; i < pathLength; i++)
	{
		if(pathLength - 1 == i)
			cout << node[path[i]] << endl;
		else
			cout << node[path[i]] << " -> ";
	}
}

/************************************************************************/  
/* 深度优先遍历（深度优先搜索）                                         */  
/************************************************************************/  
bool Graph::dfs(int source, bool* visited)  
{  
	// if current node is the destination node (t), then s-t path is found
	if(source == nodeNum - 1)
		return true;

    int destination;  
    visited[source] = true;          
    for(destination = 0; destination < nodeNum; destination++)  // search node adjacent to source  
	{
		// find adjacent node which has not been visited
        if(edge[source][destination]>0  && !visited[destination])  
		{
			// length of current path increase
			pathLength += 1;
			// add adjacent node to s-t path
			path[pathLength-1] = destination; 
			// go on searching adjacent node
			if( !(this -> dfs(destination, visited)) )
			{
				// if current adjacent node could not reach the final destinated node
				// pathLength decrease since it was increased presiously
				// continue to investigate the next adjacent node
				pathLength -= 1;
				continue;
			}
			else
			{
				// if current adjacent node could reach the final destinated node
				return true;
			}
		}
		else if(destination == nodeNum - 1)
			// no adjacent node, means no s-t path
			return false;
	}//end for
} 

// find a s-t path in the residual graph
bool Graph::findPath()
{
	int i, j;

	// initialize the pathLength for current path
	this -> pathLength = 1;
	// initialize the path
	for(i = 0; i < nodeNum; i++) 
	{
		// at the begining, path is vain
		path[i] = 0;
	}

	
	int source = 0;
	bool visited[MAX_NODE];  // record whether the node has been visited
	for(i = 0; i < nodeNum; i++) 
	{
		// at the begining, all nodes have not been visited yet
		visited[i] = false;
	}

	// source node of the s-t path (s)
	path[pathLength-1] = source;
	// search adjacent node by DFS to find the s-t path
	// if there is a s-t path, return true
	return (this->dfs(source, visited));	
}


// find the minimum capacity of edges
int Graph::findBottleneck()
{
	// initialize the bottleneck
	int bottleneck = INF;
	// find the bottleneck on the s-t path
	for(int i = 0; i < pathLength - 1; i++)
	{
		if (bottleneck > edge[path[i]][path[i+1]])
		{
			// the bottleneck is the minimum capacity of the edge on the path
			bottleneck = edge[path[i]][path[i+1]];
		}
	}

	return bottleneck;
}


// update the residual Graph according to s-t path
void Graph::update()
{
	int source = 0;
	int destination = 0;

	// find the bottleneck on the s-t path
	int bottleneck = this->findBottleneck();
	// augementing flow
	flow += bottleneck;

	// go through edges on the s-t path
	for(int i = 0; i < pathLength - 1; i++)
	{
		source = path[i];
		destination = path[i+1];
		// update residual graph
		edge[source][destination] -= bottleneck; 
		edge[destination][source] += bottleneck;
	}
}


