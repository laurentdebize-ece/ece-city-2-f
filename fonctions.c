
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions.h"
/* affichage des successeurs du sommet num*/

void afficher_successeurs(pSommet *sommet, int num) {

    printf(" sommet %d :\n", num);

    pArc arc = sommet[num]->arc;

    while (arc != NULL) {
        printf("%d ", arc->sommet);
        arc = arc->arc_suivant;
    }

}

// Ajouter l'arete entre les sommets s1 et s2 du graphe
pSommet *CreerArete(pSommet *sommet, int s1, int s2) {
    if (sommet[s1]->arc == NULL) {
        pArc Newarc = (pArc) malloc(sizeof(struct Arc));
        Newarc->sommet = s2;
        Newarc->arc_suivant = NULL;
        sommet[s1]->arc = Newarc;
        return sommet;
    } else {
        pArc temp = sommet[s1]->arc;
        while (!(temp->arc_suivant == NULL)) {
            temp = temp->arc_suivant;
        }
        pArc Newarc = (pArc) malloc(sizeof(struct Arc));
        Newarc->sommet = s2;
        Newarc->arc_suivant = NULL;

        if (temp->sommet > s2) {
            Newarc->arc_suivant = temp->arc_suivant;
            Newarc->sommet = temp->sommet;
            temp->sommet = s2;
            temp->arc_suivant = Newarc;
            return sommet;
        }

        temp->arc_suivant = Newarc;
        return sommet;
    }
}

// creer le graphe
Graphe2 *CreerGraphe2(int ordre, int taille) {
    Graphe2 *Newgraphe = (Graphe2 *) malloc(sizeof(Graphe2));
    Newgraphe->pSommet = (pSommet *) malloc(ordre * sizeof(pSommet));
    Newgraphe->pArete = (pArete *) malloc(taille * sizeof(pArete)); //Créer les are^tes du graphe.


    for (int i = 0; i < ordre; i++) {
        Newgraphe->pSommet[i] = (pSommet) malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->valeur = i;
        Newgraphe->pSommet[i]->arc = NULL;
    }
    for (int i = 0; i < taille; ++i) {
        Newgraphe->pArete[i] = (pArete) malloc(sizeof(struct Sommet));
        Newgraphe->pArete[i]->sommetDepart = NULL;// Initialisation de chaque sommet de départ d'une arête à 0.
        Newgraphe->pArete[i]->sommetArrive = NULL;// Initialisation de chaque sommet d'arrivée d'une arête à 0.
    }
    return Newgraphe;
}
Graphe1 *lire_graphe(char *nomFichier) {
    Graphe1 *graphe;
    FILE *ifs = fopen(nomFichier, "r");
    int taille, orientation, ordre, s1, s2;

    if (!ifs) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    fscanf(ifs, "%d", &ordre);

    graphe = CreerGraphe(ordre); // creer le graphe d'ordre sommets

    fscanf(ifs, "%d", &taille);
    fscanf(ifs, "%d", &orientation);

    graphe->orientation = orientation;
    graphe->ordre = ordre;

    // creer les aretes du graphe
    for (int i = 0; i < taille; ++i) {
        fscanf(ifs, "%d%d", &s1, &s2);
        graphe->pSommet = CreerArete(graphe->pSommet, s1, s2);

        if (!orientation)
            graphe->pSommet = CreerArete(graphe->pSommet, s2, s1);
    }

    return graphe;
}

/*affichage du graphe avec les successeurs de chaque sommet */
void graphe_afficher(Graphe1 *graphe) {
    printf("graphe\n");

    if (graphe->orientation)
        printf("oriente\n");
    else
        printf("non oriente\n");

    printf("ordre = %d\n", graphe->ordre);

    printf("listes d'adjacence :\n");

    for (int i = 0; i < graphe->ordre; i++) {
        afficher_successeurs(graphe->pSommet, i);
        printf("\n");
    }

}




void BFS(Graphe1 *g, int sommet0) {
    for (int i = 0; i < g->ordre; ++i) {
        g->pSommet[i]->couleur = 0;
    }
    int a = sommet0;
    int temporaire = 0;
    //printf("Veuillez choisir le sommet de départ:");
    // scanf("&d\n",a);
    File F = fileVide();
    bool end1 = false;
    enfiler(F, sommet0);
    g->pSommet[sommet0]->couleur = 1;
    printf("Ordre de découverte:\n");
    while (!end1) {
        pArc arc = g->pSommet[a]->arc;
        while (arc != NULL) {
            if (g->pSommet[arc->sommet]->couleur == 0) {
                enfiler(F, arc->sommet);
                g->pSommet[arc->sommet]->pred = a;
                g->pSommet[arc->sommet]->couleur = 1;
            }
            arc = arc->arc_suivant;
        }
        printf("%d ",a);
        decapiter(F);
        if (longueur(F) == 0) {
            end1 = 1;
        }
        if (longueur(F) != 0) {
            a = tete(F);
        }
    }
    printf("\n\n");
    printf("Parcours BFS depuis le sommet %d:\n", sommet0);
    bool end2;
    for (int i = 0; i < g->ordre; ++i) {
        temporaire = i;
        if (g->pSommet[i]->couleur != 0 && i != sommet0) {
            end2 = 0;
            while (!end2) {
                if (temporaire != sommet0) {
                    printf("%d<--", temporaire);
                }
                if (temporaire == sommet0) {
                    printf("%d\n", sommet0);
                    end2 = 1;
                }
                temporaire = g->pSommet[temporaire]->pred;
            }
        }
    }
}

int RecupererLaDistanceLaPlusCourte(
        Graphe1 *g) {
// valeur impossible, correspond aux distances des arêtes
// initialement infinis. mettre un -1 permet alors d'éviter de donner une grand valeur qui gaspillerai de la mémoire
    int sommetAvecLaPlusCourteDistance = -1;
    for (int i = 0; i < g->ordre; ++i) { //pour faire défiler la totalité des sommets (g->ordre = 9 ici)
        if (g->pSommet[i]->distance != -1 && g->pSommet[i]->couleur == 0) {
            if (sommetAvecLaPlusCourteDistance == -1) { //initialise a i lorsque les distances sont +infini
                sommetAvecLaPlusCourteDistance = i;
            } else if (g->pSommet[i]->distance < g->pSommet[sommetAvecLaPlusCourteDistance]->distance &&
                       sommetAvecLaPlusCourteDistance != -1) {
                sommetAvecLaPlusCourteDistance = i;
            }
        }
    }
    return sommetAvecLaPlusCourteDistance; //retourne
}


// La fonction permet de donner le plus cours chemin entre deux arêtes grâce à la méthode de l'algorithme de Dijkstra
// La fonction prend en paramètre un graphe et un sommet initial depuis lequel le graphe sera parcouru
void Dijkstra(Graphe1 *g, int sommet0) {
    bool end = 0;
    for (int i = 0; i < g->ordre; ++i) { // pour faire défiler la totalité des sommets
        g->pSommet[i]->couleur = 0; // couleur 0 car initialement pas découvert
        g->pSommet[i]->pred = 0; // le predecesseur passera à 0 afin de ne pas le parcourir a nouveau
        // depuis le nouveau sommet
        g->pSommet[i]->distance = -1; // on initialise les distances +infini, ici -1 pour des raisons techniques
    }
    g->pSommet[sommet0]->distance = 0; // en dehors de la boucle car nous n'avons besoin d'initialiser
    // le sommet initial une seul foid, et ça distance sera toujours de 0
    int temporaire; //variable temporaire qui coresspondra à une distance entre deux sommets.
    // Chaque distance la plus courte entre deux sommets sera assignée
    // à temporaire lorsque la fonction sera lancée

    while (!end) { // "Grande boucle" de la fonction qui mettra un terme à celle-ci une fois chaque sommet traîtés
        temporaire = RecupererLaDistanceLaPlusCourte(g); // recupère la valeur de la fonction correspondant
        // à la plus courte distance entre 2 sommets du graphe
        if (temporaire == -1) {
            end = 1;
        }
        if (end == 0) { // = tant qu'il reste des sommets
            g->pSommet[temporaire]->couleur = 1; // marque le sommet traité
            pArc arcTemporaire = g->pSommet[temporaire]->arc;
            while (arcTemporaire != NULL) { // = tant qu'il des distances d'arêtes à marquer
                if (g->pSommet[arcTemporaire->sommet]->distance == -1 ||
                    g->pSommet[temporaire]->distance + arcTemporaire->distance <
                    g->pSommet[arcTemporaire->sommet]->distance) // si la distance est infini ou que la distance
                    // n'est pas la plus courte possible
                {
                    g->pSommet[arcTemporaire->sommet]->distance =
                            g->pSommet[temporaire]->distance + arcTemporaire->distance;
                    g->pSommet[arcTemporaire->sommet]->pred = temporaire;
                } // marque l'arête avec la plus petite distance trouvée
                arcTemporaire = arcTemporaire->arc_suivant; // passe à la prochaine arête
            }
        }
    }
}
int RecupererArreteDePoidsMinimum(Graphe2 *g) { //Fonction qui donnera la prochaine arete la plus petite pour Kruskal.
    int poidsMinimum = 2147483647; // Plus grande valeur que peut contenir un int
    int areteARetourner; // Valeur que retournera la fonction.
    for (int i = 0; i < g->taille; ++i) { //Pour chaque arêtes, faire:
        if (g->pArete[i]->distance < poidsMinimum &&
            g->pArete[i]->pasDejaSelectionnee == 0) { // Ne rien faire si la distance est plus petite que
            // la précedante de poids minimum et qu'il sagit d'une arête
            // non encore "marquée":
            areteARetourner = i; // Si l'arête est la plus petite, on l'assigne à la valeur à retourner.
            poidsMinimum = g->pArete[i]->distance; // On assigne Le poids minimum de l'arête à la distance que l'on vient de trouver.
        }
    }
    g->pArete[areteARetourner]->pasDejaSelectionnee = 1; // On passe "pasDejaSelectionnee" à 1 afin de ne pas parcourir la même arête dans le sens contraire
    //(ex {0,8} et {8,0} sont égales dans un graphe non orienté).
    return areteARetourner;
}

//Fonction permettant de realiser l'algorithme de Kruskal
void Kruskal(Graphe2 *g) {
    int nombreAretes = 0; // Initialisation du nombre de sommet à 0.
    int parcoursPetitesAretes; // Initialisation de la valeur qui correspondra aux arêtes de plus petit poids
    // (les arêtes que retournera la fonction RecupererArreteDePoidsMinimum).
    for (int i = 0; i < g->ordre; ++i) { // Pour chaque sommets, faire:
        g->pSommet[i]->numeroDeComposanteConnexe = i; // initialisation de chaque CC (initialement tous différent).
    }
    while (nombreAretes < g->ordre - 1) { // Tant que le nombre d'arête est inferieur à l'ordre-1):
        parcoursPetitesAretes = RecupererArreteDePoidsMinimum(g);
        if (g->pSommet[g->pArete[parcoursPetitesAretes]->sommetDepart]->numeroDeComposanteConnexe !=
            g->pSommet[g->pArete[parcoursPetitesAretes]->sommetArrive]->numeroDeComposanteConnexe) // Si le numéro de CC du sommet de
            // Départ est différent de celui d'arrivée, faire:
        {
            g->pArete[parcoursPetitesAretes]->couleur = 1; //Marquer l'arete.
            for (int i = 0; i < g->ordre; ++i) { //Pour chaque sommet, faire:
                if (g->pSommet[i]->numeroDeComposanteConnexe ==
                    g->pSommet[g->pArete[parcoursPetitesAretes]->sommetArrive]->numeroDeComposanteConnexe &&
                    i !=
                    g->pArete[parcoursPetitesAretes]->sommetArrive) // Si le numéro de CC du sommet traité est le même que celui d'arrivée
                    // et que le sommet traité est différent du sommet d'arrivé de l'arête:
                {
                    g->pSommet[i]->numeroDeComposanteConnexe = g->pSommet[g->pArete[parcoursPetitesAretes]->sommetDepart]->numeroDeComposanteConnexe;
                    // On change le numéro de CC du sommet traité a celui du sommet de départ.
                }
            }
            g->pSommet[g->pArete[parcoursPetitesAretes]->sommetArrive]->numeroDeComposanteConnexe = g->pSommet[g->pArete[parcoursPetitesAretes]->sommetDepart]->numeroDeComposanteConnexe;
            // On change le numéro de CC du sommet d'arrivé de la plus petite arête du sommet a celui du sommet de départ de cette même arête.
            nombreAretes = nombreAretes + 1; // On incrémente le nombre d'arête.
        }
    }
}

//Fonction permettant de realiser l'algorithme de Prim
void Prim(Graphe1 *g, int sommetDeDepart) {
    bool end = 0;
    int nombreDeSommetMarque = 0; // Compte le nombre de sommet marqué
    int arreteDePoidsMinimal = 9999;  // Permettra de comparer le poids d'une arête pour choisir la plus petite à la fin.
    // Valeur aberrante afin de rentrer dans la boucle, elle sera changée un fois dedans.
    int sommetTemporaire; // Chaque sommet prendra cette variable afin d'être traité.
    int predecesseurTemporaire; // Predecesseur du sommet temporaire.
    int poidsminimumDeLArbre = 0; // Donnera le poids total minimimum de l'arbre à la fin du programme.
    for (int i = 0; i < g->ordre; ++i) // Marque les sommets à 0 et sans predecesseurs.
    {
        g->pSommet[i]->couleur = 0;
        g->pSommet[i]->pred = 0;
    }
    g->pSommet[sommetDeDepart]->couleur = 1; //Marque le sommet de départ.
    nombreDeSommetMarque++; // Incremente le nombre de sommet marqué.
    while (nombreDeSommetMarque != g->ordre) { // Tant qu'il reste des sommets non marqués:
        for (int i = 0; i < g->ordre; i++) { // Pour chacuns des sommets, faire:
            if (g->pSommet[i]->couleur == 1) { // Si le sommet est marqué, faire:
                pArc pointeurSurSuccesseur = g->pSommet[i]->arc; //On fait pointer sur l'arc du sommet traité
                while (pointeurSurSuccesseur != NULL) {
                    if (g->pSommet[pointeurSurSuccesseur->sommet]->couleur != 1 &&
                        pointeurSurSuccesseur->distance < arreteDePoidsMinimal) {
                        // Si le sommet est non marqué et
                        // que la distance trouvée est plus petite que la
                        //plus petite distance precedement trouvée:
                        arreteDePoidsMinimal = pointeurSurSuccesseur->distance; // On prend la nouvelle plus petite distance.
                        sommetTemporaire = pointeurSurSuccesseur->sommet;// Le sommet temporaire devient son successeur.
                        predecesseurTemporaire = g->pSommet[i]->valeur;// L'ancien predecesseur devient le nouveau sommet traité.
                    }
                    pointeurSurSuccesseur = pointeurSurSuccesseur->arc_suivant; // Le poiteur sur l'arc du successeur prend la valeur du prochain arc.
                }
            }
        }
        g->pSommet[sommetTemporaire]->pred = predecesseurTemporaire;// Le predecesseur du sommet traité devient le nouveau predecesseur temporaire
        // afin de passer au prochain sommet.
        g->pSommet[sommetTemporaire]->couleur = 1;// On marque le sommet.
        nombreDeSommetMarque++;// On incremente le nombre de sommet marqué.
        poidsminimumDeLArbre = poidsminimumDeLArbre +
                               arreteDePoidsMinimal; // On ajoute au poids de l'arbre le poids de l'arête que nous venons de traiter
        // afin d'avoir le poid total à la fin.
        printf("Arete[%d-%d]:\n•Poids:%d\n\n", predecesseurTemporaire, sommetTemporaire, arreteDePoidsMinimal);
        arreteDePoidsMinimal = 9999; // On refixe le poids minimal a une grosse valeur afin de rentrer dans la boucle qui compare le poids de chaque arête.
    }; // On refait la boucle tant qu'il reste des sommets non marqués.
    printf("Le poids minimum de l'arbre est de %d.\n", poidsminimumDeLArbre);
}
void DFSAdapte(Graphe3 *g, int sommet) {
    int pile[g->ordre-1]; // Tableau qui represente la pile
    int compteur = 0; // Entier qui permet de parcourir la pile
    g->pSommet[sommet]->couleur = 1; // On marque le 1er sommet
    pile[compteur] = sommet;
    compteur++;
    while (compteur != 0){
        sommet = pile[compteur - 1];
        compteur--;
        for (int i = 0; i < g->ordre; ++i) {
            if (g->capaciteMax[sommet][i] != 0 && g->capaciteMax[sommet][i] != g->fluxActuel[sommet][i] &&
                g->pSommet[i]->couleur == 0) {
                pile[compteur] = i;
                compteur++;
                g->pSommet[i]->couleur = 1;
                g->pSommet[i]->sens = 1; // sens positif
                g->pSommet[i]->pred = sommet;
                if (g->pSommet[sommet]->capacite > (g->capaciteMax[sommet][i] - g->fluxActuel[sommet][i]))
                    g->pSommet[sommet]->capacite = g->capaciteMax[sommet][i] - g->fluxActuel[sommet][i];
            }
        }
        for (int i = 0; i < g->ordre; ++i) {
            if (g->capaciteMax[i][sommet] != 0 && g->fluxActuel[i][sommet] != 0 && g->pSommet[i]->couleur == 0) {
                pile[compteur] = i;
                compteur++;
                g->pSommet[i]->couleur = 1;
                g->pSommet[i]->pred = sommet;
                g->pSommet[i]->sens = 0; // sens neg
                if (g->pSommet[sommet]->capacite > g->fluxActuel[i][sommet])
                    g->pSommet[sommet]->capacite = g->fluxActuel[i][sommet];
            }
        }
    }
}

void FordFulkerson(Graphe3 *g) {
    int capaciteFord; // Plus petite valeur du chemn augmentant
    int source = 0;
    int sommet;
    int puit = g->ordre - 1;
    do {
        capaciteFord = 2147483647; // Valeur initialement infini
        sommet = puit;
        for (int i = 0; i < g->ordre; ++i) {
            g->pSommet[i]->pred = -1;
            g->pSommet[i]->couleur = 0;
            g->pSommet[i]->capacite = 2147483647;
        }
        DFSAdapte(g, 0);
        if (g->pSommet[puit]->pred != -1) {
            do {
                if (g->pSommet[g->pSommet[sommet]->pred]->capacite < capaciteFord) {
                    capaciteFord = g->pSommet[g->pSommet[sommet]->pred]->capacite;
                }
                sommet = g->pSommet[sommet]->pred;
            } while (sommet != source);
            sommet = puit;
            do {
                if (g->pSommet[g->pSommet[sommet]->pred]->sens == 1) {
                    g->fluxActuel[g->pSommet[sommet]->pred][sommet] += capaciteFord;
                }
                else {
                    g->fluxActuel[g->pSommet[sommet]->pred][sommet] -= capaciteFord;
                }
                sommet = g->pSommet[sommet]->pred;
            } while (sommet != source);
        }
    } while (g->pSommet[puit]->pred != -1);
}

