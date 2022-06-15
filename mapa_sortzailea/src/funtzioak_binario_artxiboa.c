#include "funtzioak_binario_artxiboa.h"
void funtzioa_sortu_binari_artxiboa(MAPA* mapa, int nodo_kopurua) {
	uint8_t* mapa_struct_byte = (uint8_t*)mapa;
	FILE* sortutako_artxiboa = NULL;
	sortutako_artxiboa = fopen("dijkstra.mapa", "wb");
	for (int i = 0; i < (sizeof(int) * 4); i++)
	{
		fwrite(mapa_struct_byte + i, sizeof(uint8_t), 1, sortutako_artxiboa);
	}
	ERTZA* ertzal = mapa->ertzak;
	uint8_t* mapa_ertza_byte = (uint8_t*)ertzal;
	for (int i = 0; i < nodo_kopurua; i++) {
		for (int j = 0; j < (sizeof(int) * 4); j++) {
			fwrite(mapa_ertza_byte + j, sizeof(uint8_t), 1, sortutako_artxiboa);
		}
		ertzal = ertzal->hurrengo_ertza;
		mapa_ertza_byte = (uint8_t*)ertzal;
	}
	fclose(sortutako_artxiboa);
}
MAPA* funtzioa_irakurri_binari_artxiboa() 
{
	MAPA* mapa = (MAPA*)malloc(sizeof(MAPA));
	if (mapa == NULL)
	{
		exit(EXIT_FAILURE);
	}
	FILE* irakurritako_artxiboa = NULL;
	irakurritako_artxiboa = fopen("dijkstra.mapa", "rb");
	uint8_t* mapa_struct_byte = (uint8_t*)mapa;
	for (int i = 0; i < 16; i++) {
		fread(mapa_struct_byte + i, sizeof(uint8_t), 1, irakurritako_artxiboa);
	}
	ERTZA* ertzak = (ERTZA*)malloc(sizeof(ERTZA));
	if (ertzak == NULL)
	{
		exit(EXIT_FAILURE);
	}
	ERTZA* kopia = ertzak;
	if (kopia) {
		uint8_t* mapa_ertzak_byte = (uint8_t*)kopia;
		for (int j = 0; j < mapa->ertz_kopurua; j++)
		{
			for (int i = 0; i < (sizeof(int) * 4); i++)
			{
				fread(mapa_ertzak_byte + i, sizeof(uint8_t), 1, irakurritako_artxiboa);
			}
			if (j != mapa->ertz_kopurua - 1)
			{
				if (kopia)
				{
					kopia->hurrengo_ertza = (ERTZA*)malloc(sizeof(ERTZA));
					kopia = kopia->hurrengo_ertza;
					mapa_ertzak_byte = (uint8_t*)kopia;
				}
			}
			else
			{
				if (kopia)
				{
					kopia->hurrengo_ertza = NULL;
				}
			}
		}
	}
	mapa->ertzak = ertzak;
	return mapa;
}