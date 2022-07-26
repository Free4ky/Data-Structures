#ifndef DERIVED_H
#define DERIVED_H
#include "Base.h"
#include <sstream>
class Derived : public Base
{
private:
	vector<Letters*> current;
	vector<Letters*> left;
	vector<Letters*> right;
	string code;
	Base* parent;
	Base* leftSon;
	Base* rightSon;
public:
	Derived(int,Base* = 0, Base* = 0,Base* = 0);
	void setLeftSon(Base*);
	void setRightSon(Base*);
	//void setParent(Base*);
	Base* getParent();
	Base* getRightSon();
	Base* getLeftSon();
	string getCode();
	vector<Letters*> getVec(int);
	void add(Letters*,int);
	void setCurrent(int, Base*);

};

#endif // !DERIVED_H
