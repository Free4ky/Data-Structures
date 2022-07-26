#ifndef BASE_H
#define BASE_H

using namespace std;
#include <string>
#include <stack>
class Base
{
private:
	static int CompareQuantity;
	static Base* root;
	Base* RightSon;
	Base* LeftSon;
	Base* parent;
	int bitNubmer;
	int licenseNubmer;
	static int max;
	struct treeNode
	{
		Base* node;
		int treeLevel;
		treeNode(Base* current,int level) : node(current), treeLevel(level) {}
	};
	static stack<treeNode*> NodeStack;
public:
	void buildTree(string);
	void printTree();
	Base(int a = 0, int b = 0, Base* = 0, Base* = 0, Base* = 0);
	void addNode(int, int, Base*);
	int getLicenseNumber();
	void execute(string path);
	void FindLine(int,string);
	Base* FindNode(int, Base*);
	void FindRightLeaf(int, Base*);
	void FindLeftLeaf(string, Base*);
	void FindMAX(Base*);
	//void clear_stack();
	void deleteNode(int license);
};
char* splitString(string);
string setTabs(int);
#endif