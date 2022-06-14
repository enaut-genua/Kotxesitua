#include "dijkstra.h"

#include "includes.h"

typedef struct ertza_t
{
	int hasi;
	int bukatu;
	int pisua;
	int orientazioa;
	struct ertza_t *hurrengo_ertza;
} Ertza;

typedef struct
{
	int puntu_hasiera;
	int puntu_bukaera;
	int erpin_kopurua;
	int ertz_kopurua;
	Ertza *ertzak;
} Mapa;

typedef struct
{
	int tamaina;
	int *path;
} Path;

// Bariable globalak
static Mapa *mapa = NULL;
static int **pisu_matr = NULL;
static Norabidea **norab_matr = NULL;

// Funtzio pribatuak
static void dijsktra_kargatu_mapa(Mapa *mapa);
static int **dijkstra_matrizea_sortu(int erpin_kop);
static void dijkstra_matrizea_borratu(int **matrizea, int erpin_kop);
static void dijkstra_matrize_pisua_bete(int **matrizea, Ertza *ertza, int ertz_kop);
static void dijkstra_matrize_orientazioa_bete(int **matrizea, Ertza *ertza, int ertz_kop);

// Funtzio publikoak

void dijsktra_init(void)
{
	mapa = (Mapa *)malloc(sizeof(Mapa));
	dijsktra_kargatu_mapa(mapa);
	pisu_matr = dijkstra_matrizea_sortu(mapa->erpin_kopurua);
	norab_matr = (Norabidea **)dijkstra_matrizea_sortu(mapa->erpin_kopurua);

}

void dijkstra_borratu(void)
{
	free(mapa->ertzak);
	free(mapa);
	mapa = NULL;
}

// Funtzio pribatuak

static void dijsktra_kargatu_mapa(Mapa *mapa)
{
	if (mapa == NULL)
	{
		exit(EXIT_FAILURE);
	}
	FILE *irakurritako_artxiboa = NULL;
	irakurritako_artxiboa = fopen("dijkstra.mapa", "rb");
	uint8_t *mapa_struct_byte = (uint8_t *)mapa;
	for (size_t i = 0; i < sizeof(int) * 4; i++)
	{
		fread(mapa_struct_byte + i, sizeof(uint8_t), 1, irakurritako_artxiboa);
	}
	Ertza *ertzak = (Ertza *)malloc(sizeof(Ertza));
	if (ertzak == NULL)
	{
		exit(EXIT_FAILURE);
	}
	Ertza *aux = ertzak;
	if (aux)
	{
		uint8_t *mapa_ertzak_byte = (uint8_t *)aux;
		for (int j = 0; j < mapa->ertz_kopurua; j++)
		{
			for (size_t i = 0; i < (sizeof(int) * 4); i++)
			{
				fread(mapa_ertzak_byte + i, sizeof(uint8_t), 1, irakurritako_artxiboa);
			}
			if (j != mapa->ertz_kopurua - 1)
			{
				if (aux)
				{
					aux->hurrengo_ertza = (Ertza *)malloc(sizeof(Ertza));
					aux = aux->hurrengo_ertza;
					mapa_ertzak_byte = (uint8_t *)aux;
				}
			}
			else
			{
				if (aux)
				{
					aux->hurrengo_ertza = NULL;
				}
			}
		}
	}
	mapa->ertzak = ertzak;
}

static int **dijkstra_matrizea_sortu(int erpin_kop)
{
	int **matrizea = (int **)calloc(erpin_kop, sizeof(int *));
	if (matrizea != NULL)
	{
		for (int i = 0; i < erpin_kop; i++)
		{
			matrizea[i] = (int *)calloc(erpin_kop, sizeof(int));
		}
	}

	return matrizea;
}

static void dijkstra_matrizea_borratu(int **matrizea, int erpin_kop)
{
	for (int i = 0; i < erpin_kop; i++)
	{
		free(matrizea[i]);
	}
	free(matrizea);
}