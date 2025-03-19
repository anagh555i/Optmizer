#pragma once

typedef struct mapNode{ // subexpression of form a op b
    char* a;
    char  op;
    char* b;
    int   tNo;
    mapNode* next;
}mapNode ;

mapNode* createMap();
mapNode* insertMap(char* a,char op,char* b,int tNo,mapNode* next);
void removeMap(char* a, mapNode* map);
int lookUpMap(char* a,char op,char* b);