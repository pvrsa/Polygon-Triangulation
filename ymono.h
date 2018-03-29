#include "dcel.h"

void handleStartVertex(int x,DCEL &graph);
void handleEndVertex(int x,DCEL &graph);
void handleSplitVertex(int x,DCEL &graph);
void handleMergeVertex(int x,DCEL &graph);
void handleRegVertex(int x,DCEL &graph);

bool orientation(vertex *p, vertex *q, vertex *r){
    int val = (q->y - p->y) * (r->x - q->x) -
            (q->x - p->x) * (r->y - q->y);

    
    return (val >= 0)? false: true;
}

struct compare {
    using is_transparent = void;
    bool operator() (const half_edge *x, const half_edge *y) const{
        vertex *a = x->origin;
        vertex *b = x->twin->origin;
        vertex *c = y->origin;
        vertex *d = y->twin->origin;
        
        vertex *temp;
        if(a->y > b->y){
            temp = a;
            a=b;
            b=temp;
        }
        
        if(c->y > d->y){
            temp = c;
            c=d;
            d=temp;
        }

        return orientation(a,b,c);
        
    }

    bool operator()(const half_edge *x,vertex *v)
    const
    {
         vertex *a = x->origin;
         vertex *b = x->twin->origin;
        //  vertex *c = v->incidentEdge->origin;  
        vertex *temp;
        if(a->y > b->y){
            temp = a;
            a=b;
            b=temp;
        }

        return orientation(a,b,v);
    }

    bool operator()(vertex *v ,const half_edge *x)
    const
    {
         vertex *a = x->origin;
         vertex *b = x->twin->origin;
        //  vertex *c = v->incidentEdge->origin;  
        
        vertex *temp;
        if(a->y > b->y){
            temp = a;
            a=b;
            b=temp;
        }

        return orientation(a,b,v);

    }
};

set<half_edge*, compare> status;
map<half_edge*,vertex*> helper;

void makeYmono(DCEL &graph){
    vector<int> Q = graph.getEventQueue();

    

    // c.insert(graph.edge[0]);
    // c.insert(graph.edge[2]);
    // c.insert(graph.edge[4]);
    // c.insert(graph.edge[6]);    

    // cout << graph.edge[0] << endl;
    // cout << graph.edge[2] << endl;
    // cout << graph.edge[4] << endl;
    // cout << graph.edge[6] << endl;

    // for (set<half_edge*>::iterator it=c.begin(); it!=c.end(); ++it)
    //     std::cout << ' ' << *it << endl;

    // vertex *test = new vertex(3.5,-1.5);
    // set<half_edge*>::iterator it = c.find(test);
    // cout << *it << endl;    

    for(int i=0;i<Q.size();i++){
        switch(graph.ver[Q[i]]->type){
            case 0: handleStartVertex(Q[i],graph);
                break;
            case 1: handleEndVertex(Q[i],graph);
                break;
            case 2: handleSplitVertex(Q[i],graph);
                break;
            case 3: handleMergeVertex(Q[i],graph);
                break;
            case 4: handleRegVertex(Q[i],graph);
                break;
        }
    }

}


void handleStartVertex(int x,DCEL &graph){
    cout << "Start" << endl;
   
    half_edge *neig = graph.edge[((x+graph.V-1) % graph.V)*2]; 
    status.insert(neig);

    helper[neig] = graph.ver[x];
}

void handleEndVertex(int x,DCEL &graph){
    cout << "End" << endl;
    
    half_edge *neig = graph.edge[x*2];
    int c;
    if(helper[neig]){
        if(helper[neig]->type == 3){
            c = find(graph.ver.begin(),graph.ver.end(),helper[neig]) - graph.ver.begin();
            graph.addDiag(c,x);
        }
    }

    status.erase(neig); 
}

void handleSplitVertex(int x,DCEL &graph){
    cout << "Split" << endl;
    //  cout << graph.ver[x]->x << endl;
    set<half_edge*>::iterator it = status.find(graph.ver[x]);
    vertex* con = helper[*it];
    int c = find(graph.ver.begin(),graph.ver.end(),con) - graph.ver.begin();

    graph.addDiag(c,x);
    cout << x << " " << c << endl;
    helper[*it] = graph.ver[x];

    half_edge *neig = graph.edge[((x+graph.V-1) % graph.V)*2]; 
    status.insert(neig);
    helper[neig] = graph.ver[x];
}

void handleMergeVertex(int x,DCEL &graph){
    cout << "Merge" << endl;
    
    half_edge *neig = graph.edge[x*2];
    int c;
    if(helper[neig]){
        if(helper[neig]->type == 3){
            c = find(graph.ver.begin(),graph.ver.end(),helper[neig]) - graph.ver.begin();
            graph.addDiag(c,x);
        }
    }

    status.erase(neig);

    set<half_edge*>::iterator it = status.find(graph.ver[x]);
    vertex* con = helper[*it];
    c = find(graph.ver.begin(),graph.ver.end(),con) - graph.ver.begin();
    
    if(con->type == 3){
        graph.addDiag(c,x);
    }
    helper[*it] = graph.ver[x];
 
}

void handleRegVertex(int x,DCEL &graph){
    cout << "Regular" << endl;
    
    half_edge *neig = graph.ver[x]->incidentEdge;
    if(neig->origin->y < neig->twin->origin->y){
        neig = graph.edge[x*2];
        int c;
        if(helper[neig]){
            if(helper[neig]->type == 3){
                c = find(graph.ver.begin(),graph.ver.end(),helper[neig]) - graph.ver.begin();
                graph.addDiag(c,x);
            }
        }
        status.erase(neig);

        neig = graph.edge[((x+graph.V-1) % graph.V)*2]; 
        status.insert(neig);
        
        helper[neig] = graph.ver[x];
        
    }else{
        set<half_edge*>::iterator it = status.find(graph.ver[x]);
        vertex* con = helper[*it];
        if(con->type == 3){
            int c = find(graph.ver.begin(),graph.ver.end(),con) - graph.ver.begin();
            graph.addDiag(c,x);
        }
        helper[*it] = graph.ver[x];
    }

}

bool vertex_sorter(vertex* const &lhs, vertex* const& rhs) {
        if(lhs->y != rhs->y)
            return lhs->y > rhs->y;
        else 
            return lhs->x < rhs->x;
}

void triangulate(DCEL &graph)
{   
    vector<vertex*> lala;
    vector<vertex*> stk;
    vector<pair<vertex*,vertex* > > diags;

    map<vertex*,int > orient; //0->upper , 1->lower
    half_edge* inface; int F = graph.faces.size();

    for(int j = 1;j < F;j++)
    {
        cout << "Face : " << j << " " << graph.faces[j]->vertices.size() << endl;
        
        stk.clear();diags.clear();
        lala = graph.faces[j]->vertices;
        sort(lala.begin(),lala.end(),vertex_sorter);
        
        inface = graph.faces[j]->rep;

        cout << "Vertices \n";
        for(int i=0;i<lala.size();i++){
            if(inface->origin->y < inface->next->origin->y)
                orient[inface->origin]=0;
            else
                orient[inface->origin]=1;
            cout << inface->origin->x << " " << inface->origin->y << endl; 
            cout << orient[inface->origin] << endl;    
             
            inface = inface->next;
        }

        cout << "AHBSDI " << endl;
        for(int i=0;i<lala.size();i++){
            cout << lala[i]->x << " " << lala[i]->y << endl;
            cout << orient[lala[i]] << endl;    
        }
        stk.push_back(lala[0]);
        stk.push_back(lala[1]);
        for(int i=2;i<lala.size()-1 ; i++){
            if(orient[lala[i]] != orient[stk.back()]){
                while(stk.size() != 1){
                    diags.push_back(make_pair(stk.back(),lala[i]));
                    cout << "ASUHD" << endl;
                    stk.pop_back();
                    stk.push_back(lala[i-1]);
                    stk.push_back(lala[i]);
                }
            }else{

            }
        }

        for(int i=0;i<diags.size();i++){
            graph.addEdge(diags[i].first , diags[i].second);
        }
        cout << graph.edge.size() << endl;
    }
}



