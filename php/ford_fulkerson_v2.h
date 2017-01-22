#ifndef FORD_FULKERSON_H
#define FORD_FULKERSON_H

#define MAX_NODE 100  // default graph nodes
#define INF 100000000  // 

#include <iostream>
using namespace std;

class Graph
{
public:
	Graph(int nodeNum);  
	void setEdge(char source, char destination, int value);
	void setNode(char* nodeName);
	int getFlow();  // function to get the max flow
	void printPath();  // function to print the intermediate steps of Ford-Flukerson algorithm
	bool dfs(int soruce, bool* visited);  // function to search a s-t path with DFS algorithm
	bool findPath();   // function to search a s-t path using dfs()
	int findBottleneck();  // function to find the minimum capacity of edges on s-t path
	void update();  // update the residual Graph according to s-t path

private:
	int flow;
	int nodeNum;
	char node[MAX_NODE];  // nodes array
	int edge[MAX_NODE][MAX_NODE];  // edges array
	int path[MAX_NODE];
	int pathLength;
};

#endif