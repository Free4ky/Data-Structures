#include <iostream>
#include "Graph.h"
using namespace std;

int main()
{
	Graph g;
	//g.pritAdjMatrix();
	//g.addNode(3, 1);
	//g.pritMatrix(g.getAdjMatrix());
	g.fillAdjMatrix();
	//g.pritMatrix(g.getAdjMatrix());
	cout <<"\nIs graph connected: "<< boolalpha <<g.isConnectedGraph()<<"\n";
	cout << "\nShortsest pathes by Floyd method:\n";
	g.pritMatrix(g.getFloydPathes());
	cout << "Weighted adjacency matrix:\n";
	g.pritMatrix(g.getShortestPathes());
	g.Deikstra(5, 4);
	return 0;
}