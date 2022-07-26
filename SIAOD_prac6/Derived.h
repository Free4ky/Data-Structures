#ifndef DERIVED_H
#define DERIVED_H
#include "Base.h"
class Derived : public Base {
public:
	Derived(Base*);
};
#endif // !DERIVED_H
