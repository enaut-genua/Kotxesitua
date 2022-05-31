#include "kotxea.h"


#include "input.h"
#ifdef RASPBERRY
#include "hardware.h"
#endif

/* FUNTZIO PRIBATUAK */

static void kotxea_ezkerreko_motorra_mugitu(void);
static void kotxea_ezkerreko_motorra_gelditu(void);
static void kotxea_eskubiko_motorra_mugitu(void);
static void kotxea_eskubiko_motorra_gelditu(void);
static void kotxea_bi_motorrak_mugitu(void);
static void kotxea_gelditu(void);
static PinEgoera kotxea_ezkerreko_ldr_irakurri(void);
static PinEgoera kotxea_eskubiko_ldr_irakurri(void);


void kotxea_urruneko_kontrola(void)
{
	while (input_init() == false)
	{
		ABISUA("Inputa ez da ondo konfiguratu, berriro saiatzen...\n");		
	}

	int c = 0;

	while ((c = getchar()) != 'e')
	{
		switch (c)
		{
		case 'w':
			kotxea_bi_motorrak_mugitu();
			break;
		case 'a':
			// Ezkerrera
			kotxea_eskubiko_motorra_mugitu();
			break;
		case 'd':
			// Eskubira
			kotxea_ezkerreko_motorra_mugitu();
			break;
		default:
			kotxea_gelditu();
			break;
		}
	}

	OHARRA("Urruneko kontroletik ateratzen...");

	while (input_destroy() == false)
	{
		ABISUA("Inputa ez da ondo borratu, berriro saiatzen...\n");	
	}
}

void kotxea_marra_jarraitu(void)
{
	OHARRA("Marra bat jarraitzen...");
	while (true)
	{
		if (kotxea_ezkerreko_ldr_irakurri() == Ezgaitu)
		{
			kotxea_ezkerreko_motorra_gelditu();
		}
		if (kotxea_eskubiko_ldr_irakurri() == Ezgaitu)
		{
			kotxea_eskubiko_motorra_gelditu();	
		}
		kotxea_bi_motorrak_mugitu();
	}
}

/* FUNTZIO PRIBATUEN DEKLARAZIOA */

static void kotxea_ezkerreko_motorra_mugitu(void)
{
	OHARRA("Ezkerreko motorra mugitzen...");
#ifdef RASPBERRY
	hardware_ezkerreko_motorra_piztu();
#endif
}

static void kotxea_ezkerreko_motorra_gelditu(void)
{
	OHARRA("Ezkerreko motorra gelditu.");
}

static void kotxea_eskubiko_motorra_mugitu(void)
{
	OHARRA("Eskubiko motorra mugitzen...");
#ifdef RASPBERRY
	hardware_eskubiko_motorra_piztu();
#endif
}

static void kotxea_eskubiko_motorra_gelditu(void)
{
	OHARRA("Eskubiko motorra gelditu.");
}

static void kotxea_bi_motorrak_mugitu(void)
{
	OHARRA("Bi motorrak batera mugitzen...");
#ifdef RASPBERRY
#endif
}

static void kotxea_gelditu(void)
{
	OHARRA("Kotxea geldirik.");
#ifdef RASPBERRY
#endif
}

static PinEgoera kotxea_ezkerreko_ldr_irakurri(void)
{
	PinEgoera sentsorearen_balioa = Ezgaitu;

#ifdef RASPBERRY
	sentsorearen_balioa = hardware_ezkerreko_ldr_irakurri();
#else
	char buf[BUF_SZ] = {0};

	printf("Eman ezkerreko sentsoreareran balorea (0, 1)?: ");
	BALIOA_ERABILI_GABE(fgets(buf, BUF_SZ, stdin));
	BALIOA_ERABILI_GABE(sscanf(buf, "%d", &sentsorearen_balioa));
#endif

	return sentsorearen_balioa;
}

static PinEgoera kotxea_eskubiko_ldr_irakurri(void)
{
	PinEgoera sentsorearen_balioa = Ezgaitu;

#ifdef RASPBERRY
	sentsorearen_balioa = hardware_eskubiko_ldr_irakurri();
#else
	char buf[BUF_SZ] = {0};

	printf("Eman eskubiko sentsoreareran balorea (0, 1)?: ");
	fgets(buf, BUF_SZ, stdin);
	sscanf(buf, "%d", &sentsorearen_balioa);
#endif

	return sentsorearen_balioa;
}