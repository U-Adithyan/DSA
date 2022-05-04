//gcc ASSG3B_B200755CS_ADITHYAN_2.c
//27-02-2022; 1558

#include <stdio.h>
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

int rootDist(node r,node x){
    int d=0;
    if(x==r){
        return 0;
    }
    if(x->key<=r->key){
        return 1+rootDist(r->left,x);
    }else{
        return 1+rootDist(r->right,x);
    }
}

node LCA(node x,int a,int b){
    if (x==NULL){
        return NULL;
    }
    if(x->key==a || x->key==b){
        return x;
    }
    node left=LCA(x->left,a,b);
    node right=LCA(x->right,a,b);

    if (left!=NULL && right!=NULL){
        return x;
    }else if(left!=NULL){
        return left;
    }else{
        return right;
    }
}

int check(node root,node x,node y,int d){
    int c=0;
    if(x!=NULL){
        int dist=rootDist(root,x)+rootDist(root,y)-2*rootDist(root,LCA(root,x->key,y->key));
        if(dist==d && x->c == 'B'){
            c+=1;
        }
        c+=check(root,x->left,y,d);
        c+=check(root,x->right,y,d);
    }
    return c;
}

int beautifulNodes(node root,node x,int d){
    int nodes=0;
    if (x!=NULL){
        if (check(root,root,x,d)>0){
            nodes+=1;
        }
        nodes+=beautifulNodes(root,x->left,d);
        nodes+=beautifulNodes(root,x->right,d);
    }
    return nodes;
}

int main(){
    int x,n,key;
    scanf("%d",&x);
    scanf("%d",&n);
    node root=(node)malloc(sizeof(struct node));
    root=NULL;
    for(int i=0;i<n;i++){
        scanf("%d",&key);
        node x=createNode(key);
        root=insertRB(root,x);
        root->c='B';
    }
    printf("%d\n",beautifulNodes(root,root,x));
}