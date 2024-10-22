Cycle 2 - Terminal Commands

1) ->lex pgm.l
   ->gcc lex.yy.c
   ->./a.out
   
2),3)
   ->yacc -d pgm.y
   ->lex pgm.l
   ->gcc lex.yy.c y.tab.c -w
   ->./a.out
   
4) ->lex pgm.l
   ->yacc -d pgm.y
   ->gcc lex.yy.c y.tab.c -ll -lm -w
   ->./a.out
   
6) ->yacc -d pgm.y
   ->lex pgm.l
   ->gcc lex.yy.c y.tab.c -ll -w
   ->./a.out
