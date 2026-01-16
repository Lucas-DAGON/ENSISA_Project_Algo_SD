#include <stdio.h>
#include <stdlib.h>

#include "../include/menu.h"
#include "../include/sort.h"
#include "../include/structs.h"
#include "../include/dijkstra.h"

// Display the menu options
static void show_menu() {
    printf("\n==== MENU RESEAU DE TRANSPORT ====\n");
    printf("1 - Afficher les informations d'une station\n");
    printf("2 - Lister les voisins d'une station\n");
    printf("3 - Calculer un chemin minimal\n");
    printf("4 - Afficher les stations triees par degre\n");
    printf("0 - Quitter\n");
    printf("Votre choix : ");
}

// Print the list of stations
static void print_stations(const Station *station_array, int nb_stations)
{
    for (int i = 0; i < nb_stations; i++) {
        printf("Station %d -> degree %d\n",
               station_array[i].id_station,
               station_array[i].degree);
    }
}

// Fonction pour afficher les informations d'une station
static void show_station_info(Station *stations, int nb_stations) {
    int id;
    
    printf("Entrez l'identifiant de la station : ");
    scanf("%d", &id);
    
    // Chercher la station
    int found = 0;
    for (int i = 0; i < nb_stations; i++) {
        if (stations[i].id_station == id) {
            printf("Identifiant : %d\n", stations[i].id_station);
            printf("Degre sortant : %d\n", stations[i].degree);
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("Station non trouvee.\n");
    }
}

// Affiche tous les voisins d'une station avec le temps de trajet
static void display_neighbors(Station *stations, int nb_stations) {
    int id;
    Station *station = NULL;
    
    printf("Entrez l'identifiant de la station : ");
    scanf("%d", &id);
    
    // Chercher la station
    for (int i = 0; i < nb_stations; i++) {
        if (stations[i].id_station == id) {
            station = &stations[i];
            break;
        }
    }
    
    if (station == NULL) {
        printf("Station non trouvee.\n");
        return;
    }
    
    if (station->degree == 0) {
        printf("Aucun voisin.\n");
        return;
    }
    
    printf("Voisins de la station %d :\n", station->id_station);
    
    Edge *current = station->edges;
    while (current != NULL) {
        printf("  -> Station %d (temps: %d min)\n", 
            current->destination, current->time);
        current = current->next;
    }
}

// Handle the user's menu choice
static void handle_choice(int choice, Station *stations, int nb_stations) {
    switch (choice) {
        case 1:
            show_station_info(stations, nb_stations);
            break;

        case 2:
            display_neighbors(stations, nb_stations);
            break;

        case 3:
            calculer_chemin(stations, nb_stations);
            break;

        case 4: {
            // Change the function here to test other sorts
            int sort_algorithm = 4; // Hardcoded for Quick Sort as it is the best algorithm for our scenario
            Stat stat = sort_stations_by_degree(stations, nb_stations, sort_algorithm); // 0: Selection, 1: Insertion, 2: Bubble, 3: Merge, 4: Quick

            printf("\nSorted stations (by degree):\n");
            print_stations(stations, nb_stations);

            if (stat) {
                printf("\nComparisons: %d\n", stat->comparisons);
                printf("Swaps: %d\n", stat->swaps);
                free(stat);
            }
            break;
        }

        case 0:
            printf("Au revoir!\n");
            break;

        default:
            printf("Choix invalide. Veuillez reessayer.\n");
    }
}

// Call after data from text file is loaded and processed
void menu_loop(Station *stations, int nb_stations) {
    int choice = -1;

    // Main loop
    while (choice != 0) {
        show_menu();
        scanf("%d", &choice);
        handle_choice(choice, stations, nb_stations);
    }

    free(stations);
}