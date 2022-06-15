#ifndef DIJSKTRA_H
#define DIJKSTRA_H

#include "includes.h"

#define INFINITO 9999

typedef enum
{
    Inora,
    Iparraldea,
    Hegoaldea,
    Ekialdea,
    Mendebaldea
} Norabidea;

typedef struct ertza
{
    int hasi;
    int bukatu;
    int pisua;
    int orientazioa;
    struct ertza *hurrengo_ertza;
} ERTZA;

typedef struct mapa
{
    int puntu_hasiera;
    int puntu_bukaera;
    int erpin_kopurua;
    int ertz_kopurua;
    ERTZA *ertzak;
} MAPA;

typedef struct path
{
    int tamaina;
    int *path;
} PATH;

void matrizea_pisua_kopia(int erpin_kopurua, int **matrize_originala, int **matrize_kopia);
void bete_matrize_orientazioa(int **matrizea, ERTZA *ertza, int ertza_kop, int erpin_kop);
void matrizea_zuzendu_orientazioa(int **matrizea, int erpin_kop);
void bete_matrize_pisua(int **matrizea, ERTZA *ertza, int ertza_kop);

PATH *dijkstra(int **matrizea, int erpin_kopurua, int hasierako_puntua, int bukaerako_puntua);
Norabidea *dijkstra_bidea_pausoka(int tamaina, int **matrize_orientazioa, int *bidea);

void liberatu_matrizea(int **matrizea, int erpin_kop);

MAPA *funtzioa_irakurri_binari_artxiboa();

void inizializatu(int **matrizea, int erpin_kop);
int **sortu_matrizea(int erpin_kop);

Norabidea *dijkstra_main(int *tamaina);

#endif