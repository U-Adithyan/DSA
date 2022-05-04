//gcc ASSG2_Mod_B200755CS_Adithyan.c

#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

struct node{
    char* name;
    struct node* next;
};
typedef struct node* node;

int findIndex(char* name,int n){
    int index=0,m;
    for(int i=0;name[i]!='\0';i++){
        if(name[i]>='a' && name[i]<='z'){
            m=name[i];
            index=index+((m+1)-'a')*pow(3,i);
        }
        if(name[i]>='A' && name[i]<='Z'){
            m=name[i];
            index=index+((m+1)-'A')*pow(3,i);
        }
    }
    index=index%n;
    return index;
}

node createNode(char* name){
    node x=(node)malloc(sizeof(struct node));
    x->name=name;
    x->next=NULL;
}

void insert(node* h,int n,char* name){
    int id=findIndex(name,n);
    node x=createNode(name);
    x->next=h[id];
    h[id]=x;
}

void delete(node* h,int n,char* name){
    int id=findIndex(name,n);
    node s=h[id];
    if (s==NULL){
        return;
    }
    node p=NULL;
    while(strcmp(s->name,name)!=0){
        p=s;
        s=s->next;
    }
    if (p==NULL){
        h[id]=NULL;
        return;
    }
    p->next=s->next;
    free(s);
}

int check(node* h,int n){
    for (int i=0;i<n;i++){
        if(h[i]!=NULL && h[i]->next!=NULL){
            return -1;
        }
    }
    return 1;
}

int main(){
    int n,ans;
    char c;
    char* name;
    scanf("%d",&n);
    node* h=(node*)malloc(n*sizeof(node));
    for (int i=0;i<n;i++){
        h[i]=NULL;
    }
    while(1){
        scanf("%c",&c);
        switch(c){
            case 'i':
                name=(char*)malloc(50*sizeof(char));
                scanf(" %s",name);
                insert(h,n,name);
                break;
            case 'd':
                name=(char*)malloc(50*sizeof(char));
                scanf(" %s",name);
                delete(h,n,name);
                break;
            case 'p':
                ans=check(h,n);
                printf("%d\n",ans);
                break;
            case 't':
                return 0;
        }
    }
    return 0;
}