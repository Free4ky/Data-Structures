#include "Graph.h"
#include <iostream>
#include <stack>
#include <sstream>

using namespace std;

Graph::Graph() {
	cout << "Input node quantity: ";
	cin >> nodeQuantity;
	cout << "\n";
	AdjMatrix = new int* [nodeQuantity];
	for (int i = 0; i < nodeQuantity; i++)
	{
		AdjMatrix[i] = new int[nodeQuantity];
	}
	for (int i = 0; i < nodeQuantity; i++) {
		for (int j = 0; j < nodeQuantity; j++) {
			AdjMatrix[i][j] = 0;
		}
	}
	ShortestPathes = new int* [nodeQuantity];
	for (int i = 0; i < nodeQuantity; i++)
	{
		ShortestPathes[i] = new int[nodeQuantity];
	}
	for (int i = 0; i < nodeQuantity; i++) {
		for (int j = 0; j < nodeQuantity; j++) {
			ShortestPathes[i][j] = 0;
		}
	}
}

void Graph::addNode(int x, int y, int path_length) {
	if (x - 1 > nodeQuantity || y - 1 > nodeQuantity || x - 1 < 0 || y - 1 < 0) { return; }
	if (x != y) 
	{
		AdjMatrix[x - 1][y - 1] = 1;
		ShortestPathes[x - 1][y - 1] = path_length;
	}
}

void Graph::pritMatrix(int** matrix) {
	int x = 0;
	for (int i = 0; i < nodeQuantity; i++) {
		for (int j = 0; j < nodeQuantity; j++){
			cout << matrix[i][j] << "\t";
			x++;
			if (x == nodeQuantity) {
				cout << "\n";
				x = 0;
			}
		}
	}
	cout << "\n";
}

void Graph::fillAdjMatrix() {
	int start;
	int end;
	int path_length;
	cout << "Input graph edges in format (node, connected node, path length):\n";
	cin >> start;
	cin >> end;
	cin >> path_length;
	while (start != -1) {
		addNode(start, end, path_length);
		cin >> start;
		if (start == -1) { return;}
		cin >> end;
		cin >> path_length;
	}
}
int** Graph::Floyd() {
	int** path = new int* [nodeQuantity];
	for (int i = 0; i < nodeQuantity; i++) 
	{
		path[i] = new int[nodeQuantity];
	}
	for (int i = 0; i < nodeQuantity; i++) 
	{
		for (int j = 0; j < nodeQuantity; j++) 
		{
			path[i][j] = ShortestPathes[i][j];
		}
	}
	int inf = 100000;
	for (int i = 0; i < nodeQuantity; i++)
	{
		for (int j = 0; j < nodeQuantity; j++) 
		{
			if (path[i][j] == 0 && i != j) 
			{
				path[i][j] = inf;
			}
		}
	}
	for (int k = 0; k < nodeQuantity; k++) 
	{
		for (int i = 0; i < nodeQuantity; i++)
		{
			for (int j = 0; j < nodeQuantity; j++)
			{
				if ((path[i][k] + path[k][j]) < path[i][j])
				{
					path[i][j] = path[i][k] + path[k][j];
				}
			}
		}
	}
	return path;
}

int** Graph::getAdjMatrix() { return AdjMatrix; }
int** Graph::getFloydPathes() { return FloydPathes; }
int** Graph::getShortestPathes() { return ShortestPathes; }

bool Graph::isConnectedGraph() {
	int inf = 100000;
	FloydPathes = Floyd();
	for (int i = 0; i < nodeQuantity; i++) 
	{
		for (int j = 0; j < nodeQuantity; j++)
		{
			if (FloydPathes[i][j] == inf)
			{
				return false;
			}
		}
	}
	return true;
}

void Graph::Deikstra(int st, int ed)
{
	int start = st - 1;
	int end = ed - 1;
	stringstream ss;
	string* pathes = new string[nodeQuantity];
	int* dist = new int[nodeQuantity];
	bool* visited = new bool[nodeQuantity];
	for (int i = 0; i < nodeQuantity; i++) 
	{
		dist[i] = INT_MAX;
		visited[i] = false;
		pathes[i] = ".";
	}
	dist[start] = 0;
	ss << st;
	pathes[start] = ss.str();
	ss.str("");
	int min = INT_MAX;
	int index_min;
	for (int i = 0; i < nodeQuantity; i++) 
	{
		min = INT_MAX;
		for (int j = 0; j < nodeQuantity; j++) 
		{
			if (!visited[j] && dist[j] < min) 
			{
				min = dist[j];
				index_min = j;
			}
		}
		visited[index_min] = true;
		for (int j = 0; j < nodeQuantity; j++) 
		{
			if ((!visited[j]) && (ShortestPathes[index_min][j] > 0) && (dist[index_min] != INT_MAX) &&
				(dist[index_min] + ShortestPathes[index_min][j] < dist[j]))
			{
				dist[j] = dist[index_min] + ShortestPathes[index_min][j];
				ss << j + 1;
				pathes[j] = pathes[index_min] + ss.str();
				ss.str("");
			}
		}
	}

	for (int i = 0; i < nodeQuantity; i++) 
	{
		cout << dist[i] << "\t";
	}
	cout << "\n";
	for (int i = 0; i < nodeQuantity; i++)
	{
		cout << pathes[i] << "\t";
	}
	cout << "\n";
	cout << "Shortest path from " << st << " to " << ed << " is: " << pathes[end]<<"\nIts length is: "<< dist[end]<<"\n";
}