#include "kotxea.h"

void kotxea_ezkerreko_motorra_mugitu(void)
{
#ifdef RASPBERRY
	// Wiring pi
#else
	printf("Ezkerreko motorra mugitzen...\n");
#endif
}

void kotxea_eskubiko_motorra_mugitu(void)
{
#ifdef RASPBERRY
	// Wiring pi
#else
	printf("Eskubiko motorra mugitzen...\n");
#endif
}

int kotxea_eskubiko_ldr_irakurri(void)
{
	int sentsorearen_balioa = 0;

#ifdef RASPBERRY

#else
	char buf[BUF_SZ] = {0};

	printf("Eman eskubiko sentsoreareran balorea (0, 1)?: ");
	fgets(buf, BUF_SZ, stdin);
	sscanf(buf, "%d", &sentsorearen_balioa);
#endif

	return sentsorearen_balioa;
}

int kotxea_ezkerreko_ldr_irakurri(void)
{
	int sentsorearen_balioa = 0;

#ifdef RASPBERRY

#else
	char buf[BUF_SZ] = {0};

	printf("Eman ezkerreko sentsoreareran balorea (0, 1)?: ");
	ERABILI_GABE(fgets(buf, BUF_SZ, stdin));
	ERABILI_GABE(sscanf(buf, "%d", &sentsorearen_balioa));
#endif

	return sentsorearen_balioa;
}