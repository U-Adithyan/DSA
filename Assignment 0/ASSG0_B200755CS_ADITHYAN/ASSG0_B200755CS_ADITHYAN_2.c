//gcc ASSG0_B200755CS_ADITHYAN_2.c
//created on 02/01/2022;0955
#include<stdio.h>
#include<stdlib.h>

struct q{//structure defining the queue
    long int n;
    long int head;
    long int tail;
    long int* a;
};
typedef struct q* queue;


int isFull(queue q){//function to check if the queue is full
    if ((q->tail==(q->n))){
        return 1;
    }
    return -1;
}

int isEmpty(queue q){//function to check if queue is empty
    if(q->head==q->tail){
        return 1;
    }
    return -1;
}

void enqueue(queue q,long int x){//function to add an element to the queue
    if(isFull(q)==1){
        printf("1\n");
    }else{
        q->a[q->tail]=x;
        q->tail+=1;
    }
}

void dequeue(queue q){//function to remove an element from the queue
    if(isEmpty(q)==1){
        printf("1\n");
    }else{
        long int x;
        x=q->a[q->head];
        printf("%ld\n",x);
        q->head+=1;
    }
}

int main(){
    queue q;
    q=(queue)malloc(sizeof(struct q));//initialising the queue
    scanf("%d",&(q->n));//scaniing queue size
    q->head=0;
    q->tail=0;
    q->a=(long int*)malloc((q->n)*sizeof(long int));//initialising array

    char ch;
    long int x;

    while(1){
        scanf("%c",&ch);
        switch (ch){
            case 'i'://add a string to the queue
                scanf(" %ld",&x);
                enqueue(q,x);                
                break;
            case 'd'://remove an element from the queue
                dequeue(q);
                break;
            case 'f'://check if the queue is full
                printf("%d\n",isFull(q));
                break;
            case 'e'://check if queue is empty
                printf("%d\n",isEmpty(q));
                break;
            case 't'://exit call
                return 0;
        }
    }
}