all: calculette test_lexeme essai_ast

calculette: analyse_lexicale.o lecture_caracteres.o analyse_syntaxique.o calculette.o ast_parcours.o
	gcc -g -Wall -o calculette analyse_lexicale.o lecture_caracteres.o analyse_syntaxique.o calculette.o ast_parcours.o -lm

test_lexeme: analyse_lexicale.o lecture_caracteres.o test_lexeme.o
	gcc -g -Wall -o test_lexeme analyse_lexicale.o lecture_caracteres.o test_lexeme.o

essai_ast: ast_construction.o ast_parcours.o essai_ast.o  
	gcc -g -Wall -o essai_ast ast_construction.o ast_parcours.o essai_ast.o

analyse_lexicale.o: analyse_lexicale.c analyse_lexicale.h lecture_caracteres.h
	gcc -g -Wall -c analyse_lexicale.c

lecture_caracteres.o: lecture_caracteres.h lecture_caracteres.c
	gcc -g -Wall -c lecture_caracteres.c

analyse_syntaxique.o: analyse_syntaxique.c analyse_syntaxique.h analyse_lexicale.h
	gcc -g -Wall -c analyse_syntaxique.c

calculette.o: calculette.c analyse_syntaxique.h ast_parcours.h
	gcc -g -Wall -c calculette.c

ast_parcours.o: ast_parcours.c ast_parcours.h type_ast.h
	gcc -g -Wall -c ast_parcours.c

test_lexeme.o: analyse_lexicale.h
	gcc -g -Wall -c test_lexeme.c

ast_construction.o: ast_construction.c type_ast.h
	gcc -g -Wall -c ast_construction.c

essai_ast.o: essai_ast.c ast_construction.h ast_parcours.h type_ast.h
	gcc -g -Wall -c essai_ast.c

clean:
	rm -f calculette essai_ast test_lexeme *.o