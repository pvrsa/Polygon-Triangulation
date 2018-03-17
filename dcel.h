#include <bits/stdc++.h>

using namespace std;

struct half_edge;

struct vertex{
    double x;
    double y;
    half_edge *incidentEdge;

    vertex(double a,double b){
        x = a;
        y = b;
        incidentEdge = NULL;
    }
};

struct half_edge{
    vertex *origin;
    half_edge *twin;
    half_edge *next;
    half_edge *prev;

    half_edge(){
        next = NULL;
        prev = NULL;
    }
};

// struct face{
//     half_edge *rep;
// };
class DCEL{

    public:    
        vector<vertex> ver;  
        vector<half_edge> edg;
        
    DCEL(){

        //Vertex input
        int V;
        ifstream Vinput("FILES/vert1.txt");
        Vinput >> V;

        
        double x,y;
        for(int i=0;i<V;i++){
            Vinput >> x >> y;
            vertex *coord = new vertex(x,y);
            ver.push_back(*coord);   
        }

        //Edge input
        int E;
        ifstream Einput("FILES/edges1.txt");
        Einput >> E;


        double a,b;
        for(int i=0;i<E;i++){
            Einput >> a >> b;
            half_edge *edge = new half_edge;
            edge->origin = &ver[a];
            
            half_edge *tw = new half_edge;
            tw->origin = &ver[b]; tw->twin = edge;

            edge->twin = tw;

            if(ver[a].incidentEdge == NULL){
                ver[a].incidentEdge = edge;
                cout << a << ver[a].incidentEdge->origin->x << endl;
            }
            if(ver[b].incidentEdge == NULL){
                ver[b].incidentEdge = tw;
                cout << b << ver[b].incidentEdge->origin->x << endl;
            }

            edg.push_back(*edge);
            edg.push_back(*tw);
        }

    }

};




