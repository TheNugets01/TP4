#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <set>
#include <iterator>
using namespace std;

int main() {

    string url = "http://intranet-if.insa-lyon.fr/!";
    cout << url.erase(0, url.find("!") ) << endl;

    /*bool valide = true;
    size_t found = url.find(".css",0);
    int nbExtensions = 3;
    string extensions[nbExtensions] = {".css", ".JPG", ".js" };
    int i = 0;
    while (valide == true && i<nbExtensions)
    {
        found = url.find(extensions[i]);
        if (found != string::npos) { valide = false ;}
        ++i;
    }*/

    return 0;
}