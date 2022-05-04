//gcc ASSG5B_B200755CS_ADITHYAN_4.c
//01-04-2022; 2215

#include <stdio.h>
#include <stdlib.h>

struct Edge{
    int x;
    int y;
    int w;
    struct Edge* next;
};
typedef struct Edge* edge;

edge makeEdge(int x,int y,int w){
    edge n=(edge)malloc(sizeof(struct Edge));
    n->x=x;
    n->y=y;
    n->w=w;
    n->next=NULL;
    return n;
}

edge makeList(int e){
    edge head=NULL;
    edge tail=NULL;
    int x,y,w;
    for(int i=0;i<e;i++){
        scanf("%d %d %d",&x,&y,&w);
        if(head==NULL){
            head=makeEdge(x,y,w);
            tail=head;
        }else{
            tail->next=makeEdge(x,y,w);
            tail=tail->next;
        }
    }
    return head;
}


int main(){
    int v,e;
    scanf("%d %d",&v,&e);
    int* dist=(int*)malloc(v*sizeof(int));
    for(int i=0;i<v;i++){
        dist[i]=100000;
    }
    edge list=makeList(e);
    edge a;
    dist[list->x]=0;
    for(int i=1;i<v;i++){
        a=list;
        while(a!=NULL){
            if (dist[a->x]!=100000&&dist[a->x]+a->w<dist[a->y]){
                dist[a->y]=dist[a->x]+a->w;
            }
            a=a->next;
        }
    }
    a=list;
    while(a!=NULL){
        if (dist[a->x]!=100000&&dist[a->x]+a->w<dist[a->y]){
            printf("1\n");
            return 0;
        }
        a=a->next;
    }
    printf("-1\n");
    return 0;
}