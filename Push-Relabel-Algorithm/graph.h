#ifndef RESIDUAL_GRAPH_H
#define RESIDUAL_GRAPH_H

#define MAX_NODE 100
#define INF 100000000

#include <iostream>
using namespace std;

class Graph
{
public:
	Graph(int nodeNum);
	int getNodeNum();
	void setNode(char* nodeName);
	char getNode(int nodeIndex);
	void setEdge(char source, char destination, int value);
	void setEdge(int source, int destination, int value);
	int getEdge(int source, int destination);

private:
	int nodeNum;
	char node[MAX_NODE];  // nodes array
	int edge[MAX_NODE][MAX_NODE];  // edges array
};


#endif