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

	/* wiringPi liburutegia martxan jarri */
	if (wiringPiSetup() != 0)
	{
		ERROREA("hardware_init() -> wiringPiSetup(): Errorea wiringPi konfiguratzean.");
		return false;
	}

	/* Motorren pinak seinalea emateko jarri */
	pinMode(MotorraEskubi, OUTPUT);
	pinMode(MotorraEzkerra, OUTPUT);

	/* LDR pinak seinalea irakurtzeko jarri */
	pinMode(LDREskubi, INPUT);
	pinMode(LDREzkerra, INPUT);

	/* LDR pinetan dauden erresistentziak konfiguratu */
	pullUpDnControl(LDREskubi, PUD_UP);
	pullUpDnControl(LDREzkerra, PUD_UP);

	/* Software bidezko modulazioa aktibatu motorren pinetan */
	if (softPwmCreate(MotorraEskubi, potentzia_limitea, POTENTZIA_MAX) != 0)
	{
		char errore_mezua[BUF_SZ] = {'\0'};
		snprintf(errore_mezua, BUF_SZ, "hardware_init() -> softPwmCreate(): %s", strerror(errno));
		ERROREA(errore_mezua);
		return false;
	}
	if (softPwmCreate(MotorraEzkerra, potentzia_limitea, POTENTZIA_MAX) != 0)
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

	/* Potentzia ehunekoa jarri */
	softPwmWrite(MotorraEskubi, balioa);
}

void hardware_ezkerreko_motorra_potentzia(const int balioa)
{
	OHARRA("Ezkerreko pinaren potentzia aldatu.");
	
	/* Potentzia ehunekoa jarri */
	softPwmWrite(MotorraEzkerra, balioa);
}

PinEgoera hardware_eskubiko_ldr_irakurri(void)
{
	OHARRA("Eskubiko LDR-aren pina irakurri.");

	/* Pinetik irakurri */
	return digitalRead(LDREskubi);
}

PinEgoera hardware_ezkerreko_ldr_irakurri(void)
{
	OHARRA("Ezkerreko LDR-aren pina irakurri.");

	/* Pinetik irakurri */
	return digitalRead(LDREzkerra);
}