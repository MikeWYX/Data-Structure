#include <iostream>
using namespace std;

typedef struct array{
    int len;
    Vertex* v[max];
} array;

void insert(vertex *s,array *a){
    a->v[a->len++]=&s;
};
vertex* remove(array *a){
    a->len--;
    return a->v[a->len];
};
void updatepath(vertex *s,array *a){
    a->v[a->len++]=&s;
};
int inarray(vertex *s,array *a){
    for(int i=0;i<a->len;i++){
        if(a->v[i]==s)
            return 1;
    }
    return 0;
}
int isempty(array *a){
    if(a->len==0)
        return 1;
    return 0;
}
array search(graph *g,int goal,vertex *s0,void visit(vertex *)){
    array fringe,visited,path;
    if(s0->id==goal)
        return s0;
    insert(s0,&fringe);
    while(1){
        if(isempty(fringe)){
            path.len=0;
            return path;
        }
        vertex *s=remove(&fringe);
        if(!inarray(s,visited)){
            insert(s,&visited);
            visit(s);
            updatepath(s,&path);
            for(vertex*s2;s2;s2=nextneighbour){
                if(s2->id==goal)
                    return path+s2;
                insert(s2,&fringe);
            }
        }
    }
}
