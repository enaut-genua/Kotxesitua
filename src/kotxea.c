#include "kotxea.h"

#include "input.h"

#ifdef RASPBERRY
#include "hardware.h"
#endif

/* ALDAGAI GLOBALAK */

static struct motore_egoera_t
{
	bool eskubi_piztuta;
	bool ezkerra_piztuta;
} MOTORE_EGOERA = {0};

/* FUNTZIO PRIBATUAK */

static void kotxea_ezkerreko_motorra_mugitu(void);
static void kotxea_ezkerreko_motorra_gelditu(void);
static void kotxea_eskubiko_motorra_mugitu(void);
static void kotxea_eskubiko_motorra_gelditu(void);
static void kotxea_bi_motorrak_mugitu(void);
static void kotxea_gelditu(void);
static PinEgoera kotxea_ezkerreko_ldr_irakurri(void);
static PinEgoera kotxea_eskubiko_ldr_irakurri(void);

/* FUNTZIO PUBLIKOEN INPLEMENTAZIOA */

bool kotxea_urruneko_kontrola(void)
{
	if (input_init() == false)
	{
		ERROREA("Inputa ez da ondo konfiguratu.");
		return false;
	}

	int c = 0;
	while (c != 'e')
	{
		while (input_tekla_sakatu_da())
		{
			c = getchar();
			switch (c)
			{
			case 'w':
				// Aurrera
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
			}
		}
		kotxea_gelditu();
	}

	if (input_destroy() == false)
	{
		ERROREA("Inputa ez da ondo borratu.");
		return false;
	}

	OHARRA("Urruneko kontroletik ateratzen...");

	return true;
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

/* FUNTZIO PRIBATUEN INPLEMENTAZIOA */

static void kotxea_ezkerreko_motorra_mugitu(void)
{
	if (MOTORE_EGOERA.ezkerra_piztuta == false)
	{
		OHARRA("Ezkerreko motorra mugitzen...");

		MOTORE_EGOERA.ezkerra_piztuta = true;
#ifdef RASPBERRY
		hardware_ezkerreko_motorra_piztu();
#endif
	}
}

static void kotxea_ezkerreko_motorra_gelditu(void)
{
	OHARRA("Ezkerreko motorra gelditu.");

	MOTORE_EGOERA.ezkerra_piztuta = false;
#ifdef RASPBERRY
	hardware_ezkerreko_motorra_itzali();
#endif
}

static void kotxea_eskubiko_motorra_mugitu(void)
{
	if (MOTORE_EGOERA.eskubi_piztuta == false)
	{
		OHARRA("Eskubiko motorra mugitzen...");

		MOTORE_EGOERA.eskubi_piztuta = true;
#ifdef RASPBERRY
		hardware_eskubiko_motorra_piztu();
#endif
	}
}

static void kotxea_eskubiko_motorra_gelditu(void)
{
	OHARRA("Eskubiko motorra gelditu.");

	MOTORE_EGOERA.eskubi_piztuta = false;
#ifdef RASPBERRY
	hardware_eskubiko_motorra_itzali();
#endif
}

static void kotxea_bi_motorrak_mugitu(void)
{
	if (MOTORE_EGOERA.eskubi_piztuta == false)
	{
		kotxea_eskubiko_motorra_mugitu();
	}
	if (MOTORE_EGOERA.ezkerra_piztuta == false)
	{
		kotxea_ezkerreko_motorra_mugitu();
	}
}

static void kotxea_gelditu(void)
{
	if (MOTORE_EGOERA.eskubi_piztuta)
	{
		kotxea_eskubiko_motorra_gelditu();
	}
	if (MOTORE_EGOERA.ezkerra_piztuta)
	{
		kotxea_ezkerreko_motorra_gelditu();
	}

	OHARRA("Kotxea geldituta.");
}

static PinEgoera kotxea_ezkerreko_ldr_irakurri(void)
{
	PinEgoera sentsorearen_balioa = Ezgaitu;

#ifdef RASPBERRY
	sentsorearen_balioa = hardware_ezkerreko_ldr_irakurri();
#else
	char buf[BUF_SZ] = {0};
	int irakurketa = 0;

	printf("Eman ezkerreko sentsoreareran balorea (0, 1)?: ");
	BALIOA_ERABILI_GABE(fgets(buf, BUF_SZ, stdin));
	BALIOA_ERABILI_GABE(sscanf(buf, "%d", &irakurketa));
	sentsorearen_balioa = irakurketa == 0 ? Ezgaitu : Gaitu;
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
	int irakurketa = 0;

	printf("Eman eskubiko sentsoreareran balorea (0, 1)?: ");
	BALIOA_ERABILI_GABE(fgets(buf, BUF_SZ, stdin));
	BALIOA_ERABILI_GABE(sscanf(buf, "%d", &irakurketa));
	sentsorearen_balioa = irakurketa == 0 ? Ezgaitu : Gaitu;
#endif

	return sentsorearen_balioa;
}