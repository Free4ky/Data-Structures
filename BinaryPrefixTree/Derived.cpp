#include "Derived.h"
#include "Base.h"
#include <string>
#include<iostream>
using namespace std;
Derived::Derived(char name, Base* parent, Base* LeftSon, Base* RightSon):Base(name, parent, LeftSon, RightSon) {};