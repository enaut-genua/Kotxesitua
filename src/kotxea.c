#include "kotxea.h"
#include "input.h"
#include "dijkstra.h"

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
	Norabidea aurrea;
	Motorea mot_eskubi;
	Motorea mot_ezkerra;
} Kotxea;

/* FUNTZIO PRIBATUAK */

static bool kotxea_init(const Kotxea *kotxea);
static void kotxea_itzali(void);

static void kotxea_ezkerreko_motorra_azeleratu(Kotxea *kotxea);
static void kotxea_ezkerreko_motorra_frenatu(Kotxea *kotxea);
static void kotxea_eskubiko_motorra_azeleratu(Kotxea *kotxea);
static void kotxea_eskubiko_motorra_frenatu(Kotxea *kotxea);

static PinEgoera kotxea_ezkerreko_ldr_irakurri(void);
static PinEgoera kotxea_eskubiko_ldr_irakurri(void);

static bool kotxea_nodo_aurkitu(void);

static void kotxea_giratu_eskubira(Kotxea *kotxea);
static void kotxea_giratu_ezkerrera(Kotxea *kotxea);
static void kotxea_giratu_aurrera(Kotxea *kotxea);

/* FUNTZIO PUBLIKOEN INPLEMENTAZIOA */

bool kotxea_init(const Kotxea *kotxea)
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

static void kotxea_itzali(void)
{
	OHARRA("Kotxea gelditu.");

#ifdef RASPBERRY
	hardware_eskubiko_motorra_potentzia(0);
	hardware_ezkerreko_motorra_potentzia(0);
#endif
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
				kotxea_eskubiko_motorra_azeleratu(&kotxea);
				break;
			case 'd':
				// Eskubira
				kotxea_ezkerreko_motorra_azeleratu(&kotxea);
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

	Kotxea kotxea = {.potentzia_limitea = 35, .interbaloa = kotxea.potentzia_limitea - 1};

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

	kotxea_itzali();
	OHARRA("Helmugara iritsita.");

	return true;
}

bool kotxea_mapa(void)
{
	// Hemen dijsktra jun behar da
	Norabidea norab[] = {Ekialdea, Iparraldea, Ekialdea, Iparraldea}; // Hasierako puntura buelta
	int tamaina = sizeof(norab) / sizeof(Norabidea);

	Kotxea kotxea = {
		.potentzia_limitea = 100,
		.interbaloa = kotxea.potentzia_limitea,
		.aurrea = Iparraldea,
	};

	if (kotxea_init(&kotxea) == false)
	{
		ERROREA("kotxea_mapa(): Kotxea ezin izan da prestatu.");
		return false;
	}

	for (int i = 0; i < tamaina; i++)
	{
		// Marra zuzena, nodo bat aurkitu arte
		while (kotxea_nodo_aurkitu() == false)
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

		// Ikusi nora joan behar duen
		switch (norab[i])
		{
		case Iparraldea:
		{
			switch (kotxea.aurrea)
			{
			case Iparraldea:
				kotxea_giratu_aurrera(&kotxea);
				break;
			case Ekialdea:
				kotxea_giratu_ezkerrera(&kotxea);
				break;
			case Mendebaldea:
				kotxea_giratu_eskubira(&kotxea);
				break;
			default:
				ABISUA("ERROREA EZIN DA HONA JOAN");
				break;
			}
			break;
		}
		case Hegoaldea:
		{
			switch (kotxea.aurrea)
			{
			case Hegoaldea:
				kotxea_giratu_aurrera(&kotxea);
				break;
			case Mendebaldea:
				kotxea_giratu_ezkerrera(&kotxea);
				break;
			case Ekialdea:
				kotxea_giratu_eskubira(&kotxea);
				break;
			default:
				ABISUA("ERROREA EZIN DA HONA JOAN");
				break;
			}
			break;
		}
		case Ekialdea:
		{
			switch (kotxea.aurrea)
			{
			case Ekialdea:
				kotxea_giratu_aurrera(&kotxea);
				break;
			case Hegoaldea:
				kotxea_giratu_ezkerrera(&kotxea);
				break;
			case Iparraldea:
				kotxea_giratu_eskubira(&kotxea);
				break;
			default:
				ABISUA("ERROREA EZIN DA HONA JOAN");
				break;
			}
			break;
		}
		case Mendebaldea:
		{
			switch (kotxea.aurrea)
			{
			case Mendebaldea:
				kotxea_giratu_aurrera(&kotxea);
				break;
			case Iparraldea:
				kotxea_giratu_ezkerrera(&kotxea);
				break;
			case Hegoaldea:
				kotxea_giratu_eskubira(&kotxea);
				break;
			default:
				ABISUA("ERROREA EZIN DA HONA JOAN");
				break;
			}
			break;
		}
		default:
			break;
		}

		// Jarri kotxearen direkzio berria
		kotxea.aurrea = norab[i];
	}

	while (kotxea_nodo_aurkitu() == false)
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

	kotxea_eskubiko_motorra_frenatu(&kotxea);
	kotxea_ezkerreko_motorra_frenatu(&kotxea);

	hardware_ezkerreko_motorra_potentzia(0);
	hardware_eskubiko_motorra_potentzia(0);

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
	hardware_eskubiko_motorra_potentzia(kotxea->mot_eskubi.potentzia_balioa);
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

static void kotxea_giratu_eskubira(Kotxea *kotxea)
{
	// Frenatu
	kotxea_eskubiko_motorra_frenatu(kotxea);
	kotxea_ezkerreko_motorra_frenatu(kotxea);

	kotxea_ezkerreko_motorra_azeleratu(kotxea);
	kotxea_eskubiko_motorra_frenatu(kotxea);
	struct timespec denb = {.tv_sec = 0, .tv_nsec = 750000000};
	nanosleep(&denb, NULL);
}

static void kotxea_giratu_ezkerrera(Kotxea *kotxea)
{
	// Frenatu
	kotxea_eskubiko_motorra_frenatu(kotxea);
	kotxea_ezkerreko_motorra_frenatu(kotxea);

	kotxea_eskubiko_motorra_azeleratu(kotxea);
	kotxea_ezkerreko_motorra_frenatu(kotxea);
	struct timespec denb = {.tv_sec = 1, .tv_nsec = 000000000};
	nanosleep(&denb, NULL);
}

static void kotxea_giratu_aurrera(Kotxea *kotxea)
{
	// Zinta pasa
	while (kotxea_nodo_aurkitu() == true)
	{
		kotxea_eskubiko_motorra_azeleratu(kotxea);
		kotxea_ezkerreko_motorra_azeleratu(kotxea);
	}
}