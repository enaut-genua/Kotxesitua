#include "hardware.h"

/* Pinak definitu */
typedef enum pin_enum
{
	MotorraEskubi,
	MotorraEzkerra,
	LDREskubi,
	LDREzkerra
} Pin;

/* Funtzio Publikoak */

bool hardware_init(const int potentzia_limitea)
{
	OHARRA("Hardwarea konfiguratzen...");

	if (wiringPiSetup() != 0)
	{
		ERROREA("hardware_init() -> wiringPiSetup(): Errorea wiringPi konfiguratzean.");
		return false;
	}

	pinMode(MotorraEskubi, OUTPUT);
	pinMode(MotorraEzkerra, OUTPUT);
	pinMode(LDREskubi, INPUT);
	pinMode(LDREzkerra, INPUT);

	pullUpDnControl(LDREskubi, PUD_UP);
	pullUpDnControl(LDREzkerra, PUD_UP);

	if (softPwmCreate(MotorraEskubi, potentzia_limitea, 100) != 0)
	{
		char errore_mezua[BUF_SZ] = {'\0'};
		snprintf(errore_mezua, BUF_SZ, "hardware_init() -> softPwmCreate(): %s", strerror(errno));
		ERROREA(errore_mezua);
		return false;
	}

	if (softPwmCreate(MotorraEzkerra, potentzia_limitea, 100) != 0)
	{
		char errore_mezua[BUF_SZ] = {'\0'};
		snprintf(errore_mezua, BUF_SZ, "hardware_init() -> softPwmCreate(): %s", strerror(errno));
		ERROREA(errore_mezua);
		return false;
	}

	OHARRA("Hardwarea konfiguratuta.");

	return true;
}

void hardware_eskubiko_motorra_potentzia(const int balioa)
{
	OHARRA("Eskubiko pinaren potentzia aldatu.");
	softPwmWrite(MotorraEskubi, balioa);
}

void hardware_ezkerreko_motorra_potentzia(const int balioa)
{
	OHARRA("Ezkerreko pinaren potentzia aldatu.");
	softPwmWrite(MotorraEzkerra, balioa);
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