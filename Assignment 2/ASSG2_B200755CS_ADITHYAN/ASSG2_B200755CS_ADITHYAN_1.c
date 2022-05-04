// gcc ASSG2_B200755CS_ADITHYAN_1.c
// 03-02-2022 ; 0445

#include <stdio.h>
#include <stdlib.h>

int* hashTable(int m){//create hash table
    int* h = (int*)malloc(m*sizeof(int));
    for (int i=0; i<m; i++){
        h[i] = -1;
    }
    return h;
}

int bigPrime(int m){//find biggest prime less than m
    int ans,flag,n=2;
    while(n<m){
        flag=0;
        for(int i=2;i<(n/2);i++){
            if(n%i==0){
                flag=1;
            }
        }
        if (flag==0){
            ans=n;
        }
        n++;
    }
    return ans;
}

void insert(int* t,int k,char z,int c1,int c2,int m){//insert k into hash table
    int h;
    for(int i=0;i<m;i++){
        if(z=='a'){
            h=((k%m)+(c1*i)+(c2*i*i))%m;
        }else if(z=='b'){
            int r=bigPrime(m);
            h=((k%m)+i*(r-(k%r)))%m;
        }
        if (t[h]==-1 || t[h]==-5){
            t[h]=k;
            return;
        }
    }
}

void search(int* t,int k,char z,int c1,int c2,int m){//search for k in hash table
    int h;
    for(int i=0;i<m;i++){
        if(z=='a'){
            h=((k%m)+(c1*i)+(c2*i*i))%m;
        }else if(z=='b'){
            int r=bigPrime(m);
            h=((k%m)+i*(r-(k%r)))%m;
        }
        if (t[h]==k){
            printf("1\n");
            return;
        }
        else if(t[h]==(-1)){
            printf("-1\n");
            return;
        }
    }
    printf("-1\n");
}

void delete(int* t,int k,char z,int c1,int c2,int m){//delete k from hash
    int h;
    for(int i=0;i<m;i++){
        if(z=='a'){
            h=((k%m)+(c1*i)+(c2*i*i))%m;
        }else if(z=='b'){
            int r=bigPrime(m);
            h=((k%m)+i*(r-(k%r)))%m;
        }
        if (t[h]==-1){
            return;
        }else if (t[h]==k){
            t[h]=-5;
            return;
        }
    }
}

void print(int* t,int m){//print contents of hash
    for (int i=0;i<m;i++){
        printf("%d (",i);
        if (t[i]!=-1 && t[i]!=-5){
            printf("%d",t[i]);
        }
        printf(")\n");
    }
}

int main(){
    char z,x;
    scanf("%c",&z);
    int m,c1,c2,key;
    scanf("%d",&m);
    int* t=hashTable(m);
    if (z=='a'){
        scanf("%d %d",&c1,&c2);
    }else{
        c1=0;
        c2=0;
    }
    while(1){
        scanf("%c",&x);
        switch (x){
            case 'i':
                scanf(" %d",&key);
                insert(t,key,z,c1,c2,m);
                break;
            case 's':
                scanf(" %d",&key);
                search(t,key,z,c1,c2,m);
                break;
            case 'd':
                scanf(" %d",&key);
                delete(t,key,z,c1,c2,m);
                break;
            case 'p':
                print(t,m);
                break;
            case 't':
                return 0;
        }
    }
}