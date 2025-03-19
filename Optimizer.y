%{
    #include<stdio.h>
    #include<stdlib.h>
%}


%%

%%

yyerror(char const *s){
    printf("Error: %s\n",s);
}

int main(){
    yyparse();
    return 1;
}