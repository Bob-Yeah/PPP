#include <iostream>
#include <set>
#include <string>
using namespace std;


class Edge {
public:
	int fromNode;
	int endNode;
	int dist;
	Edge(int fN, int tN, int dis)
		:fromNode(fN), endNode(tN), dist(dis) {}
};

//GLOBAL VARIABLES:
struct Graph {
	set <int> nodeSet;
	set <Edge> edgeSet;
}Graph_test;

/*
Undirected Graph
Nodes: 1 2 3 4 5 6 7 8 9 10
Edges: (1,2,4) (1,3,1) (1,4,3) (1,6,8) (2,6,2) (3,4,5) (3,5,7) (4,5,6) (4,6,7) 
(5,6,8) (5,7,2) (5,9,16) (6,7,5) (6,8,12) (7,8,11) (7,9,8) (7,10,18) (8,10,12) (9,10,30)
*/

void initGraph(int numOfNode, int numOfEdge) {
	for (int i =0; i < numOfNode ; i++)
		Graph_test.nodeSet.insert(i);
	Graph_test.edgeSet.insert(Edge(1, 2, 4));
	Graph_test.edgeSet.insert(Edge(1, 3, 1));
	Graph_test.edgeSet.insert(Edge(1, 4, 3));
	Graph_test.edgeSet.insert(Edge(1, 6, 8));
	Graph_test.edgeSet.insert(Edge(2, 6, 2));
	Graph_test.edgeSet.insert(Edge(3, 4, 5));
	Graph_test.edgeSet.insert(Edge(3, 5, 7));
	Graph_test.edgeSet.insert(Edge(4, 5, 6));
	Graph_test.edgeSet.insert(Edge(4, 6, 7));
	Graph_test.edgeSet.insert(Edge(5, 6, 8));
	Graph_test.edgeSet.insert(Edge(5, 7, 2));
	Graph_test.edgeSet.insert(Edge(5, 9, 16));
	Graph_test.edgeSet.insert(Edge(6, 7, 5));
	Graph_test.edgeSet.insert(Edge(6, 8, 12));
	Graph_test.edgeSet.insert(Edge(7, 8, 11));
	Graph_test.edgeSet.insert(Edge(7, 9, 8));
	Graph_test.edgeSet.insert(Edge(7, 10, 18));
	Graph_test.edgeSet.insert(Edge(8, 10, 12));
	Graph_test.edgeSet.insert(Edge(9, 10, 30));
}

void Dijkstra(Graph graph, int node1, int node2) {

}

int main() {

}