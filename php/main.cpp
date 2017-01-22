#include <iostream>
#include "ford_fulkerson_v2.h"

#include <stdlib.h>
using namespace std;
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

	// Ford-Fulkerson algorithm find maximum flow
	while(graph.findPath())
	{
		graph.printPath();
		graph.findBottleneck();
		graph.update();
	}

	// print maximum flow
	cout << "max flow: " << graph.getFlow() << endl;


	system("pause");
	return 0;
}