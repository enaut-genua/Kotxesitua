#include "dijkstra.h"

PATH *dijkstra(int **matrizea, int erpin_kopurua, int hasierako_puntua, int bukaerako_puntua)
{
	PATH *camino = (PATH *)malloc(sizeof(PATH));
	int *egindako_bidea = (int *)calloc(erpin_kopurua, sizeof(int));
	int erpin_kop = erpin_kopurua * erpin_kopurua;
	int *pisua = (int *)calloc(erpin_kopurua, sizeof(int) * erpin_kopurua);
	int *egondako_erpinetan = (int *)calloc(erpin_kopurua, sizeof(int) * erpin_kopurua);
	int *bidea_dijkstra = (int *)calloc(erpin_kopurua, sizeof(int) * erpin_kopurua);
	int **matrize_pisua_kopia = sortu_matrizea(erpin_kop);
	int count = 0, distantzia_minimoa = 0, hurrengo_nodoa = 0, i = 0, j = 0;
	int tamaina = 1;
	// hasta este punto creamos todas las bariables necesarias para guardar los datos
	if (bidea_dijkstra == NULL || egindako_bidea == NULL || pisua == NULL || egondako_erpinetan == NULL || matrize_pisua_kopia == NULL)
	{
		exit(EXIT_FAILURE);
	}
	matrizea_pisua_kopia(erpin_kopurua, matrizea, matrize_pisua_kopia);
	// inicialiazmos pisua[],bidea_dijkstra[] and egindako_erpinetan[]
	for (i = 0; i < erpin_kopurua; i++)
	{
		pisua[i] = matrize_pisua_kopia[hasierako_puntua][i];
		bidea_dijkstra[i] = hasierako_puntua;
		egondako_erpinetan[i] = 0;
	}
	pisua[hasierako_puntua] = 0;
	egondako_erpinetan[hasierako_puntua] = 1;
	count = 1;
	while (count < erpin_kopurua - 1)
	{
		distantzia_minimoa = INFINITO;
		// haze el camino con menos peso
		for (i = 0; i < erpin_kopurua; i++)
			if (pisua[i] < distantzia_minimoa && !egondako_erpinetan[i])
			{
				distantzia_minimoa = pisua[i];
				hurrengo_nodoa = i;
				tamaina++;
			}
		// revisa si exise un camino mejor
		egondako_erpinetan[hurrengo_nodoa] = 1;
		for (i = 0; i < erpin_kopurua; i++)
			if (!egondako_erpinetan[i])
				if (distantzia_minimoa + matrize_pisua_kopia[hurrengo_nodoa][i] < pisua[i])
				{
					pisua[i] = distantzia_minimoa + matrize_pisua_kopia[hurrengo_nodoa][i];
					bidea_dijkstra[i] = hurrengo_nodoa;
				}
		count++;
	}
	int *instrukzio_bidea = (int *)calloc(tamaina + 1, sizeof(int));
	int tmp = 0;
	if (instrukzio_bidea)
	{
		// guarda el camino en un array
		if (i != hasierako_puntua)
		{
			egindako_bidea[bukaerako_puntua] = bukaerako_puntua;
			j = bukaerako_puntua;
			instrukzio_bidea[0] = bukaerako_puntua;
			do
			{
				if (tmp > tamaina)
				{
					tmp = tamaina;
				}
				tmp = tmp + 1;
				instrukzio_bidea[tmp] = bidea_dijkstra[j];
				j = bidea_dijkstra[j];
			} while (j != hasierako_puntua);
		}
	}
	camino->path = instrukzio_bidea;
	camino->tamaina = tmp;
	return camino; // se devuelve la estructura con el camino y el tama�o de puntos recorridos
}
Norabidea *dijkstra_bidea_pausoka(int tamaina, int **matrize_orientazioa, int *bidea)
{
	Norabidea *instrukzioak = (Norabidea *)calloc((tamaina), sizeof(Norabidea));
	if (instrukzioak)
	{
		for (int k = 0; k < (tamaina); k++)
		{
			switch (matrize_orientazioa[bidea[k]][bidea[k + 1]])
			{ // mira de que punto a que punto va y coje la orientacion de la matriz de orientazion
			case 1:
				instrukzioak[k] = Iparraldea;
				break;
			case 2:
				instrukzioak[k] = Hegoaldea;
				break;
			case 3:
				instrukzioak[k] = Ekialdea;
				break;
			case 4:
				instrukzioak[k] = Mendebaldea;
				break;
			case 0:
				instrukzioak[k] = Inora;
				break;
			}
		}
	}
	return instrukzioak;
}

void bete_matrize_pisua(int **matrizea, ERTZA *ertza, int ertza_kop)
{
	ERTZA *aux = ertza;
	for (int j = 0; j < ertza_kop; j++) // les damos los valores de las ertzas a cada lugar de la matriz
	{
		matrizea[aux->hasi - 1][aux->bukatu - 1] = aux->pisua;
		matrizea[aux->bukatu - 1][aux->hasi - 1] = aux->pisua;
		aux = aux->hurrengo_ertza;
	}
}
void bete_matrize_orientazioa(int **matrizea, ERTZA *ertza, int ertza_kop, int erpin_kop)
{
	ERTZA *kopia = ertza;
	for (int j = 0; j < ertza_kop; j++) // les damos los valores de las ertzas a cada lugar de la matriz
	{
		matrizea[kopia->hasi - 1][kopia->bukatu - 1] = kopia->orientazioa;
		matrizea[kopia->bukatu - 1][kopia->hasi - 1] = kopia->orientazioa;
		kopia = kopia->hurrengo_ertza;
	}
	matrizea_zuzendu_orientazioa(matrizea, erpin_kop); // corrigue la matriz para evitar direcciones equivocadas
}
void matrizea_pisua_kopia(int erpin_kopurua, int **matrize_originala, int **matrize_kopia)
{
	int i, j;
	for (i = 0; i < erpin_kopurua; i++)
	{
		for (j = 0; j < erpin_kopurua; j++)
		{
			if (matrize_originala[i][j] == 0)
			{
				matrize_kopia[i][j] = INFINITO;
			}
			else
			{
				matrize_kopia[i][j] = matrize_originala[i][j];
			}
		}
	}
}
void matrizea_zuzendu_orientazioa(int **matrizea, int erpin_kop)
{
	for (int i = 0; i < erpin_kop; i++)
	{
		for (int j = 0; j < erpin_kop; j++)
		{
			switch (matrizea[i][j])
			{
			case 1:
				matrizea[j][i] = 3;
				break;
			case 2:
				matrizea[j][i] = 4;
				break;
			case 3:
				matrizea[j][i] = 1;
				break;
			case 4:
				matrizea[j][i] = 2;
				break;
			default:
				matrizea[j][i] = 0;
				break;
			}
		}
	}
}

MAPA *funtzioa_irakurri_binari_artxiboa()
{

	MAPA *mapa = (MAPA *)malloc(sizeof(MAPA));
	if (mapa == NULL)
	{
		exit(EXIT_FAILURE);
	}
	FILE *irakurritako_artxiboa = NULL;
	irakurritako_artxiboa = fopen("dijkstra.mapa", "rb");
	uint8_t *mapa_struct_byte = (uint8_t *)mapa;
	for (int i = 0; i < 16; i++)
	{
		fread(mapa_struct_byte + i, sizeof(uint8_t), 1, irakurritako_artxiboa);
	}
	ERTZA *ertzak = (ERTZA *)malloc(sizeof(ERTZA));
	if (ertzak == NULL)
	{
		exit(EXIT_FAILURE);
	}
	ERTZA *kopia = ertzak;
	if (kopia)
	{
		uint8_t *mapa_ertzak_byte = (uint8_t *)kopia;
		for (int j = 0; j < mapa->ertz_kopurua; j++)
		{
			for (size_t i = 0; i < (sizeof(int) * 4); i++)
			{
				fread(mapa_ertzak_byte + i, sizeof(uint8_t), 1, irakurritako_artxiboa);
			}
			if (j != mapa->ertz_kopurua - 1)
			{
				if (kopia)
				{
					kopia->hurrengo_ertza = (ERTZA *)malloc(sizeof(ERTZA));
					kopia = kopia->hurrengo_ertza;
					mapa_ertzak_byte = (uint8_t *)kopia;
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

int **sortu_matrizea(int erpin_kop)
{
	int **matrize_ustua = (int **)calloc(erpin_kop, sizeof(int *)); // creamos la matriz ejem: array[[], [], [], []]
	if (matrize_ustua)
	{
		for (int i = 0; i < erpin_kop; i++)
		{
			matrize_ustua[i] = (int *)calloc(erpin_kop, sizeof(int));
		}
		inizializatu(matrize_ustua, erpin_kop); // ponemos todos a 0 ejem: array[[0, 0][0, 0]]
		return matrize_ustua;
	}
	else
	{
		return 0;
	}
}
void inizializatu(int **matrizea, int erpin_kop)
{
	for (int i = 0; i < erpin_kop; i++)
	{
		for (int j = 0; j < erpin_kop; j++)
		{
			matrizea[i][j] = 0;
		}
	}
}

void liberatu_matrizea(int **matrizea, int erpin_kop)
{
	for (int q = 0; q < erpin_kop; q++)
	{
		free(matrizea[q]);
	}
	free(matrizea);
}

Norabidea *dijkstra_main(int *tamainaa)
{

	MAPA *mapa = funtzioa_irakurri_binari_artxiboa();
	// inportamos el mapa
	PATH *bidea;
	// creamos una struct para guardar el camino
	int **matrizea = sortu_matrizea(mapa->erpin_kopurua);														 // creamos una matriz de peso vacia
	int **matrize_orienta = sortu_matrizea(mapa->erpin_kopurua);												 // creamos una matriz de orientazion vacia
	bete_matrize_pisua(matrizea, mapa->ertzak, mapa->ertz_kopurua);												 // le a�adimos los datos importados del mapa a la matriz de peso
	bete_matrize_orientazioa(matrize_orienta, mapa->ertzak, mapa->ertz_kopurua, mapa->erpin_kopurua);			 // le a�adimos los datos importados del mapa a la matriz de orientazion
	bidea = dijkstra(matrizea, mapa->erpin_kopurua, (mapa->puntu_bukaera - 1), (mapa->puntu_hasiera - 1));		 // hacemos el proceso de dijkstra
	Norabidea *instrukzioak = (Norabidea *)dijkstra_bidea_pausoka(bidea->tamaina, matrize_orienta, bidea->path); // sabiendo los puntos por los que pasa, hacemos una array de instrucciones
	*tamainaa = bidea->tamaina;
	liberatu_matrizea(matrizea, mapa->erpin_kopurua);
	liberatu_matrizea(matrize_orienta, mapa->erpin_kopurua);
	free(bidea);
	free(mapa);

	return instrukzioak;
}
