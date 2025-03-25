%{
 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>
 #include "expl.h"
 #include "expl.c"
 int yylex(void);
 void yyerror(const char* s);
 extern FILE* yyin;
 FILE* TAC_FILE;
%}

%union{
 struct TokenAttr* ToAttr;
 int integer;
}
%type <ToAttr> expr  program  Slist Stmt InputStmt OutputStmt AsgStmt WhileStmt Ifstmt BreakStmt ContinueStmt  Declarations DeclList Decl Varlist Identifier
%type <integer> Type
%token PLUS MINUS MUL DIV  PBEGIN END READ WRITE IF ELSE THEN ENDIF ENDWHILE WHILE LT GT LTE GTE EQUALS NOTEQUALS DO BREAK CONTINUE DECL ENDDECL INT STR 
%token <ToAttr> NUM ID STRING
%left OR
%left AND
%left EQUALS NOTEQUALS
%left LT LTE GT GTE
%left PLUS MINUS
%left MUL DIV


%%

program : Declarations Slist {
    printf("Program finished\nNo Syntax Error\n");
    fprintf(TAC_FILE,"%s",$2->Code); //Here the entire code is wwritten to the TAC file
   }
  | {printf("Write Code in input.expl bruh\n");exit(1);};
  
  ;

Declarations : DECL DeclList ENDDECL  {print_GSymbolTable();}
| DECL ENDDECL {};

DeclList : DeclList Decl {}
| Decl {};

Decl : Type Varlist ';' {curr_declaration_type = 0;};//resetting the declaration type

Type : INT {curr_declaration_type = INTEGER_TYPE;} 
| STR {curr_declaration_type = STRING_TYPE;}

Varlist : Varlist ',' ID {
  G_Install($3->varname,curr_declaration_type,1); //Assuming both str and int have size = 1
};
| ID {G_Install($1->varname,curr_declaration_type,1);}

Slist : Slist Stmt {
  struct TokenAttr* result_token = $2;
  result_token->Code = strcat($1->Code,result_token->Code);
  $$=result_token;
}
| Stmt {$$=$1;};
;

Stmt : InputStmt {} 
|OutputStmt {}
|AsgStmt {$$=$1;}
|Ifstmt {$$=$1;}
|WhileStmt {}
|BreakStmt {}
|ContinueStmt {}
;

// Three Address Code Generation Pending.....

InputStmt : READ '(' Identifier ')' ';' {};

OutputStmt : WRITE '(' expr ')' ';' {};

AsgStmt : Identifier '=' expr ';' {};

BreakStmt : BREAK ';' {}

ContinueStmt : CONTINUE ';' {}

Ifstmt : IF '(' expr ')' THEN Slist ELSE Slist ENDIF ';' {
    char* BooleanTrue = $3->trueLabel;
    char* BooleanFalse = $3->falseLabel;
    char* ExitLabel = newlabel();
    struct TokenAttr* result_token = IfElse_TAC_Generate($3,$6,$8,BooleanTrue,BooleanFalse,ExitLabel);
    $$=result_token;
  }
| IF '(' expr ')' THEN Slist ENDIF ';' {
    char* BooleanTrue = $3->trueLabel;
    char* BooleanFalse = $3->falseLabel;
    struct TokenAttr* result_token = If_TAC_Generate($3,BooleanTrue,$6,BooleanFalse);
    $$=result_token;
  }
;

WhileStmt : WHILE '(' expr ')' DO Slist ENDWHILE ';' {}

expr : expr PLUS expr  {}
  | expr MINUS expr   {}
  | expr MUL expr {}
  | expr DIV expr {}
  | expr LT expr {}
  | expr LTE expr {}
  | expr GT expr {}
  | expr GTE expr {}
  | expr EQUALS expr {}
  | expr NOTEQUALS expr {}
  | expr AND expr {}
  | expr OR expr {}
  | '(' expr ')'  {}
  | NUM   {}
  | Identifier {}
  ;

Identifier : ID {
    if($1->Gentry==NULL){
      printf("Syntax Error: usage of undeclared Variable : %s\n",$1->varname);
      return -1;
    } 
  
  };

%%

void yyerror(char const *s)
{
    printf("yyerror %s\n",s);
}


int main(void) {
    
    FILE* input_file = fopen("input.expl","r");
    TAC_FILE = fopen("TAC_file.txt","w");
    if(!input_file){
        printf("Error: invalid File\n");
    }
    yyin = input_file;
    yyparse();

 return 0;
}