#include <stdio.h>
#include <iostream>
#include "FluxLog.h"
using namespace std;

int main()
{
    FluxLog src ("test.txt", ios_base::in);
    src.LireLigne().Afficher();
}