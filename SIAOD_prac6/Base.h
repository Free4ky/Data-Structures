#ifndef BASE_H
#define BASE_H
#include <vector>
#include <iostream>
using namespace std;
class Base {
private:
	vector<Base*> children;
	vector<Base*>::iterator children_iterator;
	Base* parent;
	int** field;
	//bool visited[8];
	static const int chess_size = 8;
	static vector<Base*> AllSolutions;
public:
	Base(Base* = 0);
	void FindLeaf(Base*);
	bool CheckSolution();
	void pritMatrix(Base*);
	void setParent(Base*);
	void setField(Base*);
	void setImPossibleCords(Base*, int, int);
	void buildTree(Base*, int = 0);
	//void setVisited(bool);
	vector<Base*> getChildren();
	int execute();
	//int** getField();
};
#endif // !BASE_H