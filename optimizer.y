%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include "HashMap.h"
    
    extern FILE *yyin;
    extern void yyerror(char const *s);
    extern int yylex();

    struct mapNode* hash;
    FILE* outFile;
    mapNode* makeNode(char* a,char op,char* b);
    void handleAssignment(char* a, mapNode* expr);
%}

%union{
 char* String;
 int Int;
 struct mapNode* node;
}

%token IF ELSE GOTO NEQ EQ LE GE GT LT begin end
%token <String> ID LABEL NUM

%left LT
%left GT
%left GE
%left LE
%left EQ
%left NEQ

%left '+'
%left '-'
%left '*'
%left '/'

%type<node> Expr;
%type<String> BExpr;

%start Program

%%
Program     :   StmtList
            ;
StmtList    :   StmtList Stmt 
            |   Stmt 
            ;
Stmt        :   ID '=' Expr         {handleAssignment($1,$3);}
            |   IF BExpr GOTO ID    {freeMap();fprintf(outFile,"if %s goto %s\n",$2,$4);}
            |   GOTO ID             {freeMap();fprintf(outFile,"goto %s\n",$2);}
            |   ID ':'              {freeMap();fprintf(outFile,"%s:\n",$1);}
            ;
BExpr       :   ID GE ID            {sprintf($$,"%s >= %s",$1,$3);$$=strdup($$);}  
            |   ID LE ID            {sprintf($$,"%s <= %s",$1,$3);$$=strdup($$);}  
            |   ID NEQ ID           {sprintf($$,"%s != %s",$1,$3);$$=strdup($$);}  
            |   ID EQ ID            {sprintf($$,"%s == %s",$1,$3);$$=strdup($$);}  
            |   ID GT ID            {sprintf($$,"%s > %s",$1,$3);$$=strdup($$);}  
            |   ID LT ID            {sprintf($$,"%s > %s",$1,$3);$$=strdup($$);}  
            ;
Expr        :   ID              {$$=makeNode($1,' ',"");}
            |   NUM             {$$=makeNode($1,' ',"");}
            |   Expr '+' Expr   {$$=makeNode($1->a,'+',$3->a);}
            |   Expr '-' Expr   {$$=makeNode($1->a,'-',$3->a);}
            |   Expr '*' Expr   {$$=makeNode($1->a,'*',$3->a);}
            |   Expr '/' Expr   {$$=makeNode($1->a,'/',$3->a);}
            ;

%%

void yyerror(char const *s){
    printf("Error %s\n",s);
    exit(0);
}

int main(){
    FILE *fp=fopen("example.tac","r");
    outFile=fopen("optimized.tac","w");
    hash=createMap();
    yyin=fp;
    yyparse();
    return 0;
}

void handleAssignment(char* a, mapNode* expr){
    char* res=lookUpMap(expr->a,expr->op,expr->b);
    if(strcmp(res,"NULL")!=0) fprintf(outFile,"%s=%s\n",a,res);
    else fprintf(outFile,"%s=%s %c %s\n",a,expr->a,expr->op,expr->b);
    removeMap(a,hash);
    insertMap(expr->a,expr->op,expr->b,a);
}

mapNode* makeNode(char* a,char op,char* b){
    mapNode* ptr=(mapNode*)malloc(sizeof(mapNode)); 
    ptr->next=NULL;
    ptr->a=a;
    ptr->op=op;
    ptr->b=b;
    return ptr;
}