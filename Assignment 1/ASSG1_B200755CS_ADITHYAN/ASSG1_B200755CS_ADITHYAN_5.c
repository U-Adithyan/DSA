//gcc ASSG1_B200755CS_ADITHYAN_5.c
//09-01-2021 ;1020

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
    long int key;
    struct node* left;
    struct node* right;
    struct node* p;
};
typedef struct node* node;

struct tree{
    node root;
};
typedef struct tree* tree;

int findEnd(char* str,int start){//to find index of the corresponding )
    int i=start;
    int k=0;
    while(str[i]!='\0'){
        if(str[i]=='('){
            k=k+1;
        }
        else if(str[i]==')'){
            k=k-1;
        }
        if(k==0){
            return i;
        }
        i=i+1;
    }
}

node makeTree(char* s,int start,int end){//to make bst from paranthesis form
    if (end==start+2){
        return NULL;
    }else{
        node x=(node)malloc(sizeof(struct node));
        x->key=0;

        int flag=0;
        int i=start+2;
        if(s[i]=='-'){
            flag=1;
            i+=1;
        }
        while(s[i]!=' '){
            x->key=(x->key)*10+(s[i]-48);
            i=i+1;
        }
        if (flag==1){
            x->key=((x->key)*(-1));
        }

        int a=i+1;
        int b=findEnd(s,a);
        x->left=makeTree(s,a,b);
        if(x->left!=NULL){
            x->left->p=x;
        }

        a=b+2;
        b=findEnd(s,a);
        x->right=makeTree(s,a,b);
        if(x->right!=NULL){
            x->right->p=x;
        }
        return x;
    }
}

long int largestBst(node x,int* p){//to find size of largest bst within the tree
    if (x==NULL){
        return 0;
    }
    int b=1;
    int a;
    a=largestBst(x->left,p);
    if (x->left!=NULL && (x->left->key)<=(x->key)){
        b+=a;
    }
    a=largestBst(x->right,p);
    if (x->right!=NULL && (x->right->key)>=(x->key)){
        b+=a;
    }
    if (b>(*p)){
        *p=b;
    }
    return b;
}

int main(){
    char* str=(char*)malloc(10000*sizeof(char));
    fgets(str,10000,stdin);


    int end=findEnd(str,0);

    tree t=(tree)malloc(sizeof(struct tree));
    t->root=makeTree(str,0,end);
    t->root->p=NULL;

    int* p=(int*)malloc(sizeof(int));
    *p=0;
    long int i=largestBst(t->root,p);

    printf("%d",(*p));

    return 0;
}