#include "Base.h"
#include "Derived.h"
#include <iostream>
#pragma warning(disable : 4996)
using namespace std;
int main()
{
    string path = "C:\\Новая папка\\random_uinc.txt";
    Base start;
    start.execute(path);
    return 0;
}