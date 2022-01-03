#include<stdio.h>
#include<stdlib.h>

struct node{//struct representing each node of the linked list
    long int key;
    struct node* next;
};
typedef struct node* node;

struct ll{//struct to the linked list
    node head;//pointer to first node of the linked list
};
typedef struct ll* list;

node createNode(long int a){//function to create a node with the given key
    node p;
    p=(node)malloc(sizeof(struct node));
    p->key=a;
    p->next=NULL;
    return p;
}

void listInsert(list l,node x){//function to add a node at the end of the list
    node s;
    s=l->head;
    if(s==NULL){
        l->head=x;//check to see if the only element
    }else{
        while((s->next)!=NULL){
            s=s->next;
        }
        s->next=x;
    }
}

void createList(char* str,list l){//make a linked list from the string of space separated integers
    long int i=0,flag=0,key;
    char c;
    while((c=str[i++])!='\n'){
        if(c!=' '){
            if(flag==0){
                key=c-48;
                flag=1;
            }else{
                key=(key*10)+(c-48);
            }
        }else{
            node x=createNode(key);
            listInsert(l,x);
            flag=0;
        }
    }
    node x=createNode(key);
    listInsert(l,x);
}

node kLast(list l,long int k){//find the Kth last node in the linked list
    node start=l->head;
    for (int i=0;i<k;i++){
        if (start==NULL){
            return start;
        }
        start=start->next;
    }
    node ans=l->head;
    while(start!=NULL){
        ans=ans->next;
        start=start->next;
    }
    free(start);
    return ans;
}

int main(){
    list l=(list)malloc(sizeof(list));//initialising linked list
    l->head=NULL;

    char* str=(char*)malloc(10000*sizeof(char));//insitailise string
    fgets(str,10000,stdin);//input

    createList(str,l);//creating list

    int k;
    scanf("%ld",&k);//input k
    node x=kLast(l,k);
    if (x==NULL){
        printf("-1\n");//not available condition
    }else{
        printf("%ld\n",x->key);//printing ans
    }
    return 0;
}