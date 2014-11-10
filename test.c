#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hardware.h"
#include "drive.h"
#include "bloc.h"
#include "mbr.h"

static void empty_it()
{
    return;
}

int main (int argc, char **argv)
{
    unsigned int i;
    int bloc;
    int current_volume_int;
    char* hw_config;
    char* current_volume;
    int rnd;
    
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

    read_mbr();
    load_super(current_volume_int);

    do
    {
        bloc = new_bloc();
        printf("%i new_bloc()\n",bloc);
    } while(bloc);

    for(i=0; i<10; i++)
    {
        rnd = (rand() % 99) + 1;
        printf("free_bloc(%i)\n",rnd);
        free_bloc(rnd);
    }
    
    for(i=0; i<3; i++)
    {
        bloc = new_bloc();
        printf("%i new_bloc()\n",bloc);
    }

    /* and exit! */
    exit(EXIT_SUCCESS);
}
