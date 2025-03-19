%{
 #include <stdlib.h>
 #include <stdio.h>
 #include "y.tab.h"
 #include "expl.h"
void yyerror(const char* s);
 int number;
 char* variable;
%}



%%

[0-9]+ {number = atoi(yytext); yylval.ToAttr = MakeTokenAttr(number,NULL,INTEGER_TYPE,NULL); return NUM;}
"begin" {return PBEGIN;}
"end" {return END;}
"read" {return READ;}
"write" {return WRITE;}
"if" {return IF;}
"then" {return THEN;}
"else" {return ELSE;}
"endif" {return ENDIF;}
"while" {return WHILE;}
"do" {return DO;}
"endwhile" {return ENDWHILE;}
"break" {return BREAK;}
"continue" {return CONTINUE;}
"decl" {return DECL;}
"enddecl" {return ENDDECL;}
"int" {return INT;}
"str" {return STR;}
"<" {return LT;}
">" {return GT;}
"<=" {return LTE;}
">=" {return GTE;}
"==" {return EQUALS;}
"!=" {return NOTEQUALS;}
"&&" {return AND;}
"||" {return OR;}
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MUL;}
"/" {return DIV;}
"=" {return *yytext;}
";" {return *yytext;}
"," {return *yytext;}
["][a-zA-Z0-9_ -]*["] {
    //yytext holds string
    yylval.ToAttr = MakeTokenAttr(-1,yytext,STRING_TYPE,NULL);
    return STRING;
}
[a-zA-Z][a-zA-Z0-9_]* {
    variable = yytext;
    yylval.ToAttr = MakeTokenAttr(-1,variable,-1,NULL);
    Gsymbol* entry = GLookUp(variable);
    if(entry!=NULL){
        (yylval.ToAttr)->Gentry = entry;
        (yylval.ToAttr)->Type = entry->type;
    }
    return ID;
    }
[ \t] {}
[()] {return *yytext;}
[\n] {}
. {printf("%s ",yytext); yyerror("Unknown character\n");exit(1);}

%%

int yywrap(void) {
 return 1;
}