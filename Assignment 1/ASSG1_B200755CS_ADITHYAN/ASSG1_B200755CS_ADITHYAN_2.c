//gcc ASSG1_B200755CS_ADITHYAN_2.c
//06-01-2021 ;0500

#include<stdio.h>
#include<stdlib.h>

struct node{
    int key;
    struct node* left;
    struct node* right;
    struct node* p;
};
typedef struct node* node;

struct tree{
    node root;
};
typedef struct tree* tree;

node createNode(long int k){//create a node
    node x=(node)malloc(sizeof(struct node));
    x->key=k;
    x->left=NULL;
    x->p=NULL;
    x->right=NULL;
    return x;
}

void insert(tree t,node x){//insert node to bst
    node y=NULL;
    node z=t->root;
    while(z!=NULL){
        y=z;
        if(x->key<z->key){
            z=z->left;
        }else{
            z=z->right;
        }
    }
    x->p=y;
    if(y==NULL){
        t->root=x;
    }else{
        if(x->key<y->key){
            y->left=x;
        }else{
            y->right=x;
        }
    }
}

void replace(tree t,node a,node b){//replace node a with b
    if(a->p==NULL){
        t->root=b;
    }else if(a==a->p->left){
        a->p->left=b;
    }else{
        a->p->right=b;
    }
    if(b!=NULL){
        b->p=a->p;
    }
}

node minValue(node x){//find min key value of bst
    while(x->left!=NULL){
        x=x->left;
    }
    return x;
}

void delete(tree t,node x){//delete node x from bst
    if(x==NULL){
        printf("-1\n");
    }else{
        printf("%ld\n",x->key);
        if(x->left==NULL){
            replace(t,x,x->right);
        }else if(x->right==NULL){
            replace(t,x,x->left);
        }else{
            node y=minValue(x->right);
            if(y->p!=x){
                replace(t,y,y->right);
                y->right=x->right;
                y->right->p=x;
            }
            replace(t,x,y);
            y->left=x->left;
            y->left->p=y;
        }
    }
}

node search(tree t,long int k){//search for node with key k
    tree x=(tree)malloc(sizeof(struct tree));
    x->root=NULL;
    if(t->root==NULL){
        return NULL;
    }
    if(t->root->key==k){
        return t->root;
    }
    if(t->root->key>k){
        x->root=t->root->left;
        return search(x,k);
    }
    if(t->root->key<k){
        x->root=t->root->right;
        return search(x,k);
    }
}

long int level(tree t,long int k){//search for level of node with key k
    int lvl=1;
    node x=t->root;
    while(x->key!=k){
        lvl+=1;
        if (k<x->key){
            x=x->left;
        }
        else{
            x=x->right;
        }
        if(x==NULL){
            return -1;
        }
    }
    return lvl;
}

node maxValue(node x){//find max key valued node
    while(x->right!=NULL){
        x=x->right;
    }
    return x;
}

node successor(tree t,node x){//find sucessor of node x in bst
    if(x->right!=NULL){
        return minValue(x->right);
    }else{
        node z=x;
        node y=z->p;
        while(y!=NULL && z==y->right){
            z=y;
            y=y->p;
        }
        return y;
    }
}

node predecessor(tree t,node x){//find predecessor of node x in bst
    if(x->left!=NULL){
        return maxValue(x->left);
    }else{
        node z=x;
        node y=z->p;
        while(y!=NULL && z==y->left){
            z=y;
            y=y->p;
        }
        return y;
    }
}

void inorder(tree t){//print bst inorder
    tree x=(tree)malloc(sizeof(struct tree));
    if(t->root!=NULL){
        x->root=t->root->left;
        inorder(x);
        printf("%ld ",t->root->key);
        x->root=t->root->right;
        inorder(x);
    }
}

void preorder(tree t){//print bst preorder
    tree x=(tree)malloc(sizeof(struct tree));
    if(t->root!=NULL){
        printf("%ld ",t->root->key);
        x->root=t->root->left;
        preorder(x);
        x->root=t->root->right;
        preorder(x);
    }
}

void postorder(tree t){//print bst postorder
    tree x=(tree)malloc(sizeof(struct tree));
    if(t->root!=NULL){
        x->root=t->root->left;
        postorder(x);
        x->root=t->root->right;
        postorder(x);
        printf("%ld ",t->root->key);
    }
}

int main(){
    tree t=(tree)malloc(sizeof(struct tree));
    t->root=NULL;

    char c;
    long int k;
    node x;

    while(1){
        scanf("%c",&c);
        switch(c){
        case 'a':
            scanf(" %ld",&k);
            x=createNode(k);
            insert(t,x);
            break;
        case 'd':
            scanf(" %ld",&k);
            x=search(t,k);
            delete(t,x);
            break;
        case 's':
            scanf(" %ld",&k);
            x=search(t,k);
            if(x!=NULL){
                printf("1\n");
            }else{
                printf("-1\n");
            }
            break;
         case 'l':
            scanf(" %ld",&k);
            k=level(t,k);
            printf("%d\n",k);
            break;
        case 'm':
            if(t->root!=NULL){
                x=minValue(t->root);
                printf("%ld\n",x->key);
            }
            break;
        case 'x':
            if(t->root!=NULL){
                x=maxValue(t->root);
                printf("%ld\n",x->key);
            }
            break;
        case 'r':
            scanf(" %ld",&k);
            x=search(t,k);
            if (x!=NULL){
                x=predecessor(t,x);
            }
            if(x!=NULL){
                printf("%ld\n",x->key);
            }else{
                printf("-1\n");
            }
            break;
        case 'u':
            scanf(" %ld",&k);
            x=search(t,k);
            if(x!=NULL){
                x=successor(t,x);
            }
            if(x!=NULL){
                printf("%ld\n",x->key);
            }else{
                printf("-1\n");
            }
            break;
        case 'i':
            inorder(t);
            printf("\n");
            break;
        case 'p':
            preorder(t);
            printf("\n");
            break;
        case 't':
            postorder(t);
            printf("\n");
            break;
        case 'e':
            return 0;
        }
    }
    return 0;
}