#ifndef HARDWARE_H
#define HARDWARE_H

#include "includes.h"

void hardware_init(void);

void hardware_eskubiko_motorra_piztu(void);
void hardware_eskubiko_motorra_itzali(void);
void hardware_ezkerreko_motorra_piztu(void);
void hardware_ezkerreko_motorra_itzali(void);

PinEgoera hardware_eskubiko_ldr_irakurri(void);
PinEgoera hardware_ezkerreko_ldr_irakurri(void);

#endif