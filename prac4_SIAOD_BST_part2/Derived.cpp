#include "Derived.h"
#include "Base.h"
using namespace std;
Derived::Derived(int licenceNumber, int bitNumber, Base* parent, Base* LeftSon, Base* RightSon, int treeLevel, int balance) : Base()
{
	this->licenseNumber = licenceNumber;
	this->bitNumber = bitNumber;
	this->parent = parent;
	this->LeftSon = LeftSon;
	this->RightSon = RightSon;
	this->treeLevel = treeLevel;
	this->balance = balance;
}
int Derived::getBalance() 
{
	return this->balance;
}
int Derived::getBitNumber() 
{
	return this->bitNumber;
}
Base* Derived::getLeftSon()
{
	return this->LeftSon;
}
Base* Derived::getRightSon()
{
	return this->RightSon;
}
Base* Derived::getParent()
{
	return this->parent;
}
int Derived::getLicenseNumber() 
{
	return this->licenseNumber;
}
int Derived::getTreeLevel() 
{
	return this->treeLevel;
}
void Derived::setLeftSon(Base* left)
{
	this->LeftSon = left;
}
void Derived::setRightSon(Base* right)
{
	this->RightSon = right;
}
void Derived::setParent(Base* parent)
{
	this->parent = parent;
}
void Derived::setBalance(int balance) 
{
	this->balance = balance;
}
void Derived::setTreeLevel(int treeLevel) 
{
	this->treeLevel = treeLevel;
}
void Derived::setLicenseNumber(int license) 
{
	this->licenseNumber = license;
}
void Derived::setBitNumber(int bit) 
{
	this->bitNumber = bit;
}