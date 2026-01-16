#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../include/structs.h"
#include "../include/dijkstra.h"


// trouver l'index d'une station
static int trouver_index(Station *stations, int n, int id) {
    int i;
    for (i = 0; i < n; i++) {
        if (stations[i].id_station == id) {
            return i;
        }
    }
    return -1;
}

// calculer le plus court chemin avec dijkstra
void calculer_chemin(Station *stations, int nb_stations) {
    int i, j;
    int depart, arrivee;
    int src_idx, dest_idx;
    int *distances;
    int *precedents;
    int *visite;
    int min_dist, min_idx;
    Edge *voisin;
    int nouvelle_dist;
    
    printf("Station de depart : ");
    scanf("%d", &depart);
    printf("Station d'arrivee : ");
    scanf("%d", &arrivee);
    
    // Allocation dynamique
    distances = malloc(nb_stations * sizeof(int));
    precedents = malloc(nb_stations * sizeof(int));
    visite = malloc(nb_stations * sizeof(int));
    
    // trouver les indices
    src_idx = trouver_index(stations, nb_stations, depart);
    dest_idx = trouver_index(stations, nb_stations, arrivee);
    
    if (src_idx == -1 || dest_idx == -1) {
        printf("Une des stations n'existe pas\n");
        free(distances);
        free(precedents);
        free(visite);
        return;
    }
    
    // initialisation
    for (i = 0; i < nb_stations; i++) {
        distances[i] = INT_MAX;
        precedents[i] = -1;
        visite[i] = 0;
    }
    distances[src_idx] = 0;
    
    // algorithme principal
    for (i = 0; i < nb_stations - 1; i++) {
        // chercher le min
        min_dist = INT_MAX;
        min_idx = -1;
        for (j = 0; j < nb_stations; j++) {
            if (visite[j] == 0 && distances[j] < min_dist) {
                min_dist = distances[j];
                min_idx = j;
            }
        }
        
        if (min_idx == -1) {
            break;
        }
        
        visite[min_idx] = 1;
        
        // regarder les voisins
        voisin = stations[min_idx].edges;
        while (voisin != NULL) {
            int v_idx = trouver_index(stations, nb_stations, voisin->destination);
            if (v_idx != -1 && visite[v_idx] == 0) {
                nouvelle_dist = distances[min_idx] + voisin->time;
                if (nouvelle_dist < distances[v_idx]) {
                    distances[v_idx] = nouvelle_dist;
                    precedents[v_idx] = min_idx;
                }
            }
            voisin = voisin->next;
        }
    }

    // affichage du résultat
    if (distances[dest_idx] == INT_MAX) {
        printf("Pas de chemin trouve\n");
        free(distances);
        free(precedents);
        free(visite);
        return;
    }
    
    // reconstruire le chemin
    int *chemin = malloc(nb_stations * sizeof(int));
    int taille = 0;
    int actuel = dest_idx;
    while (actuel != -1) {
        chemin[taille] = actuel;
        taille++;
        actuel = precedents[actuel];
    }
    
    // afficher
    printf("Temps total: %d minutes\n", distances[dest_idx]);
    printf("Chemin: ");
    for (i = taille - 1; i >= 0; i--) {
        printf("%d", stations[chemin[i]].id_station);
        if (i != 0) {
            printf(" -> ");
        }
    }
    printf("\n");
    
    free(distances);
    free(precedents);
    free(visite);
    free(chemin);
}