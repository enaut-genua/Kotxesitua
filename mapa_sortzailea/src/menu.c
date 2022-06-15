#include "menu.h"
int menua()
{
	int aukera;
	char str[128];
	printf("============================================\n\n");
	printf("                   MENUA                    ");
	printf("\n\n============================================\n");
	printf("1: Mapa bat sortu\n");
	printf("2: Mapa bat editatu\n");
	printf("3: Hasierako eta bukaerako puntuak editatu\n");
	printf("0: Irten\n");
	printf("============================================\n");

	fgets(str, 128, stdin);
	(void)sscanf(str, "%d", &aukera);

	return aukera;
}
void aukera_exekutatu(int aukera)
{
	char str[128];
	int erpin_kopuru = 0, ertza_kopuru = 0, jarrai = 0, nodo_hasi = 0, nodo_bukatu = 0;
	MAPA* mapa_irakurri = NULL;
	switch (aukera) {
	case 1:
		printf("=======MAPA SORTU=============\n");
		printf("Erpin kopurua:\n");
		fgets(str, 32, stdin);
		(void)sscanf(str, "%d", &erpin_kopuru);
		printf("Ertza kopurua:\n");
		fgets(str, 32, stdin);
		(void)sscanf(str, "%d", &ertza_kopuru);
		ERTZA* ertzak = NULL;
		ERTZA* ertza_berria = NULL;
		for (int i = 0; i < ertza_kopuru; i++)
		{
			ertza_berria = funtzioa_sortu_ertza();
			ertzak = funtzioa_sartu_ertza_kateatua(ertzak, ertza_berria);
		}
		MAPA* mapa = NULL;
		mapa = funtzioa_sortu_mapa(ertzak, erpin_kopuru, ertza_kopuru);
		funtzioa_sortu_binari_artxiboa(mapa, ertza_kopuru);
		free_zerrenda(ertzak);
		free(mapa);
		break;
	case 2:
		printf("=======MAPA EDITATU=============\n");
		do {
			mapa_irakurri = funtzioa_irakurri_binari_artxiboa();
			printf("Nodoaren asiera:\n");
			fgets(str, 32, stdin);
			(void)sscanf(str, "%d", &nodo_hasi);
			printf("Nodoaren bukaera:\n");
			fgets(str, 32, stdin);
			(void)sscanf(str, "%d", &nodo_bukatu);
			funtzioa_editatu_ertza(mapa_irakurri->ertzak, nodo_hasi, nodo_bukatu);
			jarraitu(jarrai);
		} while (jarrai);
		funtzioa_sortu_binari_artxiboa(mapa_irakurri, mapa_irakurri->ertz_kopurua);
		free(mapa_irakurri);
		break;
	case 3:
		mapa_irakurri = funtzioa_irakurri_binari_artxiboa();
		printf("=======HASI ETA BUKATU=============\n");
		printf("Hasierako puntu berria:\n");
		fgets(str, 32, stdin);
		(void)sscanf(str, "%d", &mapa_irakurri->puntu_hasiera);
		printf("Bukaerako puntu berria:\n");
		fgets(str, 32, stdin);
		(void)sscanf(str, "%d", &mapa_irakurri->puntu_bukaera);
		funtzioa_sortu_binari_artxiboa(mapa_irakurri, mapa_irakurri->ertz_kopurua);
		free(mapa_irakurri);
		break;
	}
}
int jarraitu() {
	char str[32];
	int jarraitu = 0;
	printf("Nodo gehiago editatu nahi dituzu?(0-Ez, 1-BAI)");
	fgets(str, 32, stdin);
	(void)sscanf(str, "%i", &jarraitu);
	return jarraitu;
}