#ifndef DIJSKTRA_H
#define DIJKSTRA_H

#include "includes.h"

typedef enum
{
    Inora,
    Iparraldea,
    Hegoaldea,
    Ekialdea,
    Mendebaldea
} Norabidea;

void dijsktra_init(void);
void dijkstra_borratu(void);

#endif