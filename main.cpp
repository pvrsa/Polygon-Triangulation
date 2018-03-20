#include <iostream>
#include "dcel.h"

using namespace std;

int main(){

    DCEL graph;
    
    int V = graph.ver.size();

    for(int i=0;i<V;i++)
        cout << graph.ver[i].type << endl;
    return 0;
}