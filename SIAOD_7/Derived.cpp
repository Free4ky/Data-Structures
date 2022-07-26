#include "Derived.h"
Derived::Derived(int code,Base* parent, Base* leftSon, Base* rightSon) : Base()
{
	stringstream ss;
	ss << code;
	this->parent = parent;
	this->leftSon = leftSon;
	this->rightSon = rightSon;
	
	if (parent) 
	{
		this->code = (dc parent)->getCode() + ss.str();
		setCurrent(code,parent);
	}
	else 
	{
		this->code = "";
	}
	ss.str("");
}
Base* Derived::getParent() { return parent; }
Base* Derived::getLeftSon() { return leftSon; }
Base* Derived::getRightSon() { return rightSon; }
string Derived::getCode() { return code; }
void Derived::setLeftSon(Base* leftSon) { this->leftSon = leftSon; }
void Derived::setRightSon(Base* rightSon) { this->rightSon = rightSon; }
void Derived::setCurrent(int cs, Base* parent) 
{
	Derived* p = dc parent;
	switch (cs)
	{
	case 0:
		for (int i = 0; i < p->left.size(); i++) 
		{
			current.push_back(p->left[i]);
		}
		break;
	case 1:
		for (int i = 0; i < p->right.size(); i++)
		{
			current.push_back(p->right[i]);
		}
		break;
	}
}
vector<Letters*> Derived::getVec(int cs) 
{
	switch (cs)
	{
	case 1:
		return current;
	case 2:
		return left;
	case 3:
		return right;
	}
}
void Derived::add(Letters* letter, int cs) 
{
	switch (cs)
	{
	case 1:
		left.push_back(letter);
		break;
	case 2:
		right.push_back(letter);
		break;
	}
}
