#include <bits/stdc++.h>

using namespace std;

struct half_edge;

struct vertex{
    double x;
    double y;
    half_edge *incidentEdge;
    int type;  //0->start; 1->end; 2->split; 3->merge; 4->regular

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

struct face{
    half_edge *rep;
};

class DCEL{

    public:    
        vector<vertex> ver;  
        vector<half_edge> edge;
        vector<face> faces;
        int V,E;

    DCEL(){

        //Vertex input
        
        ifstream Vinput("FILES/vert1.txt");
        Vinput >> V;

        
        double x,y;
        for(int i=0;i<V;i++){
            Vinput >> x >> y;
            vertex *coord = new vertex(x,y);
            ver.push_back(*coord);   
        }

        int a,b;
        for(int i=0;i<V-1;i++){
            a = i; b = i+1;

            half_edge *edg = new half_edge;
            edg->origin = &ver[a];
            
            half_edge *tw = new half_edge;
            tw->origin = &ver[b]; tw->twin = edg;

            edg->twin = tw;

            if(ver[a].incidentEdge == NULL){
                ver[a].incidentEdge = edg;
                cout << a << ver[a].incidentEdge->origin->x << endl;
            }
            edge.push_back(*edg);
            edge.push_back(*tw);
        }
        E = edge.size();

        for(int i=0;i<E;i+=2){
            a = i%E; b = (i+2)%E;
            edge[a].next = &edge[b];
            edge[b].prev = &edge[a];

            a = (i+1)%E; b=(i+3)%E;
            edge[a].prev = &edge[b];
            edge[b].next = &edge[a];
        }

        face *f1 = new face;
        f1->rep = &edge[0];

        setTypeV();
    }

    int turn_check(int p, int q, int r){
        int val = (ver[q].y - ver[p].y) * (ver[r].x - ver[q].x) -
                (ver[q].x - ver[p].x) * (ver[r].y - ver[q].y);
    
        if (val == 0) return 0;  
        return (val > 0)? 1: 2;
    }

    void setTypeV(){
        
        int a,b,c;
        for(int i = 0;i<V;i++)
        {
            a = (i-1)%V;
            if(a==-1)
                a = V-1;
            b=i%V;
            c=(i+1)%V;
            if( turn_check(a,b,c)==2 )
            {
                if(ver[b].y > ver[a].y && (ver[b].y > ver[c].y||ver[b].y==ver[c].y))
                {
                    ver[i].type = 2;
                }
                else if(ver[b].y < ver[c].y && (ver[b].y < ver[a].y||ver[b].y==ver[a].y))
                {
                    ver[i].type = 3;
                }else{
                    ver[i].type = 4;
                }
            }
            else
            {
                if(ver[b].y > ver[a].y && (ver[b].y > ver[c].y||ver[b].y==ver[c].y))
                {
                    ver[i].type = 0;
                }
                else if(ver[b].y < ver[c].y && (ver[b].y < ver[a].y||ver[b].y==ver[a].y))
                {
                    ver[i].type = 1;
                }
                else
                {
                    ver[i].type = 4;
                }
            }
        }

    }

    void addDiag(int a,int b){

    }

    //ToDo - sort according to x coord if y is same
    vector<int> getEventQueue(){
        vector<pair<double,int > > lala;
        for(int i=0;i<V;i++){
            lala.push_back(make_pair(ver[i].y,i));
        }
        sort(lala.begin(),lala.end());
    
        vector<int> eventQueue;

        for(int i=0;i<V;i++){
            eventQueue.push_back(lala[i].second);
        }

        return eventQueue;
    }
};




