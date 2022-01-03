//gcc ASSG0_B200755CS_ADITHYAN_1.c
//created on 02/01/2022;0915

#include<stdio.h>
#include<stdlib.h>

struct s{//structure representing the stack
    long int n;
    long int top;
    long int* a;
};
typedef struct s* stack;

int isFull(stack s){//check to see if struct is fully filled
    if(s->top==s->n){
        return 1;
    }else{
        return 0;
    }
}

int isEmpty(stack s){//check to see if stack is empty 
    if((s->top)==0){
        return 1;
    }else{
        return 0;
    }
}

void push(stack s,long int x){//push an element in to the stack
    if(isFull(s)){
        long int* b=(long int*)malloc(2*(s->n)*sizeof(long int));
        for(int i=0;i<(s->n);i++){
            b[i]=s->a[i];
        }
        (s->n)*=2;
        s->a=b;
        s->a[s->top]=x;
        s->top+=1;
        printf("1\n");
    }else{
        s->a[s->top]=x;
        s->top+=1;
    }
}

void pop(stack s){//pop an element out of the stack
    if(isEmpty(s)){
        printf("-1\n");
    }else{
        printf("%ld\n",s->a[s->top-1]);
        (s->top)=(s->top)-1;
    }
}


int main(){
    
    stack s;
    s=(stack)malloc(sizeof(struct s));//stack initialisation
    scanf("%ld",&(s->n));//taking the size of the stack
    s->a=(long int*)malloc((s->n)*sizeof(long int));//array initilaisation
    s->top=0;

    char ch;
    long int d;

    while(1){
        scanf("%c",&ch);
        switch(ch){
            case 'i'://push function
                scanf(" %ld",&d);
                push(s,d);
                break;
            case 'd'://pop function
                pop(s);
                break;
            case 't'://termination
                return 0;
        }
    }
}