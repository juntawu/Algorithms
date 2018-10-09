#include "push_relabel.h"

// construction function to initilize attributes
PushRelabel::PushRelabel(int nodeNum)
{
	int i, j;
	for(i = 0; i < nodeNum; i++)
	{
		nodeLabel[i] = 0;
		nodeExcess[i] = 0;
		for(j = 0; j < nodeNum; j++)
		{
			 edgeFlow[i][j] = 0;
			 edgeDirection[i][j] = 0;
		}
	}
}

// initialization
void PushRelabel::initialize( Graph& const originalGraph, Graph& residualGraph)
{
	int i, j;
	int nodeNum = originalGraph.getNodeNum();

	// initialize the node label: h(s)=n; h(t)=0
	for(i = 0; i < nodeNum; i++)
	{
		// h(s) = n;
		if(0 == i)
			nodeLabel[i] = nodeNum;
		// h(v) = 0 for not "s" node
		else
			nodeLabel[i] = 0;
	}

	// initialize edgeFlow: f(e)=C(e) for all e=(s,u)
	for(j = 0; j < nodeNum; j++)
	{
		// search edge e=(s, u)
		if(originalGraph.getEdge(0, j) > 0)
		{
			// output all good from s
			edgeFlow[0][j] = originalGraph.getEdge(0, j);
			nodeExcess[j] = edgeFlow[0][j];
			this->updateGraph(0, j, edgeFlow[0][j], originalGraph, residualGraph );
		}
	}

	// initialize edge direction flag matrix
	for(i = 0; i < nodeNum; i++)
	{
		for(j = 0; j < nodeNum; j++)
		{
			// search edge in original graph
			if(originalGraph.getEdge(i, j) > 0)
			{
				edgeDirection[i][j] = 1;
				edgeDirection[j][i] = -1;
			}
		}
	}
}


// push operation
void PushRelabel::push(int source, int destination, Graph& const originalGraph, Graph& residualGraph)
{
	int v = source;
	int w = destination;
	
	int capacity;  // capacity of the edge (v,w) in original graph
	int flow;  // the flow of edge 
	int excess;  // the excess of the node v
	int bottleneck;

	// (v ,w) is forward edge: f(e) += bottleneck
	if(1 == edgeDirection[v][w])
	{
		capacity = originalGraph.getEdge(v, w);
		flow = edgeFlow[v][w];
		excess = nodeExcess[v];
		bottleneck = ( excess < capacity - flow ) ? excess : (capacity - flow);
		edgeFlow[v][w] += bottleneck;  // update edge flow
		nodeExcess[v] -= bottleneck;  // update nodeExcess
		nodeExcess[w] += bottleneck;  
		this -> updateGraph(v, w, edgeFlow[v][w], originalGraph, residualGraph);
	}
	// (v, w) is backward edge: f(e) -= bottlenece
	else if(-1 == edgeDirection[v][w])
	{
		flow = edgeFlow[w][v];
		excess = nodeExcess[v];
		bottleneck = (excess < flow) ? excess : flow;
		edgeFlow[w][v] -= bottleneck;  // update edge flow
		nodeExcess[v] -= bottleneck;  // update nodeExcess
		nodeExcess[w] += bottleneck;
		this -> updateGraph(w, v, edgeFlow[w][v], originalGraph, residualGraph);
	}


	// print intermediate steps
	cout << residualGraph.getNode(v) << " -> " << residualGraph.getNode(w) << " : " << bottleneck << endl;
}


bool PushRelabel::isRelabelValid(Graph& residualGraph, int node)
{
	
	int newLabel = nodeLabel[node] + 1;
	bool validFlag = false;  // flag denotes whether the new label is valid
	// keep label valid
	for(int j = 0; j < residualGraph.getNodeNum(); j++) 
	{
		// node j connceted with currently investigating node
		if(residualGraph.getEdge(node, j) > 0)
		{
			if(newLabel <= nodeLabel[j] + 1)
				validFlag = true;
			else
			{
				validFlag = false;
				break;
			}
		}	
	}
	
	// "validFlag = true" only with each edge (node, j) satisfies
	// newLabel <= nodeLabel[j] + 1
	return validFlag;
}

// relabel operation
void PushRelabel::relabel(int node)
{
	nodeLabel[node] += 1;
}

// update the residual graph
void PushRelabel::updateGraph(int source, int destination, int flow, Graph& const originalGraph, Graph& residualGraph)
{
	// nes capacity of the edge being pushed and its reversed edge capacity
	int newCapacity = originalGraph.getEdge(source, destination) - flow;
	residualGraph.setEdge(source, destination, newCapacity);
	residualGraph.setEdge(destination, source, flow);
}


int PushRelabel::calculateFlow(Graph& originalGraph, Graph& residualGraph)
{
	int i, j;
	int excessNode;
	int adjacentNode;
	int nodeNum = originalGraph.getNodeNum();

	this ->initialize(originalGraph, residualGraph);
	while(true)
	{
		bool isThereExcessNode = false;
		// search node v with non-zero excess
		for(i = 1; i < nodeNum - 1; i++)
		{
			// found node v (not destination, not source)
			if(nodeExcess[i] > 0)
			{
				excessNode = i;
				isThereExcessNode = true;
				break;  // break for
			} //end if
		} //end for

		// no node v with non-zero excess exists 
		if(false == isThereExcessNode)
			break;  // break while

		
		bool isThereEdge = false;
		// search edge (v, w) in residual graph wiht h(v)>h(w)
		for(j = 0; j < nodeNum; j++)
		{
			if(residualGraph.getEdge(excessNode, j) > 0 && nodeLabel[excessNode] > nodeLabel[j])
			{
				adjacentNode = j;
				isThereEdge = true;
				break; 
			}
		} //end for

		// there is such edge (v, w) in residual graph wiht h(v)>h(w)
		if(true == isThereEdge)
			this->push(excessNode, adjacentNode, originalGraph, residualGraph);
		// no such edge (v, w) in residual graph wiht h(v)>h(w)
		else
		{
			// judge whether the relabel is valid
			if( this->isRelabelValid(residualGraph, excessNode) )
				this ->relabel(excessNode);
		}
	} //end while

	int flow = 0;
	for(j = 0; j < nodeNum; j++)
		flow += edgeFlow[0][j];
	return flow;
}
