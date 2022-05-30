#include "hardware.h"

/* Pinak definitu */
typedef enum pin_enum
{
	MotorraEskubi = 0,
	MotorraEzkerra,
	LDREskubi,
	LDREzkerra
} Pin;

void hardware_init()
{
	INFO("Hardwarea konfiguratzen...");
	wiringPiSetup();

	pinMode(MotorraEskubi, OUTPUT);
	pinMode(MotorraEzkerra, OUTPUT);
	pinMode(LDREskubi, INPUT);
	pinMode(LDREzkerra, INPUT);

	pullUpDnControl(LDREskubi, PUD_UP);
	pullUpDnControl(LDREzkerra, PUD_UP);

	INFO("Hardwarea konfiguratuta.");
}

void hardware_eskubiko_motorra_piztu(void)
{
	INFO("Eskubiko motorra piztu.");
	digitalWrite(MotorraEskubi, HIGH);
}

void hardware_eskubiko_motorra_itzali(void)
{
	INFO("Eskubiko motorra itzali.");
	digitalWrite(MotorraEskubi, LOW);
}

void hardware_ezkerreko_motorra_piztu(void)
{
	INFO("Ezkerreko motorra piztu.");
	digitalWrite(MotorraEzkerra, HIGH);
}

void hardware_ezkerreko_motorra_itzali(void)
{
	INFO("Ezkerreko motorra itzali");
	digitalWrite(MotorraEzkerra, LOW);
}
