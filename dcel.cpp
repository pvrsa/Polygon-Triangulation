#include <bits/stdc++.h>

using namespace std;

struct half_edge;

struct vertex{
    double x;
    double y;
    half_edge *incidentEdge;
};

struct half_edge{
    vertex *origin;
    half_edge *twin;
    half_edge *next;
    half_edge *prev;
};

struct face{
    half_edge *rep;
};

int main(){

    int V,E;

    
    //
    ifstream input("FILES/input1.txt");

    input >> V >> E;


    return 0;
}


