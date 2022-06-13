#include "kotxea.h"
#include "input.h"

#ifdef RASPBERRY
#include "hardware.h"
#endif

/* DATU MOTA PRIBATUAK */

typedef struct
{
	bool azeleratu;
	int potentzia_balioa;
} Motorea;

typedef struct
{
	int potentzia_limitea;
	int interbaloa;
	Motorea mot_eskubi;
	Motorea mot_ezkerra;
} Kotxea;

/* FUNTZIO PRIBATUAK */

static bool kotxea_init(Kotxea *kotxea);
static void kotxea_ezkerreko_motorra_azeleratu(Kotxea *kotxea);
static void kotxea_ezkerreko_motorra_frenatu(Kotxea *kotxea);
static void kotxea_eskubiko_motorra_azeleratu(Kotxea *kotxea);
static void kotxea_eskubiko_motorra_frenatu(Kotxea *kotxea);

static PinEgoera kotxea_ezkerreko_ldr_irakurri(void);
static PinEgoera kotxea_eskubiko_ldr_irakurri(void);

static bool kotxea_nodo_aurkitu(void);

/* FUNTZIO PUBLIKOEN INPLEMENTAZIOA */

bool kotxea_init(Kotxea *kotxea)
{
	bool ret = true;

#ifdef RASPBERRY
	ret = hardware_init(kotxea->potentzia_limitea);
#else
	BALIOA_ERABILI_GABE(kotxea);
#endif

	OHARRA("Kotxea prest.");

	return ret;
}

bool kotxea_urruneko_kontrola(void)
{
	OHARRA("Urruneko kontrola.");

	Kotxea kotxea = {.potentzia_limitea = POTENTZIA_MAX, .interbaloa = kotxea.potentzia_limitea};

	if (kotxea_init(&kotxea) == false)
	{
		ERROREA("kotxea_urruneko_kontrola(): Kotxea ezin izan da prestatu.");
		return false;
	}

	if (input_init() == false)
	{
		ERROREA("kotxea_urruneko_kontrola(): Inputa ez da ondo konfiguratu.");
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
				kotxea_eskubiko_motorra_azeleratu(&kotxea);
				kotxea_ezkerreko_motorra_azeleratu(&kotxea);
				break;
			case 'a':
				// Ezkerrera
				kotxea_ezkerreko_motorra_azeleratu(&kotxea);

				break;
			case 'd':
				// Eskubira
				kotxea_eskubiko_motorra_azeleratu(&kotxea);
				break;
			}
		}
		kotxea_eskubiko_motorra_frenatu(&kotxea);
		kotxea_ezkerreko_motorra_frenatu(&kotxea);
	}

	if (input_destroy() == false)
	{
		ABISUA("Inputa ez da ondo borratu.");
	}

	OHARRA("Urruneko kontroletik ateratzen...");

	return true;
}

bool kotxea_marra_jarraitu(void)
{
	OHARRA("Marra bat jarraitu.");

	Kotxea kotxea = {.potentzia_limitea = 30, .interbaloa = kotxea.potentzia_limitea - 1};

	if (kotxea_init(&kotxea) == false)
	{
		ERROREA("kotxea_marra_jarraitu(): Kotxea ezin izan da prestatu.");
		return false;
	}

	kotxea_nodo_aurkitu();
	while (/*kotxea_nodo_aurkitu() == false*/ true)
	{
		if (kotxea_ezkerreko_ldr_irakurri() == Gaitu)
		{
			kotxea_ezkerreko_motorra_frenatu(&kotxea);
		}
		else
		{
			kotxea_ezkerreko_motorra_azeleratu(&kotxea);
		}

		if (kotxea_eskubiko_ldr_irakurri() == Gaitu)
		{
			kotxea_eskubiko_motorra_frenatu(&kotxea);
		}
		else
		{
			kotxea_eskubiko_motorra_azeleratu(&kotxea);
		}
	}

	OHARRA("Helmugara iritsita.");

	return true;
}

/* FUNTZIO PRIBATUEN INPLEMENTAZIOA */

static void kotxea_ezkerreko_motorra_azeleratu(Kotxea *kotxea)
{
	OHARRA("Ezkerreko motorra azeleratu.");

	kotxea->mot_ezkerra.azeleratu = true;
	kotxea->mot_ezkerra.potentzia_balioa += (kotxea->mot_ezkerra.potentzia_balioa < kotxea->potentzia_limitea) ? kotxea->interbaloa : 0;

#ifdef RASPBERRY
	hardware_ezkerreko_motorra_potentzia(kotxea->mot_ezkerra.potentzia_balioa);
#endif
}

static void kotxea_ezkerreko_motorra_frenatu(Kotxea *kotxea)
{
	OHARRA("Ezkerreko motorra frenatu.");

	kotxea->mot_ezkerra.azeleratu = false;
	kotxea->mot_ezkerra.potentzia_balioa -= (kotxea->mot_ezkerra.potentzia_balioa > 0) ? kotxea->interbaloa : 0;

#ifdef RASPBERRY
	hardware_ezkerreko_motorra_potentzia(kotxea->mot_ezkerra.potentzia_balioa);
#endif
}

static void kotxea_eskubiko_motorra_azeleratu(Kotxea *kotxea)
{
	OHARRA("Eskubiko motorra azeleratu.");

	kotxea->mot_eskubi.azeleratu = true;
	kotxea->mot_eskubi.potentzia_balioa += (kotxea->mot_eskubi.potentzia_balioa < kotxea->potentzia_limitea) ? kotxea->interbaloa : 0;

#ifdef RASPBERRY
	hardware_eskubiko_motorra_potentzia(kotxea->mot_ezkerra.potentzia_balioa);
#endif
}

static void kotxea_eskubiko_motorra_frenatu(Kotxea *kotxea)
{
	OHARRA("Eskubiko motorra frenatu.");

	kotxea->mot_eskubi.azeleratu = false;
	kotxea->mot_eskubi.potentzia_balioa -= (kotxea->mot_eskubi.potentzia_balioa > 0) ? kotxea->interbaloa : 0;

#ifdef RASPBERRY
	hardware_eskubiko_motorra_potentzia(kotxea->mot_eskubi.potentzia_balioa);
#endif
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

static bool kotxea_nodo_aurkitu(void)
{
	return (kotxea_ezkerreko_ldr_irakurri() == Gaitu && kotxea_eskubiko_ldr_irakurri() == Gaitu);
}