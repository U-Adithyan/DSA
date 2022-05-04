//gcc ASSG1MOD_B200755CS_ADITHYAN.c

#include<stdio.h>
#include<stdlib.h>

struct node{
    int key;
    struct node* left;
    struct node* right;
    struct node* p;
    int visit;
};
typedef struct node* node;

struct tree{
    node root;
};
typedef struct tree* tree;

int findEnd(char* str,int start){
    int i=start;
    int k=0;
    while(str[i]!='\0'){
        if(str[i]=='('){
            k=k+1;
        }
        else if(str[i]==')'){
            k=k-1;
        }
        if(k==0){
            return i;
        }
        i=i+1;
    }
}

node makeTree(char* s,int start,int end){
    if (end==start+2){
        return NULL;
    }else{
        node x=(node)malloc(sizeof(struct node));
        x->key=0;
        x->visit=0;

        int flag=0;
        int i=start+2;
        if(s[i]=='-'){
            flag=1;
            i+=1;
        }
        while(s[i]!=' '){
            x->key=(x->key)*10+(s[i]-48);
            i=i+1;
        }
        if (flag==1){
            x->key=((x->key)*(-1));
        }

        int a=i+1;
        int b=findEnd(s,a);
        x->left=makeTree(s,a,b);
        if(x->left!=NULL){
            x->left->p=x;
        }

        a=b+2;
        b=findEnd(s,a);
        x->right=makeTree(s,a,b);
        if(x->right!=NULL){
            x->right->p=x;
        }
        return x;
    }
}

node searchNode(node x,int key){
    if (x==NULL){
        return NULL;
    }
    if(x->key==key){
        return x;
    }
    node l=searchNode(x->left,key);
    if(l!=NULL){
        return l;
    }
    l=searchNode(x->right,key);
    return l;
}

int findSum(node x,int k){
    if(x==NULL || k<0){
        return 0;
    }
    if(x->visit==1){
        return 0;
    }
    int ans=x->key;
    x->visit=1;
    ans+=findSum(x->p,k-1);
    ans+=findSum(x->left,k-1);
    ans+=findSum(x->right,k-1);
    return ans;
}


int main(){
    char* str=(char*)malloc(10000*sizeof(char));
    fgets(str,10000,stdin);
    int end=findEnd(str,0);
    tree t=(tree)malloc(sizeof(struct tree));
    t->root=makeTree(str,0,end);
    t->root->p=NULL;

    int s,k;
    scanf("%d %d",&s,&k);
    node start=searchNode(t->root,s);

    s=findSum(start,k);
    printf("%d",s);

    return 0;
}