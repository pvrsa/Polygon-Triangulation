#include "ymono.h"

using namespace std;

int main(){

    DCEL graph;
    
    int V = graph.ver.size();

    cout << graph.edge.size() << endl;

    makeYmono(graph);

    cout << graph.edge.size() << endl;  
    cout << graph.faces.size() << endl;  

    triangulate(graph);
    

    return 0;
}