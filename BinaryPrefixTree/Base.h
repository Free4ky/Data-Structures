#ifndef BASE_H
#define BASE_H
#include <string>

using namespace std;
class Base
{
private:
	Base* parent;
	Base* LeftSon;
	Base* RightSon;
	char name;
public:
	Base(char,Base*, Base*, Base*);
	void setName(char);
	void setParent(Base*);
	void setLeftSon(Base*);
	void setRightSon(Base*);
	Base* getParent();
	Base* getLeftSon();
	Base* getRightSon();
	char getName();
	string convertor();
	void printNames(string);
};
bool isOperator(char);
int Priority(char);
#endif