
#include <stdio.h>
#include "type_ast.h"
#include "ast_parcours.h"

void aff_operateur(TypeOperateur op)
{
	switch (op)
	{
	case N_PLUS:
		printf("+");
		break;
	case N_MOINS:
		printf("-");
		break;
	case N_MUL:
		printf("*");
		break;
	case N_DIV:
		printf("/");
		break;
	}
}

void afficher_Ast(Ast expr)
{
	switch (expr->nature)
	{
	case OPERATION:
		printf("(");
		afficher_Ast(expr->gauche);
		aff_operateur(expr->operateur);
		afficher_Ast(expr->droite);
		printf(")");
		break;
	case VALEUR:
		printf("%d", expr->valeur);
		break;
	}
}

int evaluation(Ast expr)
{
	if (expr == NULL)
	{
		return 0;
	}
	switch (expr->nature)
	{
	case VALEUR:
		return expr->valeur;

	case OPERATION:
	{
		int gauche = evaluation(expr->gauche);
		int droite = evaluation(expr->droite);

		switch (expr->operateur)
		{
		case N_PLUS:
			return gauche + droite;
		case N_MOINS:
			return gauche - droite;
		case N_MUL:
			return gauche * droite;
		case N_DIV:
			if (droite == 0)
			{
				printf("Erreur: Division par zéro\n");
				return 0;
			}
			return gauche / droite;
		default:
			return 0;
		}
	}
	default:
		return 0;
	}
}
