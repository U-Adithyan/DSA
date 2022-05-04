// gcc ASSG2_B200755CS_ADITHYAN_3.c
// 04-02-2022 ; 1746

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
    int age;
    char* firstName;
    char* lastName;
    struct node* left;
    struct node* right;
    struct node* p;
};
typedef struct node* node;

node* createHash(){//create hash table
    node* h=(node*)malloc(128*sizeof(node));
    for(int i=0;i<128;i++){
        h[i]=NULL;
    }
    return h;
}

node createNode(char* firstName,char* lastName,int age){//create the bst node
    node x=(node)malloc(sizeof(struct node));
    x->age=age;
    x->firstName=(char*)malloc(100*sizeof(char));
    x->lastName=(char*)malloc(100*sizeof(char));
    strcpy(x->firstName,firstName);
    strcpy(x->lastName,lastName);
    x->left=NULL;
    x->right=NULL;
    x->p=NULL;
    return x;
}

void insert(node* h,int key,node x){//insert node x to the bst rooted at h
    node y=NULL;
    node z=h[key];
    while(z!=NULL){
        y=z;
        if(x->age<z->age){
            z=z->left;
        }else{
            z=z->right;
        }
    }
    x->p=y;
    if(y==NULL){
        h[key]=x;
    }else{
        if(x->age<y->age){
            y->left=x;
        }else{
            y->right=x;
        }
    }
}

void insertData(node* h,char* firstName,char* lastName,int age){//function to insert to hashtable
    int key=0;
    for (int i=0;lastName[i]!='\0';i++){
        key+=lastName[i];
    }key=key%128;
    node x=createNode(firstName,lastName,age);
    insert(h,key,x);
}

node find(node x,char* first){//preorder search in bst
    if(x==NULL){
        return NULL;
    }else if(strcmp(x->firstName,first)==0){
        return x;
    }else{
        node y=find(x->left,first);
        if(y!=NULL){
            return y;
        }else{
            return find(x->right,first);
        }
    }
}

void print(node h,node x){//print the relatives of x
    printf("%s %s %d\n",h->firstName,h->lastName,h->age);
    if(h!=x){
        if (h->age>x->age){
            print(h->left,x);
        }else{
            print(h->right,x);
        }
    }
}

void printRelatives(node* h,char* first,char* last){//print relative preprocessing
    int key=0;
    for (int i=0;last[i]!='\0';i++){
        key+=last[i];
    }key=key%128;
    node x=find(h[key],first);
    if(x==NULL){
        printf("-1\n");
    }else{
        print(h[key],x);
    }
}

int main(){
    char c;
    char* first=(char*)malloc(100*sizeof(char));
    char* last=(char*)malloc(100*sizeof(char));
    int age;
    node* h=createHash();
    while(1){
        scanf("%c",&c);
        switch(c){
            case 'i':
                scanf(" %s",first);
                scanf(" %s",last);
                scanf(" %d",&age);
                insertData(h,first,last,age);
                break;
            case 'p':
                scanf(" %s",first);
                scanf(" %s",last);
                printRelatives(h,first,last);
                break;
            case 't':
                return 0;
        }
    }
    
    return 0;
}