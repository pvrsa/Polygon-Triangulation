#include <iostream>
#include "dcel.h"

using namespace std;

int main(){

    DCEL graph;
    
    int V = graph.ver.size();
    
    for(int i=0;i<V;i++){
        if(graph.ver[i].incidentEdge != NULL)
            cout << graph.ver[i].incidentEdge->origin->x << endl;
    }

    return 0;
}