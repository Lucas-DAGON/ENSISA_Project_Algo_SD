#include <stdio.h>
#include <stdlib.h>
#include "../include/menu.h"
#include "../include/sort.h"
#include "../include/structs.h"

static void show_menu() {
    printf("==== MENU RESEAU DE TRANSPORT ====\n");
    printf("1 - Afficher les informations d'une station\n");
    printf("2 - Lister les voisins d'une station\n");
    printf("3 - Calculer un chemin minimal\n");
    printf("4 - Afficher les stations triées par degré\n");
    printf("0 - Quitter\n");
    printf("Votre choix : ");
}

static void print_stations(const Station *station_array, int n)
{
    for (int i = 0; i < n; i++) {
        printf("Station %d -> degree %d\n",
               station_array[i].id_station,
               station_array[i].degree);
    }
}

static void handle_choice(int choice, Station *stations, int n) {
    switch (choice) {
        case 1:
            // Code pour afficher les informations d'une station
            break;

        case 2:
            // Code pour lister les voisins d'une station
            break;

        case 3:
            // Code pour calculer un chemin minimal
            break;

        case 4: {
            // Change the function here to test other sorts
            Stat stat = sort_stations_by_degree(stations, n, 5); // 1: Selection, 2: Insertion, 3: Bubble, 4: Merge, 5: Quick

            printf("\nSorted stations (by degree):\n");
            print_stations(stations, n);

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
            printf("Choix invalide. Veuillez réessayer.\n");
    }
}

// Call after data from file is loaded and processed
void menu_loop(Station *stations, int n) {
    int choice = -1;

    // Main loop
    while (choice != 0) {
        show_menu();
        scanf("%d", &choice);
        handle_choice(choice, stations, n);
    }

    free(stations);
}