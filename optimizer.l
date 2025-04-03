%{
    #include "y.tab.h"  
    #include<string.h>
    #include<stdbool.h>
    
    bool debug=false;

    void print(char* txt){
        if(debug)
        printf("Found %s\n",txt);
    }
%}

%%

"if"    {print(yytext); return IF;}
"begin"    {print(yytext); return begin;}
"end"    {print(yytext); return end;}
"else"    {print(yytext); return ELSE;}
"goto"    {print(yytext); return GOTO;}
[!][=]  { print(yytext); return NEQ;}
[=][=]  { print(yytext); return EQ;}
[<][=]  { print(yytext); return LE;}
[>][=]  { print(yytext); return GE;}
[>]  { print(yytext); return GT;}
[<]  { print(yytext); return LT;}

[0-9]+              {print(yytext); yylval.String=strdup(yytext); return NUM;}
[(|)|+|\-|*|/|;|%|=|<|>|,|&|{|}|\[|\]:]    {print(yytext);return *yytext;}
[a-zA-Z][a-zA-Z0-9]*    {
                            print(yytext);
                            yylval.String=strdup(yytext); return ID;
                        }
[ \n\t]             {;}
.                   {printf("Unexpected Character\n");
                    exit(0);}

%%

int yywrap(void){
    return 1;
}