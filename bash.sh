lex Optimizer.l
yacc Optimizer.y -d
gcc -g lex.yy.c y.tab.c -o parser.exe
./parser.exe
