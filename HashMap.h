#pragma once

typedef struct mapNode{ // subexpression of form x = a op b
    char* a;
    char  op;
    char* b;
    char* x;
    struct mapNode* next;
}mapNode ;

extern mapNode* hash;

mapNode* createMap();
void freeMap();
void insertMap(char* a,char op,char* b,char* x);
void removeMap(char* a, mapNode* map);
char* lookUpMap(char* a,char op,char* b);