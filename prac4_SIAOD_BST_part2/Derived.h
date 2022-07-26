#ifndef DERIVED_H
#define DERIVED_H
#include "Base.h"
class Derived : public Base
{
private:
	Base* LeftSon;
	Base* RightSon;
	Base* parent;
	int licenseNumber;
	int bitNumber;
	int treeLevel;
	int balance;
public:
	Derived(int, int, Base*, Base*, Base*,int treeLevel = 0, int balance = 0);
	Base* getLeftSon();
	Base* getRightSon();
	Base* getParent();
	int getLicenseNumber();
	int getBitNumber();
	int getTreeLevel();
	int getBalance();
	void setBitNumber(int);
	void setLicenseNumber(int);
	void setLeftSon(Base*);
	void setRightSon(Base*);
	void setParent(Base*);
	void setBalance(int);
	void setTreeLevel(int);
};
#endif // !DERIVED_H