#ifndef __AST_PARCOURS__
#define __AST_PARCOURS__

#include "type_ast.h"

void afficher_Ast(Ast expr);
// affiche l'arbre abstrait de l'expression arithmetique expr

int evaluation(Ast expr);
// calcule la valeur de l'expression arithmetique expr
// FONCTION A COMPLETER !

#endif
