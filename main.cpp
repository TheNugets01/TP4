#include <stdio.h>
#include <iostream>
#include "LireLigne.h"
using namespace std;

int main()
{
    LireLigne src ("test.log", ios_base::in);
    cout << src.Lecture().ip << endl;
}