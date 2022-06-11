#ifndef HARDWARE_H
#define HARDWARE_H

#include "includes.h"
#include "kotxea.h"

/* Pinak konfiguratu */
bool hardware_init(const int potentzia_limitea);

/* Motorren potentzia erregulatu */
void hardware_eskubiko_motorra_potentzia(const int balioa);
void hardware_ezkerreko_motorra_potentzia(const int balioa);

/* LDR-en balioak irakurri */
PinEgoera hardware_eskubiko_ldr_irakurri(void);
PinEgoera hardware_ezkerreko_ldr_irakurri(void);

#endif