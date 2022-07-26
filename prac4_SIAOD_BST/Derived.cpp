#include "Base.h"
#include "Derived.h"
#pragma warning(disable : 4996)

Derived::Derived(int licenceNumber, int bitNumber,Base* parent, Base* LeftSon, Base* RightSon) : Base(licenceNumber, bitNumber, parent, LeftSon, RightSon){}
