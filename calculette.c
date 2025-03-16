#include <stdio.h>
#include <stdlib.h>
#include "type_ast.h"
#include "analyse_syntaxique.h"
#include "analyse_lexicale.h"
#include "ast_parcours.h"

int main(int argc, char *argv[])
{
    Ast arbre;

    if (argc < 2)
    {
        printf("Usage : %s <fichier_programme>\n", argv[0]);
        return 1;
    }

    analyser(argv[1], &arbre);

    if (arbre != NULL)
    {
        printf("Arbre abstrait : ");
        afficher_Ast(arbre);
        printf("\n");

        int resultat = evaluation(arbre);
        printf("Résultat de l'évaluation : %d\n", resultat);
    }

    return 0;
}