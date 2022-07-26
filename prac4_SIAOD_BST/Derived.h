#ifndef DERIVED_H
#define DERIVED_H
#include "Base.h"
class Derived : public Base
{
public:
	Derived(int,int,Base*,Base*, Base*);
};
#endif // !DERIVED_H

