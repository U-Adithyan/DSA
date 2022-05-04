//gcc ASSG3A_B200755CS_ADITHYAN_2.c
// 22-02-2022; 0407

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct node{
int key ;
struct node* left;
struct node* right;
};
typedef struct node* node;


node createNode(int k){
    node x=(node)malloc(sizeof(struct node));
    x->key=k;
    x->left=NULL;
    x->right=NULL;
    return x;
}


node insert(node root,node x){
    node y=NULL;
    node z=root;
    while(z!=NULL){
        y=z;
        if(x->key<z->key){
            z=z->left;
        }else{
            z=z->right;
        }
    }
    if(y==NULL){
        root=x;
    }else{
        if(x->key<y->key){
            y->left=x;
        }else{
            y->right=x;
        }
    }
    return root;
}

int height(node x){
    if(x==NULL){
        return 0;
    }
    int hl=height(x->left);
    int hr=height(x->right);
    if (hl>hr){
        return 1+hl;
    }
    return 1+hr;
}

int isAVL(node root){
    if (root==NULL){
        return 1;
    }
    int hl=height(root->left);
    int hr=height(root->right);
    if (abs(hl-hr)<=1 && isAVL(root->left) && isAVL(root->right)){
        return 1;
    }else{
        return 0;
    }
}

int main(){
    char c;
    int d;
    node root=NULL;
    while(1){
        scanf("%c",&c);
        switch(c){
            case 'i':
                scanf(" %d",&d);
                node x=createNode(d);
                root=insert(root,x);
                break;
            case 'c':
                printf("%d\n",isAVL(root));
                break;
            case 't':
                return 0;
        }
    }
}