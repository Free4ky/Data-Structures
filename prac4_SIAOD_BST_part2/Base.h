#ifndef BASE_H
#define BASE_H
using namespace std;
#include <string>
#include <chrono>
class Base
{
protected:
	static Base* root;
	static Base* LastAddedNode;
private:
	string path;
	static int max;
	static int RotateQuantity;
	static int NodeQuantity;
	static int CompareQuantity;
public:
	Base();
	void buildTree();
	void printTree(int,Base*);
	void FindLine(int);
	Base* FindNode(int, Base*);
	//string getPath();
	int execute();
	void addNode(int, int, Base*, int);
	void rebalance();
	int countLevels(int, Base*);
	void newBalacne(Base*);
	Base* findReferenceNode(Base*);
	void TurnLeft(Base*);
	void TurnRight(Base*);
	void TurnLR(Base*);
	void TurnRL(Base*);
	int whatTurn(Base*, Base*);
	void FindMAX(Base*);
	void deleteNode(int);
	void deleteAndRebalance(int);
	Base* FindLeaf(Base*);
};
char* splitString(string);
string setTabs(int);
#endif