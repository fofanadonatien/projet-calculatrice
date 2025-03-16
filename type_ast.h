
#ifndef __TYPE_AST__
#define __TYPE_AST__

typedef enum
{
	OPERATION,
	VALEUR
} TypeAst;
typedef enum
{
	N_PLUS,
	N_MUL,
	N_MOINS,
	N_DIV
} TypeOperateur;

typedef struct noeud
{
	TypeAst nature;
	TypeOperateur operateur;
	struct noeud *gauche, *droite;
	int valeur;
} NoeudAst;

typedef NoeudAst *Ast;

// Renommé pour éviter le conflit avec la fonction afficher de analyse_lexicale.h
void afficher_Ast(Ast expr);

#endif
