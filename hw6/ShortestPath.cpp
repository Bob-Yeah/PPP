#include <iostream>
#include <queue>
#include <string>
#include <stdint.h>
using namespace std;

//GLOBAL VARIABLES:
struct Graph {
	int adjMatrix[10][10];
};

/*
Undirected Graph
Nodes: 1 2 3 4 5 6 7 8 9 10
Edges: (1,2,4) (1,3,1) (1,4,3) (1,6,8) (2,6,2) (3,4,5) (3,5,7) (4,5,6) (4,6,7) 
(5,6,8) (5,7,2) (5,9,16) (6,7,5) (6,8,12) (7,8,11) (7,9,8) (7,10,18) (8,10,12) (9,10,30)
*/

void initGraph(Graph &Graph_test) {
	for (int i =0; i < 10 ; i++)
		for (int j = 0; j < 10; j++)
			Graph_test.adjMatrix[i][j]=INT32_MAX;
	Graph_test.adjMatrix[0][1]=4;
	Graph_test.adjMatrix[1][0]=4;
	Graph_test.adjMatrix[0][2]=1;
	Graph_test.adjMatrix[2][0]=1;
	Graph_test.adjMatrix[0][3]=3;
	Graph_test.adjMatrix[3][0]=3;
	Graph_test.adjMatrix[0][5]=8;
	Graph_test.adjMatrix[5][0]=8;
	Graph_test.adjMatrix[1][5]=2;
	Graph_test.adjMatrix[5][1]=2;
	Graph_test.adjMatrix[2][3]=5;
	Graph_test.adjMatrix[3][2]=5;
	Graph_test.adjMatrix[2][4]=7;
	Graph_test.adjMatrix[4][2]=7;
	Graph_test.adjMatrix[3][4]=6;
	Graph_test.adjMatrix[4][3]=6;
	Graph_test.adjMatrix[3][5]=7;
	Graph_test.adjMatrix[5][3]=7;
	Graph_test.adjMatrix[4][5]=8;
	Graph_test.adjMatrix[5][4]=8;
	Graph_test.adjMatrix[4][6]=2;
	Graph_test.adjMatrix[6][4]=2;
	Graph_test.adjMatrix[4][8]=16;
	Graph_test.adjMatrix[8][4]=16;
	Graph_test.adjMatrix[5][6]=5;
	Graph_test.adjMatrix[6][5]=5;
	Graph_test.adjMatrix[5][7]=12;
	Graph_test.adjMatrix[7][5]=12;
	Graph_test.adjMatrix[6][7]=11;
	Graph_test.adjMatrix[7][6]=11;
	Graph_test.adjMatrix[6][8]=8;
	Graph_test.adjMatrix[8][6]=8;
	Graph_test.adjMatrix[6][9]=18;
	Graph_test.adjMatrix[9][6]=18;
	Graph_test.adjMatrix[7][9]=12;
	Graph_test.adjMatrix[9][7]=12;
	Graph_test.adjMatrix[8][9]=30;
	Graph_test.adjMatrix[9][8]=30;
}

void Dijkstra(Graph graph, int node1, int node2) {
	int dists[10];
	bool searchedNode[10];
	queue <int> route[10];
	for (int i=0;i<10;i++){
		dists[i]=INT32_MAX;
		searchedNode[i]=false;
	}
	searchedNode[node1-1]=true;
	dists[node1-1]=0;
	route[node1-1].push(node1);
	int currentNode = node1-1;
	while (searchedNode[node2-1]!=true){
		int shortestDist=INT32_MAX;
		int shortestNode=-1;
		for (int j=0;j<10;j++){
			if ((graph.adjMatrix[currentNode][j]!=INT32_MAX) 
			&& (searchedNode[j]==false) ){
				//cout << "CurrrentNode: "<<currentNode+1 <<" to Node: "<< j+1 << " dist is "<<graph.adjMatrix[currentNode][j]<<endl;
				if (dists[currentNode]+graph.adjMatrix[currentNode][j]<dists[j]){
					
					dists[j]=dists[currentNode]+graph.adjMatrix[currentNode][j];
					//cout<<"Update dist to Node: "<<j+1<<" is "<< dists[j]<<endl;
					route[j]=route[currentNode];
					route[j].push(j+1);
				}
				//cout << "Current dist of "<<j+1 << " is "<<dists[j]<<endl;
				
			}
		}
		for (int i=0;i<10;i++){
			if(searchedNode[i]) continue;
			if (dists[i]<shortestDist){
				shortestDist=dists[i];
				shortestNode=i;
			}
			//cout<< "Current shortest dist is "<<shortestDist << " shortest Node is "<<shortestNode+1<<endl;
		}
		searchedNode[shortestNode]=true;
		currentNode=shortestNode;
		//cout<< currentNode +1 <<endl;
	}
	cout<<dists[node2-1]<<endl;
	while (!route[node2-1].empty()){
		cout << route[node2-1].front();
		route[node2-1].pop();
		if (route[node2-1].empty()) break;
		cout << " -> ";
	}
	cout << endl;
}

int main() {
	Graph graph_test;
	initGraph(graph_test);
	string node1,node2;
	while (true){
		cout << "input two nodes: ";
		cin >> node1 ;
		if ((node1 == "q") || (node1 == "quit")) break;
		cin >> node2;
		Dijkstra(graph_test,stoi(node1,nullptr,0),stoi(node2,nullptr,0));
	}
	return 0;
}