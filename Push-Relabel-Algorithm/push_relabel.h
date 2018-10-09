#ifndef PUSH_RELABEL_H
#define PUSH_RELABEL_H

#include "graph.h"


class PushRelabel
{
public:
	// const???
	PushRelabel(int nodeNum);
	void initialize(Graph& const originalGraph, Graph& residualGraph);
	void push(int source, int destination, Graph& const originalGraph, Graph& residualGraph);
	bool isRelabelValid(Graph& residualGraph, int node);
	void relabel(int node);
	void updateGraph(int source, int destination, int flow, Graph& const originalGraph, Graph& residualGraph);
	int calculateFlow(Graph& originalGraph, Graph& residualGraph);

private:
	int nodeLabel[MAX_NODE];
	int nodeExcess[MAX_NODE];
	int edgeFlow[MAX_NODE][MAX_NODE];
	int edgeDirection[MAX_NODE][MAX_NODE];
};


#endif