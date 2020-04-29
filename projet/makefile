all :
	## Pour le fichier .l
	# flex lexicale.l
	# gcc lex.yy.c -o lexer

	## Pour le fichier .y
	yacc -d compiler.y 
	# pour debuguer flex -d compiler.l 
	flex -d compiler.l 
	gcc lex.yy.c y.tab.c symboltable.c -o compiler


clean :
	## Pour le fichier .l
	# rm -f lex.yy.c lexer

	## Pour le fichier .y
	rm -f lex.yy.c y.tab.c compiler
