//gcc ASSG3A_B200755CS_ADITHYAN_1.c
// 22-02-2022; 0447

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

node search(node A,int k){
    if (A==NULL){
        return NULL;
    }
    if (A->key==k){
        return A;
    }else if (A->key>k){
        return search(A->left,k);
    }else{
        return search(A->right,k);
    }
}

void getBalance(node A,int k){
    node x=search(A,k);
    if (x!=NULL){
        printf("%d\n",(height(x->left))-(height(x->right)));
    }else{
        printf("FALSE\n");
    }
}

node leftRotate(node A,int k){
    node n=search(A,k);
    node p=n->right;
    n->right=p->left;
    p->left=n;
    return p;
}

node rightRotate(node A,int k){
    node n=search(A,k);
    node p=n->left;
    n->left=p->right;
    p->right=n;
    return p;
}

node insert(node A,int k){
    if (A==NULL){
        return createNode(k);
    }
    if (k<A->key){
        A->left=insert(A->left,k);
    }else if(k>A->key){
        A->right=insert(A->right,k);
    }else{
        return A;
    }
    int bal=(height(A->left))-(height(A->right));
    if (bal>1){
        if (k > A->left->key){
            A->left=leftRotate(A->left,A->left->key);
        }
        return rightRotate(A,A->key);
    }
    if (bal<-1){
        if (k < A->right->key){
            A->right=rightRotate(A->right,A->right->key);
        }
        return leftRotate(A,A->key);
    }
    return A;
}

node max(node x){
    node s=x;
    while(s->right!=NULL){
        s=s->right;
    }
    return s;
}

node delete(node A,int k){
    if(A==NULL){
        return A;
    }
    if (k<A->key){
        A->left=delete(A->left,k);
    }else if (k>A->key){
        A->right=delete(A->right,k);
    }else{
        if (A->left==NULL && A->right==NULL){
            free(A);
            return NULL;
        }else if (A->left ==NULL){
            node temp=A;
            A=A->right;
            free(temp);
        }else if(A->right==NULL){
            node temp=A;
            A=A->left;
            free(temp);
        }else{
            node predecessor=max(A->left);
            A->key=predecessor->key;
            A->left=delete(A->left,predecessor->key);
        }
    }
    if(A==NULL){
        return NULL;
    }
    int bal=(height(A->left))-(height(A->right));
    if (bal>1){
        if ((height(A->left->left))-(height(A->left->right))<0){
            A->left=leftRotate(A->left,A->left->key);
        }
        return rightRotate(A,A->key);
    }
    if (bal<-1){
        if ((height(A->right->left))-(height(A->right->right))>0){
            A->right=rightRotate(A->right,A->right->key);
        }
        return leftRotate(A,A->key);
    }
    return A;
}

void printTree(node A){
    printf("( ");
    if (A!=NULL){
        printf("%d ",A->key);
        printTree(A->left);
        printTree(A->right);
    }
    printf(") ");
}

int main(){
    node A=NULL;
    node x;
    int d;
    char c;
    while(1){
        scanf("%c",&c);
        switch(c){
            case 'i':
                scanf(" %d",&d);
                A=insert(A,d);
                break;
            case 'd':
                scanf(" %d",&d);
                x=search(A,d);
                if (x!=NULL){
                    printf("%d\n",x->key);
                }else{
                    printf("FALSE\n");
                }
                A=delete(A,d);
                break;
            case 's':
                scanf(" %d",&d);
                x=search(A,d);
                if (x!=NULL){
                    printf("TRUE\n");
                }else{
                    printf("FALSE\n");
                }
                break;
            case 'b':
                scanf(" %d",&d);
                getBalance(A,d);
                break;
            case 'p':
                printTree(A);
                printf("\n");
                break;
            case 'e':
                return 0;
        }
    }
}