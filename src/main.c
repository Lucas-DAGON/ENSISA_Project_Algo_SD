#include <stdio.h>
#include "../include/structs.h"
#include "../include/menu.h"
#include "../include/read_file.h"

int main(int argc, char **argv) {
    Station *stations;
    int n = 0;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"fichier.txt\"\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    stations = read_station_file(argv[1], &n);
    if (!stations)
        return EXIT_FAILURE;
    
    printf("Reseau charge: %d stations\n", n);
    
    menu_loop(stations, n);
    
    return EXIT_SUCCESS;
}