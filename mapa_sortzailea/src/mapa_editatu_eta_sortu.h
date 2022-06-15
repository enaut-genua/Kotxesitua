#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
typedef struct ertza {
	int hasi;
	int bukatu;
	int pisua;
	int orientazioa;
	struct ertza* hurrengo_ertza;
}ERTZA;
typedef struct mapa
{
	int puntu_hasiera;
	int puntu_bukaera;
	int erpin_kopurua;
	int ertz_kopurua;
	ERTZA* ertzak;
} MAPA;
ERTZA* funtzioa_sortu_ertza();
ERTZA* funtzioa_sartu_ertza_kateatua(ERTZA* ptrBurua, ERTZA* ptrBerria);
MAPA* funtzioa_sortu_mapa(ERTZA* ertzak, int erpin_kop, int ertz_kop);
ERTZA* free_zerrenda(ERTZA* ptrBurua);
void funtzioa_editatu_ertza(ERTZA* ertza, int hasi, int bukatu);