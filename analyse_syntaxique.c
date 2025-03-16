#include <stdio.h>
#include <stdlib.h>
#include "analyse_lexicale.h"
#include "analyse_syntaxique.h"
#include "type_ast.h"

int nb_erreurs = 0;

Ast Rec_exp(void);
Ast Rec_eag(void);
Ast Rec_seq_terme(void);
Ast Rec_suite_seq_terme(Ast gauche);
Ast Rec_terme(void);
Ast Rec_seq_facteur(void);
Ast Rec_suite_seq_facteur(Ast gauche);
Ast Rec_facteur(void);
TypeOperateur Rec_op1(void);
TypeOperateur Rec_op2(void);

// Fonction utilitaire pour créer un nœud opération
Ast creer_operation(TypeOperateur op, Ast gauche, Ast droite)
{
    Ast nouveau = (Ast)malloc(sizeof(NoeudAst));
    nouveau->nature = OPERATION;
    nouveau->operateur = op;
    nouveau->gauche = gauche;
    nouveau->droite = droite;
    return nouveau;
}

// Fonction utilitaire pour créer un nœud valeur
Ast creer_valeur(int val)
{
    Ast nouveau = (Ast)malloc(sizeof(NoeudAst));
    nouveau->nature = VALEUR;
    nouveau->valeur = val;
    nouveau->gauche = NULL;
    nouveau->droite = NULL;
    return nouveau;
}

void erreur_syntaxe()
{
    printf("Erreur de syntaxe ligne %d, colonne %d\n",
           lexeme_courant().ligne,
           lexeme_courant().colonne);
    nb_erreurs++;
}

void analyser(char *fichier, Ast *arbre)
{
    demarrer(fichier);
    *arbre = Rec_exp();

    if (nb_erreurs == 0)
    {
        printf("Expression correcte !\n");
    }
    else
    {
        printf("Expression incorrecte : %d erreur(s)\n", nb_erreurs);
        *arbre = NULL;
    }

    arreter();
}

Ast Rec_exp()
{
    Ast arbre = Rec_eag();
    if (!fin_de_sequence())
    {
        erreur_syntaxe();
    }
    return arbre;
}

Ast Rec_eag()
{
    return Rec_seq_terme();
}

Ast Rec_seq_terme()
{
    Ast gauche = Rec_terme();
    return Rec_suite_seq_terme(gauche);
}

Ast Rec_suite_seq_terme(Ast gauche)
{
    Nature_Lexeme nature = lexeme_courant().nature;
    switch (nature)
    {
    case PLUS:
    case MOINS:
    {
        TypeOperateur op = Rec_op1();
        Ast droite = Rec_terme();
        return Rec_suite_seq_terme(creer_operation(op, gauche, droite));
    }
    default:
        return gauche;
    }
}

Ast Rec_terme()
{
    return Rec_seq_facteur();
}

Ast Rec_seq_facteur()
{
    Ast gauche = Rec_facteur();
    return Rec_suite_seq_facteur(gauche);
}

Ast Rec_suite_seq_facteur(Ast gauche)
{
    if (lexeme_courant().nature == MUL || lexeme_courant().nature == DIV)
    {
        TypeOperateur op = Rec_op2();
        Ast droite = Rec_facteur();
        return Rec_suite_seq_facteur(creer_operation(op, gauche, droite));
    }
    return gauche;
}

Ast Rec_facteur()
{
    Ast resultat;
    switch (lexeme_courant().nature)
    {
    case ENTIER:
        resultat = creer_valeur(lexeme_courant().valeur.valeur_entiere);
        avancer();
        break;

    case PARO:
        avancer();
        resultat = Rec_eag();
        if (lexeme_courant().nature == PARF)
        {
            avancer();
        }
        else
        {
            erreur_syntaxe();
        }
        break;

    default:
        erreur_syntaxe();
        resultat = creer_valeur(0); // Valeur par défaut en cas d'erreur
    }
    return resultat;
}

TypeOperateur Rec_op1()
{
    Nature_Lexeme nature = lexeme_courant().nature;
    TypeOperateur op;
    switch (nature)
    {
    case PLUS:
        op = N_PLUS;
        break;
    case MOINS:
        op = N_MOINS;
        break;
    default:
        erreur_syntaxe();
        op = N_PLUS; // Valeur par défaut en cas d'erreur
    }
    avancer();
    return op;
}

TypeOperateur Rec_op2()
{
    Nature_Lexeme nature = lexeme_courant().nature;
    TypeOperateur op;
    switch (nature)
    {
    case MUL:
        op = N_MUL;
        break;
    case DIV:
        op = N_DIV;
        break;
    default:
        erreur_syntaxe();
        op = N_MUL; // Valeur par défaut en cas d'erreur
    }
    avancer();
    return op;
}