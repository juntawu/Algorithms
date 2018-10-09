#include "graph.h"
#include "push_relabel.h"
#include <stdlib.h>

#define nodeNum 4

int main()
{
	
	// graph wiht node s, u, v, t
	char nodeName[nodeNum] = {'s', 'u', 'v', 't'};
	Graph graph = Graph(nodeNum);
	graph.setNode(nodeName);
	graph.setEdge('s', 'u', 1);
	graph.setEdge('s', 'v', 1);
	graph.setEdge('u', 'v', 1);
	graph.setEdge('u', 't', 1);
	graph.setEdge('v', 't', 1);
	
/*
	char nodeName[nodeNum] = {'s', 'u', 'v', 't'};
	Graph graph = Graph(nodeNum);
	graph.setNode(nodeName);
	graph.setEdge('s', 'u', 3);
	graph.setEdge('u', 'v', 1);
	graph.setEdge('v', 't', 2);
*/	

	Graph residualGraph = graph;

	PushRelabel pushRelabel(nodeNum);
	cout << "maxmium flow: " << pushRelabel.calculateFlow(graph, residualGraph) << endl;

	system("pause");
	return 0;
}