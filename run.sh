#!/bin/bash/
lex parser.l
yacc parser.y -d
gcc -g lex.yy.c y.tab.c -o parser.exe
./parser.exe

lex optimizer.l 
yacc -d optimizer.y
gcc lex.yy.c y.tab.c HashMap.c -o out
./out
