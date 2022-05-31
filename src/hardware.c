#include "hardware.h"

/* Pinak definitu */
typedef enum pin_enum
{
	MotorraEskubi,
	MotorraEzkerra,
	LDREskubi,
	LDREzkerra
} Pin;

void hardware_init()
{
	OHARRA("Hardwarea konfiguratzen...");
	wiringPiSetup();

	pinMode(MotorraEskubi, OUTPUT);
	pinMode(MotorraEzkerra, OUTPUT);
	pinMode(LDREskubi, INPUT);
	pinMode(LDREzkerra, INPUT);

	pullUpDnControl(LDREskubi, PUD_UP);
	pullUpDnControl(LDREzkerra, PUD_UP);

	OHARRA("Hardwarea konfiguratuta.");
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