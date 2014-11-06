#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "mbr.h"
#include "bloc.h"

extern struct superbloc_s sb;
extern struct mbr_s mbr;


static void empty_it()
{
    return;
}

int main (int argc, char **argv)
{
    int i;
    int current_volume_int;
    char* hw_config;
    char* current_volume;
    
    hw_config = getenv("HW_CONFIG");
    current_volume = getenv("CURRENT_VOLUME");
    current_volume_int = atoi(current_volume);

    /* init hardware */
    if(init_hardware(hw_config) == 0)
    {
	    fprintf(stderr, "Error in hardware initialization\n");
	    exit(EXIT_FAILURE);
    }

    /* Interreupt handlers */
    for(i=0; i<16; i++)
	    IRQVECTOR[i] = empty_it;

    /* Allows all IT */
    _mask(1);

    load_super(current_volume_int);
    
    printf("--------------------------------------------------------------------------------\n");
    printf("VOLUME %i\n", current_volume_int);
    printf("--------------------------------------------------------------------------------\n");
    printf("Serial: %i\n", sb.serial);
    printf("Name: %s\n", sb.name);
    printf("Premier libre: %i\n", sb.premier_libre);
    printf("Nb blocs libres: %i\n", sb.nb_blocs_libres);
    printf("Inoeud racine: %i\n", sb.inoeud_racine);
    printf("%% libre: %i %%\n", ((sb.nb_blocs_libres/mbr.vols[current_volume_int].nb_sec)*100));

    /* and exit! */
    exit(EXIT_SUCCESS);
}
