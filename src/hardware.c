#include "hardware.h"

static const int POTENTZIA_LIMITEA = 30;
static const int INTERBALOA = POTENTZIA_LIMITEA - 1;

/* Pinak definitu */
typedef enum pin_enum
{
	MotorraEskubi,
	MotorraEzkerra,
	LDREskubi,
	LDREzkerra
} Pin;

/* Funtzio Publikoak */

bool hardware_init()
{
	OHARRA("Hardwarea konfiguratzen...");
	wiringPiSetup();

	pinMode(MotorraEskubi, OUTPUT);
	pinMode(MotorraEzkerra, OUTPUT);
	pinMode(LDREskubi, INPUT);
	pinMode(LDREzkerra, INPUT);

	pullUpDnControl(LDREskubi, PUD_UP);
	pullUpDnControl(LDREzkerra, PUD_UP);

	if (softPwmCreate(MotorraEskubi, POTENTZIA_LIMITEA, 100) != 0)
	{
		char errore_mezua[BUF_SZ] = {'\0'};
		snprintf(errore_mezua, BUF_SZ, "hardware_init() -> softPwmCreate(): %s", strerror(errno));
		ERROREA(errore_mezua);
		return false;
	}

	if (softPwmCreate(MotorraEzkerra, 20, 100) != 0)
	{
		char errore_mezua[BUF_SZ] = {'\0'};
		snprintf(errore_mezua, BUF_SZ, "hardware_init() -> softPwmCreate(): %s", strerror(errno));
		ERROREA(errore_mezua);
		return false;
	}

	OHARRA("Hardwarea konfiguratuta.");

	return true;
}

void hardware_eskubiko_motorra_piztu(void)
{
	OHARRA("Eskubiko motorraren pina piztu.");
	digitalWrite(MotorraEskubi, HIGH);
}

void hardware_eskubiko_motorra_itzali(void)
{
	OHARRA("Eskubiko motorraren pina itzali.");
	digitalWrite(MotorraEskubi, LOW);
}

void hardware_ezkerreko_motorra_piztu(void)
{
	OHARRA("Ezkerreko motorraren pina piztu.");
	digitalWrite(MotorraEzkerra, HIGH);
}

void hardware_ezkerreko_motorra_itzali(void)
{
	OHARRA("Ezkerreko motorraren pina itzali.");
	digitalWrite(MotorraEzkerra, LOW);
}

void hardware_eskubiko_motorra_azeleratu(int *balioa)
{
	OHARRA("Eskubiko motorraren pina frekuentzia handitu.");
	*balioa += *balioa < POTENTZIA_LIMITEA ? INTERBALOA : 0;
	softPwmWrite(MotorraEskubi, *balioa);
}

void hardware_eskubiko_motorra_frenatu(int *balioa)
{
	OHARRA("Eskubiko motorraren pina frekuentzia txikitu.");
	*balioa -= *balioa > 0 ? INTERBALOA : 0;
	softPwmWrite(MotorraEskubi, *balioa);
}

void hardware_ezkerreko_motorra_azeleratu(int *balioa)
{
	OHARRA("Ezkerreko motorraren pina frekuentzia handitu.");
	*balioa += *balioa < POTENTZIA_LIMITEA ? INTERBALOA : 0;
	softPwmWrite(MotorraEzkerra, *balioa);
}

void hardware_ezkerreko_motorra_frenatu(int *balioa)
{
	OHARRA("Ezkerreko motorraren pina frekuentzia txikitu.");
	*balioa -= *balioa > 0 ? INTERBALOA : 0;
	softPwmWrite(MotorraEzkerra, *balioa);
}

PinEgoera hardware_eskubiko_ldr_irakurri(void)
{
	OHARRA("Eskubiko LDR-aren pina irakurri.");
	return digitalRead(LDREskubi);
}

PinEgoera hardware_ezkerreko_ldr_irakurri(void)
{
	OHARRA("Ezkerreko LDR-aren pina irakurri.");
	return digitalRead(LDREzkerra);
}