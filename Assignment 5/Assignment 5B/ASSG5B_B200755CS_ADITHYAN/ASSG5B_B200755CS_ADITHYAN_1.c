//gcc ASSG5B_B200755CS_ADITHYAN_1.c
//31-03-2022; 0957

#include <stdio.h>
#include <stdlib.h>

int main(){
    int v;
    scanf("%d",&v);
    int** graph=(int**)malloc(v*sizeof(int*));
    for(int i=0;i<v;i++){
        graph[i]=(int*)malloc(v*sizeof(int));
    }
    for (int i=0;i<v;i++){
        for (int j=0;j<v;j++){
            scanf("%d",&graph[i][j]);
        }
    }
    for (int i=0;i<v;i++){
        printf("%d ",i);
        for (int j=0;j<v;j++){
            if (graph[i][j]==1){
                printf("%d ",j);
            }
        }
        printf("\n");
    }
}