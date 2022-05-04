//gcc ASSG5B_B200755CS_ADITHYAN_3.c
//02-04-2022; 1015

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
    int v;
    int weight;
    struct Node* next;
};
typedef struct Node* node;

node makeEdge(int v){
    node x=(node)malloc(sizeof(struct Node));
    x->v=v;
    x->weight=0;
    x->next=NULL;
    return x;
}

int findMin(int* dist,int* visit, int n){
    int min=10000000,ind=0;
    for(int i=0;i<n;i++){
        if(dist[i]<min&&visit[i]==0){
            min=dist[i];
            ind=i;
        }
    }
    return ind;
}

void dijkstra1(node* list,int u,int n){
    int* visit=(int*)malloc(n*sizeof(int));
    int* dist=(int*)malloc(n*sizeof(int));
    for (int i=0;i<n;i++){
        visit[i]=0;
        dist[i]=10000000;
    }
    dist[u]=0;
    int a;
    for (int i=0;i<n;i++){
        a=findMin(dist,visit,n);
        visit[a]=1;
        node y=list[a];
        while(y!=NULL){
            if(dist[y->v]>dist[a]+y->weight ){
                dist[y->v]=dist[a]+y->weight;
            }
            y=y->next;
        }
    }
    for (int i=0;i<n;i++){
        if (dist[i]==10000000){
            printf("INF ");
        }else{
            printf("%d ",dist[i]);
        }
    }
    printf("\n");
}

void dijkstra2(node* list,int u,int v,int n){
    int* visit=(int*)malloc(n*sizeof(int));
    int* dist=(int*)malloc(n*sizeof(int));
    for (int i=0;i<n;i++){
        visit[i]=0;
        dist[i]=10000000;
    }
    dist[u]=0;
    int a;
    for (int i=0;i<n;i++){
        a=findMin(dist,visit,n);
        visit[a]=1;
        node y=list[a];
        while(y!=NULL){
            if(dist[y->v]>dist[a]+y->weight){
                dist[y->v]=dist[a]+y->weight;
            }
            y=y->next;
        }
    }
    if (dist[v]==10000000){
        printf("UNREACHABLE\n");
    }else{
        printf("%d\n",dist[v]);
    }
}

int main(){
    int n,u,v;
    scanf("%d\n",&n);
    char* str;
    node* list=(node*)malloc(n*sizeof(node));
    for (int i=0;i<n;i++){
        list[i]=NULL;
    }
    node x,y;
    for (int i=0;i<n;i++){
        str=(char*)malloc(10000*sizeof(char));
        fgets(str,10000,stdin);
        u=0;
        v=0;
        for(u=0;u<strlen(str)-1;u++){
            if(str[u]==' '){
                if(v!=i){
                    x=makeEdge(v);
                    y=list[i];
                    if(y==NULL){
                        list[i]=x;
                    }else{
                        while(y->next!=NULL){
                            y=y->next;
                        }
                        y->next=x;
                    }
                }
                v=0;
            }else{
                v=v*10+str[u]-'0';
            }
        }
        if(v!=i){
                x=makeEdge(v);
                y=list[i];
                if(y==NULL){
                    list[i]=x;
                }else{
                    while(y->next!=NULL){
                        y=y->next;
                    }
                    y->next=x;
                }
            }
    }
    for (int i=0;i<n;i++){
        scanf("%d",&u);
        y=list[u];
        while(y!=NULL){
            scanf("%d",&v);
            y->weight+=v;
            y=y->next;
        }
    }
    while (1){
        str=(char*)malloc(20*sizeof(char));
        scanf("%s",str);
        if(strcmp(str,"apsp")==0){
            scanf("%d",&u);
            dijkstra1(list,u,n);
        }else if(strcmp(str,"sssp")==0){
            scanf("%d %d",&u,&v);
            dijkstra2(list,u,v,n);
        }else if(strcmp(str,"stop")==0){
            return 0;
        }
    }
}