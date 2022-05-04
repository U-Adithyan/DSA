//gcc ASSG1_B200755CS_ADITHYAN_1.c
//05-01-2021 ;1821

#include<stdio.h>
#include<stdlib.h>

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

struct qnode{
    node k;
    struct qnode* next;
};
typedef struct qnode* qnode;

struct queue{
    struct qnode* head;
    struct qnode* tail;
};
typedef struct queue* queue;

node createNode(long int k){//create node
    node x=(node)malloc(sizeof(struct node));
    x->key=k;
    x->left=NULL;
    x->p=NULL;
    x->right=NULL;
    return x;
}

void enqueue(queue q,node x){//add to queue
    qnode z=(qnode)malloc(sizeof(struct qnode));
    z->k=x;
    z->next=NULL;
    if (q->head==NULL){
        q->head=z;
        q->tail=z;
        return;
    }
    q->tail->next=z;
    q->tail=z;
}

node dequeue(queue q){//delete from queue
    qnode x=q->head;
    q->head=x->next;
    x->next=NULL;
    return x->k; 
}

void insert(tree t,node x){//insert to tree on level order
    if (t->root==NULL){
        t->root=x;
    }else{
        queue q=(queue)malloc(sizeof(struct queue));
        q->head=NULL;
        enqueue(q,t->root);
        while(q->head!=NULL){
           node y=dequeue(q);
           if (y->left!=NULL){
               enqueue(q,y->left);
           }else{
               y->left=x;
               x->p=y;
               return;
           }
           if (y->right!=NULL){
               enqueue(q,y->right);
           }else{
               y->right=x;
               x->p=y;
               return;
           }
        }
    }

}

void print(tree t){//print paranthesis form
    tree x=(tree)malloc(sizeof(struct tree));
    
    printf("( ");
    if(t->root!=NULL){
        printf("%ld ",t->root->key);
        x->root=t->root->left;
        print(x);
        x->root=t->root->right;
        print(x);
    }
    printf(") ");
}

int main(){
    tree t=(tree)malloc(sizeof(struct tree));
    t->root=NULL;

    char c;
    long int k;

    while(1){
        scanf("%c",&c);
        switch(c){
        case 'i':
            scanf(" %ld",&k);
            node x=createNode(k);
            insert(t,x);
            break;
        case 'p':
            print(t);
            printf("\n");
            break;
        case 'e':
            return 0;
        }
    }
}