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

%token IF GOTO NEQ EQ LE GE GT LT 
%token <String> ID NUM

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

%type<node> Expr El;
%type<String> BExpr;

%start Program

%%
Program     :   StmtList
            ;
StmtList    :   StmtList Stmt 
            |   Stmt 
            ;
            ;
Stmt        :   ID '=' Expr         {handleAssignment($1,$3);}
            |   ID '=' El           {removeMap($1,hash);fprintf(outFile,"%s = %s\n",$1,$3->a);}
            |   IF BExpr GOTO ID    {freeMap();fprintf(outFile,"if %s goto %s\n",$2,$4);}
            |   GOTO ID             {freeMap();fprintf(outFile,"goto %s\n",$2);}
            |   ID ':'              {freeMap();fprintf(outFile,"%s:\n",$1);}
            ;
BExpr       :   El GE El            {sprintf($$,"%s <= %s",$1->a,$3->a);$$=strdup($$);}  
            |   El LE El            {sprintf($$,"%s >= %s",$1->a,$3->a);$$=strdup($$);}  
            |   El NEQ El           {sprintf($$,"%s != %s",$1->a,$3->a);$$=strdup($$);}  
            |   El EQ El            {sprintf($$,"%s == %s",$1->a,$3->a);$$=strdup($$);}  
            |   El GT El            {sprintf($$,"%s > %s",$1->a,$3->a);$$=strdup($$);}  
            |   El LT El            {sprintf($$,"%s > %s",$1->a,$3->a);$$=strdup($$);}  
            ;
Expr        :   El '+' El       {$$=makeNode($1->a,'+',$3->a);}
            |   El '-' El       {$$=makeNode($1->a,'-',$3->a);}
            |   El '*' El       {$$=makeNode($1->a,'*',$3->a);}
            |   El '/' El       {$$=makeNode($1->a,'/',$3->a);}
            ;
El          :   ID              {$$=makeNode($1,' ',"");}
            |   NUM             {$$=makeNode($1,' ',"");}
            ;

%%

void yyerror(char const *s){
    printf("Error %s\n",s);
    exit(0);
}

int main(){
    FILE *fp=fopen("TAC_file.txt","r");
    outFile=fopen("optimized.tac","w");
    hash=createMap();
    yyin=fp;
    yyparse();
    printf("Optimization completed\n");
    return 0;
}

void handleAssignment(char* a, mapNode* expr){
    char* res=lookUpMap(expr->a,expr->op,expr->b);
    if(strcmp(res,"NULL")!=0) fprintf(outFile,"%s = %s\n",a,res);
    else fprintf(outFile,"%s = %s %c %s\n",a,expr->a,expr->op,expr->b);
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