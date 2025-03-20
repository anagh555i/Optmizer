#!/bin/bash/

lex optimizer.l 
yacc -d optimizer.y
gcc lex.yy.c y.tab.c HashMap.c -o out
./out
