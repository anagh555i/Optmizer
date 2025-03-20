lex parser.l
yacc parser.y -d
gcc -g lex.yy.c y.tab.c -o parser.exe
./parser.exe
