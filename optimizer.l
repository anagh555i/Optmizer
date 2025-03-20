%{
    #include "y.tab.h"  
    #include<string.h>  
%}

%%

"if"    {printf("Found %s\n",yytext); return IF;}
"begin"    {printf("Found %s\n",yytext); return begin;}
"end"    {printf("Found %s\n",yytext); return end;}
"else"    {printf("Found %s\n",yytext); return ELSE;}
"goto"    {printf("Found %s\n",yytext); return GOTO;}
[!][=]  { printf("Found %s\n",yytext); return NEQ;}
[=][=]  { printf("Found %s\n",yytext); return EQ;}
[<][=]  { printf("Found %s\n",yytext); return LE;}
[>][=]  { printf("Found %s\n",yytext); return GE;}
[>]  { printf("Found %s\n",yytext); return GT;}
[<]  { printf("Found %s\n",yytext); return LT;}

[0-9]+              {yylval.Int=atoi(yytext); return NUM;}
[(|)|+|\-|*|/|;|%|=|<|>|,|&|{|}|\[|\]:]    {printf("found %s\n",yytext);return *yytext;}
[a-zA-Z][a-zA-Z0-9]*    {
                            printf("found %s %d\n",yytext,yyleng);
                            yylval.String=strdup(yytext); return ID;
                        }
[ \n\t]             {;}
.                   {printf("Unexpected Character\n");
                    exit(0);}

%%

int yywrap(void){
    return 1;
}