// gcc ASSG2_B200755CS_ADITHYAN_4.c
// 05-02-2022 ; 0445

#include <stdio.h>
#include <stdlib.h>
typedef char* string;

string* createHash(){//crete a hash table
    string* h=(string*)malloc(1000*sizeof(string));
    for(int i=0;i<1000;i++){
        h[i]=NULL;
    }
    return h;
}

void insertData(string* h,string name){//insert data to hash table
    int k1=0,k2=0,k3=0;
    for(int i=0;name[i]!='\0';i++){
        if(i==0||i==1||i==2){
            k1+=name[i];
        }
        if(i==0||i==2||i==4){
            k2+=name[i];
        }
        if(i==0||i==4||i==8){
            k3+=name[i];
        }
    }
    k1=(k1%26)%10;
    k2=(k2%26)%10;
    k3=(k3%26)%10;
    int key=k1*100+k2*10+k3;
    h[key]=name;
}

void search(string* h, string roll){//search using roll no in hash table
    int key=(roll[1]-'0')*100+(roll[2]-'0')*10+(roll[3]-'0');
    if(h[key]==NULL || h[key][0]!=roll[0]){
        printf("NOT FOUND\n");
    }else{
        for(int i=0;h[key][i]!='\0';i++){
            printf("%c",h[key][i]);
        }
        printf("\n");
    }
}

void delete(string* h, string roll){//delete using roll no in hash table
    int key=(roll[1]-'0')*100+(roll[2]-'0')*10+(roll[3]-'0');
    if(h[key]!=NULL){
        h[key]=NULL;
    }
}

int main(){
    string* h=createHash();
    string name;
    string roll;
    char c;
    while(1){
        scanf("%c",&c);
        switch(c){
            case 'i':
                name=(string)malloc(100*sizeof(char));
                scanf(" %s",name);
                insertData(h,name);
                break;
            case 's':
                roll=(string)malloc(7*sizeof(char));
                scanf(" %s",roll);
                search(h,roll);
                break;
            case 'd':
                roll=(string)malloc(7*sizeof(char));
                scanf(" %s",roll);
                delete(h,roll);
                break;
            case 't':
                return 0;
        }
    }
}