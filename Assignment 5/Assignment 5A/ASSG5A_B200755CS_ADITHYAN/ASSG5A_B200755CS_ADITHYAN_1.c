//gcc ASSG5A_B200755CS_ADITHYAN_1.c
//30-03-2022; 1745

#include <stdio.h>
#include <stdlib.h>

struct node{
    int parent;
    int access;
    int rank;
};
typedef struct node* node;

node makeNode(int k){
    node x=(node)malloc(sizeof(struct node));
    x->parent=k;
    x->access=0;
    x->rank=0;
    return x;
}

void makeSet(node* s,int x){
    s[x]=makeNode(x); 
}

int findSet1(node* s,int k){
    if(s[k]->parent==k){
        s[k]->access+=1;
        return k;
    }
    s[k]->access+=1;
    return findSet1(s,s[k]->parent);
}

int findSet2(node* s,int k){
    if(s[k]->parent==k){
        s[k]->access+=1;
        return k;
    }
    s[k]->access+=1;
    int x=findSet2(s,s[k]->parent);
    s[k]->parent=x;
    return x;
}

int union1(node* s,int x,int y){
    if(s[x]==NULL){
        return findSet1(s,y);
    }
    if(s[y]==NULL){
        return findSet1(s,x);
    }
    int a=findSet1(s,x);
    int b=findSet1(s,y);
    s[b]->parent=a;
    return a;
}

int union2(node* s,int x,int y){
    if(s[x]==NULL){
        return findSet1(s,y);
    }
    if(s[y]==NULL){
        return findSet1(s,x);
    }
    int a=findSet1(s,x);
    int b=findSet1(s,y);
    if (s[a]->rank < s[b]->rank){
        s[a]->parent=b;
        return b;
    }
    if (s[a]->rank == s[b]->rank){
        s[b]->parent=a;
        s[a]->rank++;
        return a;
    }
    s[b]->parent=a;
    return a;
}

int union3(node* s,int x,int y){
    if(s[x]==NULL){
        return findSet2(s,y);
    }
    if(s[y]==NULL){
        return findSet2(s,x);
    }
    int a=findSet2(s,x);
    int b=findSet2(s,y);
    s[b]->parent=a;
    return a;
}

int union4(node* s,int x,int y){
    if(s[x]==NULL){
        return findSet2(s,y);
    }
    if(s[y]==NULL){
        return findSet2(s,x);
    }
    int a=findSet2(s,x);
    int b=findSet2(s,y);
    if (s[a]->rank < s[b]->rank){
        s[a]->parent=b;
        return b;
    }
    if (s[a]->rank == s[b]->rank){
        s[b]->parent=a;
        s[a]->rank++;
        return a;
    }
    s[b]->parent=a;
    return a;
}

int main(){
    node* a=(node*)malloc(10000*sizeof(node));
    node* b=(node*)malloc(10000*sizeof(node));
    node* c=(node*)malloc(10000*sizeof(node));
    node* d=(node*)malloc(10000*sizeof(node));
    for(int i=0;i<=10000;i++){
        a[i]=NULL;
        b[i]=NULL;
        c[i]=NULL;
        d[i]=NULL;
    }
    char ch;
    int x,y;
    int p=0,q=0,r=0,s=0;
    while(1){
        scanf("%c",&ch);
        switch(ch){
            case 'm':
                scanf(" %d",&x);
                if(a[x]!=NULL){
                    printf("-1\n");
                }else{
                    printf("%d\n",x);
                    makeSet(a,x);
                    makeSet(b,x);
                    makeSet(c,x);
                    makeSet(d,x);
                }
                break;
            case 'f':
                scanf(" %d",&x);
                if(a[x]==NULL){
                    printf("-1\n");
                }else{
                    printf("%d ",findSet1(a,x));
                    printf("%d ",findSet1(b,x));
                    printf("%d ",findSet2(c,x));
                    printf("%d\n",findSet2(d,x));
                }
                break;
            case 'u':
                scanf(" %d %d",&x,&y);
                if(a[x]==NULL || a[y]==NULL){
                    printf("-1\n");
                }else{
                    printf("%d ",union1(a,x,y));
                    printf("%d ",union2(b,x,y));
                    printf("%d ",union3(c,x,y));
                    printf("%d\n",union4(d,x,y));
                }
                break;
                break;
            case 's':
                for(int i=0;i<=10000;i++){
                    if(a[i]!=NULL){
                        p+= a[i]->access;
                        q+= b[i]->access;
                        r+= c[i]->access;
                        s+= d[i]->access;
                    }
                }
                printf("%d ",p);
                printf("%d ",q);
                printf("%d ",r);
                printf("%d\n",s);
                return 0;
        }
    }
}