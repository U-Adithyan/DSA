//gcc ASSG3B_B200755CS_ADITHYAN_1.c
//26-02-2022; 1838

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
    int key;
    char c;
    struct node* left;
    struct node* right;
};
typedef struct node* node;

node createNode(int key){
    node x=(node)malloc(sizeof(struct node));
    x->key=key;
    x->c='R';
    x->left=NULL;
    x->right=NULL;
}

void paranthesis(node x){
    printf("( ");
    if(x!=NULL){
        printf("%d ",x->key);
        printf("%c ",x->c);
        paranthesis(x->left);
        paranthesis(x->right);
    }
    printf(") ");
}

node leftRotate(node n){
    node p=n->right;
    n->right=p->left;
    p->left=n;
    return p;
}

node rightRotate(node n){
    node p=n->left;
    n->left=p->right;
    p->right=n;
    return p;
}

char nodeColor(node x){
    if (x==NULL){
        return 'B';
    }
    return x->c;
}

node insertRB(node root, node x){
    int key = x->key;
    if (root==NULL){
        return x;
    }
    if (key > root->key){
        root->right=insertRB(root->right,x);
        if(nodeColor(root->right)=='R'){
            if((nodeColor(root->right->right)=='R')||nodeColor(root->right->left)=='R'){
                if(nodeColor(root->left)=='B'){
                    if(nodeColor(root->right->right)=='R'){
                        node y=leftRotate(root);
                        y->c='B';
                        y->left->c='R';
                        return y;
                    }else{
                        root->right=rightRotate(root->right);
                        node y=leftRotate(root);
                        y->c='B';
                        y->left->c='R';
                        return y;
                    }
                }
                else if (nodeColor(root->left)=='R'){
                    root->left->c='B';
                    root->right->c='B';
                    root->c='R';
                }
            }
        }
    }else{
        root->left = insertRB(root->left, x);
        if (root->left->c=='R'){
            if ((nodeColor(root->left->left) == 'R') || nodeColor(root->left->right) == 'R'){
                if (nodeColor(root->right)=='B'){
                    if (nodeColor(root->left->left) =='R'){
                        node y=rightRotate(root);
                        y->c='B';
                        y->right->c='R';
                        return y;
                    }else{
                        root->left=leftRotate(root->left);
                        node y=rightRotate(root);
                        y->c='B';
                        y->right->c='R';
                        return y;
                    }
                }else if (nodeColor(root->right)=='R'){
                    root->right->c='B';
                    root->left->c='B';
                    root->c='R';
                }
            }
        }
    }
    return root;
}

node insertRedBlack(node root,int key){
    node x=createNode(key);
    root=insertRB(root,x);
    root->c='B';
    paranthesis(root);
    printf("\n");
    return root;
}

int main(){
    int d;
    node root=(node)malloc(sizeof(struct node));
    root=NULL;
    while (1){
        d=0;
        char* s=(char*)malloc(20*sizeof(char));
        scanf("%s",s);
        if(s[0]=='t'){
            return 0;
        }
        for(int i=0;i<strlen(s);i++){
            d=(d*10)+s[i]-'0';
        }
        root=insertRedBlack(root,d);
    }
}