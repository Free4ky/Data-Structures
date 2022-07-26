#ifndef GRAPH_H
#define GRAPH_H

class Graph {
private:
	int** AdjMatrix;
	int** ShortestPathes;
	int** FloydPathes;
	int nodeQuantity;
public:
	Graph();
	void addNode(int,int,int);
	void pritMatrix(int**);
	void fillAdjMatrix();
	bool isConnectedGraph();
	int** Floyd();
	int** getAdjMatrix();
	int** getFloydPathes();
	int** getShortestPathes();
	void Deikstra(int, int);
};
#endif // !GRAPH_H
