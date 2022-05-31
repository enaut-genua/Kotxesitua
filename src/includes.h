#ifndef INCLUDES_H
#define INCLUDES_H

/* C STD */
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* POSIX */
#include <poll.h>
#include <termios.h>
#include <unistd.h>

/* Wiring Pi */
#ifdef RASPBERRY
#include <wiringPi.h>
#endif

/* LAGUNTZAK */
#define BUF_SZ 128
#define BALIOA_ERABILI_GABE(x) (void)(x)
#define OHARRA(x) (fprintf(stdout, "Oharra: %s\n", x))
#define ABISUA(x) (fprintf(stderr, "Abisua: %s\n", x))
#define ERROREA(x) (fprintf(stderr, "Errorea: %s\n", x))

/* DATU MOTAK */
typedef enum pin_egoera_t
{
	Ezgaitu,
	Gaitu,
} PinEgoera;

#endif