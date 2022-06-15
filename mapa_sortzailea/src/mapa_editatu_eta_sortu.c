#include "mapa_editatu_eta_sortu.h"
ERTZA* funtzioa_sortu_ertza() {
	ERTZA* ertz;
	ertz = (ERTZA*)malloc(sizeof(ERTZA));
	char str[128];
	printf("==================\n");
	printf("Puntua 1:\n");
	fgets(str, 32, stdin);
	(void)sscanf(str, "%d", &ertz->hasi);
	printf("Puntua 2:\n");
	fgets(str, 32, stdin);
	(void)sscanf(str, "%d", &ertz->bukatu);
	printf("Pisua:\n");
	fgets(str, 32, stdin);
	(void)sscanf(str, "%d", &ertz->pisua);
	printf("Orientazioa (Iparra: 1, Egoaldea: 2, Hekialdea: 3, Mendebaldea: 4):\n");
	fgets(str, 32, stdin);
	(void)sscanf(str, "%d", &ertz->orientazioa);
	ertz->hurrengo_ertza = NULL;
	return ertz;
}
ERTZA* funtzioa_sartu_ertza_kateatua(ERTZA* ptrBurua, ERTZA* ptrBerria) {
	if (ptrBurua == NULL) {
		ptrBurua = ptrBerria;
		ptrBurua->hurrengo_ertza = NULL;
	}
	else {
		ptrBerria->hurrengo_ertza = ptrBurua;
		ptrBurua = ptrBerria;
	}
	return ptrBurua;
}
MAPA* funtzioa_sortu_mapa(ERTZA* ertzak, int erpin_kop, int ertz_kop) {
	MAPA* mapa = NULL;
	mapa = (MAPA*)malloc(sizeof(MAPA));
	char str[32];
	if (mapa) {
		printf("==================\n");
		printf("Puntua Hasiera:\n");
		fgets(str, 32, stdin);
		(void)sscanf(str, "%d", &mapa->puntu_hasiera);
		printf("Puntua Bukaera:\n");
		fgets(str, 32, stdin);
		(void)sscanf(str, "%d", &mapa->puntu_bukaera);
		mapa->erpin_kopurua = erpin_kop;
		mapa->ertz_kopurua = ertz_kop;
		mapa->ertzak = ertzak;
		return mapa;
	}
	else
	{
		return 0;
	}
}
ERTZA* free_zerrenda(ERTZA* ptrBurua) {
	ERTZA* ptrAux = NULL;
	ptrAux = ptrBurua;

	while (ptrBurua != NULL) {
		ptrAux = ptrBurua;
		ptrBurua = ptrBurua->hurrengo_ertza;
		free(ptrAux);
	}
	return  NULL;
}
void funtzioa_editatu_ertza(ERTZA* ertza, int hasi, int bukatu)
{
	ERTZA* ertza_aux = ertza;
	char str[32];
	while (ertza_aux != NULL)
	{
		if (ertza_aux->hasi == hasi && ertza_aux->bukatu == bukatu || ertza_aux->hasi == bukatu && ertza_aux->bukatu == hasi)
		{
			printf("Pisu berria: ");
			fgets(str, 32, stdin);
			(void)sscanf(str, "%d", &ertza_aux->pisua);
			printf("Orientazio berria: ");
			fgets(str, 32, stdin);
			(void)sscanf(str, "%d", &ertza_aux->orientazioa);
			break;
		}
		ertza_aux = ertza_aux->hurrengo_ertza;
	}
}