// gcc ASSG2_B200755CS_ADITHYAN_2.c
// 03-02-2022 ; 0655

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
char* word;
struct node *next;
};
typedef struct node* node;

node makeNode(){//make a node of chain
    node s=(node)malloc(sizeof(struct node));
    s->word=(char*)malloc(100*sizeof(char));
    s->next=NULL;
    return s;
}

node* createHash(int k){//create hash table
    node* h=(node*)malloc(k*sizeof(node));
    for(int i=0;i<k;i++){
        h[i]=NULL;
    }
    return h;
}

void insertHash(node* h,int k,node x){//insert element k to the hash table
    int key=(strlen(x->word)*strlen(x->word))%k;
    node s=h[key];
    if (s==NULL){
        h[key]=x;
        return;
    }
    node prev=NULL;
    while(s!=NULL){
        if(strcmp(s->word,x->word)==0){
            return;
        }
        prev=s;
        s=s->next;
    }
    prev->next=x;
}

void printHash(node* h, int k){//print contents of the hash table
    for (int i=0;i<k;i++){
        printf("%d:",i);
        node s=h[i];
        if (s==NULL){
            printf("null");
        }
        while(s!=NULL){
            printf("%s",s->word);
            s=s->next;
            if(s!=NULL){
                printf("-");
            }
        }
        printf("\n");
    }
}

void insert(node* h,int k, char*str){//insert preprocessing
    int j=0;
    node x=makeNode();
    for (int i=0;str[i+1]!='\0';i++){
        if (str[i]!=' '){
            x->word[j]=str[i];
            j++;
        }else{
            x->word[j]='\0';
            insertHash(h,k,x);
            x=makeNode();
            j=0;
        }
    }
    insertHash(h,k,x);
}

int main(){
    int k;
    scanf("%d\n",&k);
    node* h=createHash(k);
    char* str=(char*)malloc(500*sizeof(char));
    fgets(str,500,stdin);
    insert(h,k,str);
    printHash(h,k);
    return 0;
}