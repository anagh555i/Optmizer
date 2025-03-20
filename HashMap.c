#include "HashMap.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

mapNode* createMap(){
    mapNode* ptr=(mapNode*)malloc(sizeof(mapNode)); 
    ptr->next=NULL;
    ptr->x=strdup("NULL");
    return ptr;
}

void freeMap(){
    mapNode* ptr=hash;
    while(hash->next){
        ptr=hash->next;
        hash->next=hash->next->next;
        free(ptr);
    }
}

void insertMap(char* a,char op,char* b,char* x){
    mapNode* ptr=(mapNode*)malloc(sizeof(mapNode));
    ptr->a=a;
    ptr->op=op;
    ptr->b=b;
    ptr->x=x;;
    ptr->next=hash->next;
    hash->next=ptr;
}

void removeMap(char* a, mapNode* map){
    while(map->next){
        if(strcmp(map->next->a,a)==0 || strcmp(map->next->b,a)==0 || strcmp(map->next->x,a)==0) map->next=map->next->next;
        else map=map->next;
    }
}

char* lookUpMap(char* a,char op,char* b){
    mapNode* map=hash;
    while(map->next){
        if(strcmp(map->next->a,a)==0 || strcmp(map->next->b,b)==0 && op==map->next->op) return map->next->x;
        map=map->next;
    }
    return hash->x;
}