//gcc ASSG4_B200755CS_ADITHYAN_1.c

#include <stdio.h>
#include <stdlib.h>

struct node{
    int key;
    int degree;
    struct node* parent;
    struct node* child;
    struct node* sibling;
};
typedef struct node* node;

struct heap{
    struct node* head;
};
typedef struct heap* heap;

heap makeHeap(){
    heap h=(heap)malloc(sizeof(struct heap));
    h->head=NULL;
    return h;
}

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

void enqueue(queue q,node x){
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

node dequeue(queue q){
    qnode x=q->head;
    q->head=x->next;
    x->next=NULL;
    return x->k; 
}

node makeNode(int k){
    node x=(node)malloc(sizeof(struct node));
    x->key=k;
    x->degree=0;
    x->parent=NULL;
    x->sibling=NULL;
    x->child=NULL;
    return x;
}

int minimum(heap h){
    node x=h->head;
    int min=x->key;
    while(x!=NULL){
        if (x->key < min){
            min=x->key;
        }
        x=x->sibling;
    }
    return min;
}

void link(node y, node x){
    y->parent=x;
    y->sibling=x->child;
    x->child=y;
    x->degree=x->degree+1;
}

node binomialHeapMerge(heap h1,heap h2){
    node x=h1->head;
    node y=h2->head;
    if (x==NULL){
        return y;
    }
    if (y==NULL){
        return x;
    }
    node h=NULL;
    node z=NULL;
    if (x->degree>y->degree){
        z=y;
        y=y->sibling;
    }else{
        z=x;
        x=x->sibling;
    }
    h=z;
    while (x!=NULL && y!=NULL){
        if (x->degree>y->degree){
            z->sibling=y;
            y=y->sibling;
        }else{
            z->sibling=x;
            x=x->sibling;
        }
        z=z->sibling;
    }
    if (x!=NULL){
        z->sibling=x;
    }
    if (y!=NULL){
        z->sibling=y;
    }
    return h;
}

heap Union(heap h1,heap h2){
    heap h=makeHeap();
    h->head=binomialHeapMerge(h1,h2);
    h1->head=NULL;
    h2->head=NULL;
    if (h->head==NULL){
        return h;
    }
    node prev=NULL;
    node x=h->head;
    node next=x->sibling;
    while (next!=NULL){
        if ((x->degree!=next->degree)||((next->sibling !=NULL)&&(next->sibling->degree==x->degree))){
            prev=x;
            x=next;
        }else{
            if(x->key<next->key){
                x->sibling=next->sibling;
                link(next,x);
            }else{
                if (prev==NULL){
                    h->head=next;
                }else{
                    prev->sibling=next;
                }
                link(x,next);
                x=next;
            }
        }
        next=x->sibling;
    }
    return h;    
}

heap insert(heap h,int x){
    node n=makeNode(x);
    heap h1=makeHeap();
    h1->head=n;
    h=Union(h,h1);
    return h;
}

void print(heap h){
    queue q=(queue)malloc(sizeof(struct queue));
    q->head=NULL;
    enqueue(q,h->head);
    while(q->head!=NULL){
        node y=dequeue(q);
        while(y!=NULL){
            printf("%d ",y->key);
            if (y->child!=NULL){
                enqueue(q,y->child);
            }
            y=y->sibling;
        }
    }
}

node search(node x, int k){
    if (x==NULL){
        return NULL;
    }
    if (x->key==k){
        return x;
    }
    node y=search(x->child,k);
    if(y!=NULL){
        return y;
    }
    return search(x->sibling,k);
}

void decreaseKey(heap h,int x,int k){
    node y=search(h->head,x);
    if (k>x || y==NULL){
        printf("-1\n");
    }else{
        node z=y->parent;
        y->key=y->key-k;
        printf("%d\n",y->key);
        while(z!=NULL && z->key<y->key){
            int temp=z->key;
            z->key=y->key;
            z->key=temp;
            y=z;
            z=z->parent;
        }
    }
}

node reverse (node x){
    node prev=NULL;
    node next=NULL;
    while (x!=NULL){
        next=x->sibling;
        x->sibling=prev;
        prev=x;
        x=next;
    }
    return prev;
}

heap extractMin(heap h){
    node x=h->head;
    node prev=NULL;
    node min=x;
    while(x->sibling!=NULL){
        if (x->sibling->key < min->key){
            prev=x;
            min=x->sibling;
        }
        x=x->sibling;
    }
    if (prev!=NULL){
        prev->sibling=min->sibling;
    }else{
        h->head=min->sibling;
    }
    printf("%d\n",min->key);
    heap h1=makeHeap();
    h1->head=reverse(min->child);
    x=h->head;
    while(x!=NULL){
        x->parent=NULL;
        x=x->sibling;
    }
    h=Union(h,h1);
    return h;
}

heap delete(heap h,int x){
    node y=search(h->head,x);
    if (y==NULL){
        printf("-1\n");
        return h;
    }
    printf("%d\n",x);
    node z=y->parent;
    y->key=-1000001;
    while(z!=NULL && z->key<y->key){
        int temp=z->key;
        z->key=y->key;
        z->key=temp;
        y=z;
        z=z->parent;
    }
    node p=h->head;
    node prev=NULL;
    node min=p;
    while(p->sibling!=NULL){
        if (p->sibling->key < min->key){
            prev=p;
            min=p->sibling;
        }
        p=p->sibling;
    }
    if (prev!=NULL){
        prev->sibling=min->sibling;
    }else{
        h->head=min->sibling;
    }
    heap h1=makeHeap();
    h1->head=reverse(min->child);
    h=Union(h,h1);
    return h;
}


int main(){
    heap h=makeHeap();
    int d,k;
    node min;
    char c;
    while(1){
        scanf("%c",&c);
        switch(c){
            case 'i':
                scanf(" %d",&d);
                h=insert(h,d);
                break;
            case 'd':
                scanf(" %d",&d);
                h=delete(h,d);
                break;
            case 'p':
                print(h);
                printf("\n");
                break;    
            case 'm':
                printf("%d\n",minimum(h));
                break;
            case 'x':
                h=extractMin(h);
                break;
            case 'r':
                scanf(" %d",&d);
                scanf(" %d",&k);
                decreaseKey(h,d,k);
                break;
            case 'e':
                return 0;
        }
    }
}