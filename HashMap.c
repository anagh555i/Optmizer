#include "HashMap.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

mapNode* createMap(){
    mapNode* ptr=(mapNode*)malloc(sizeof(mapNode)); 
    ptr->next=NULL;
    return ptr;
}

mapNode* insertMap(char* a,char op,char* b,int tNo,mapNode* next){
    mapNode* ptr=(mapNode*)malloc(sizeof(mapNode));
    ptr->a=a;
    ptr->op=op;
    ptr->b=b;
    ptr->tNo=tNo;
    ptr->next=next;
    return ptr;
}

void removeMap(char* a, mapNode* map){
    while(map->next){
        if(strcmp(map->next->a,a)==0 || strcmp(map->next->b,a)==0) map->next=map->next->next;
        else map=map->next;
    }
}

int lookUpMap(char* a,char op,char* b){
    while(map->next){
        if(strcmp(map->next->a,a)==0 || strcmp(map->next->b,b)==0 && op==map->next->op) return map->next->tNo;
        map=map->next;
    }
    return -1;
}