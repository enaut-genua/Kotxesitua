#ifndef INCLUDES_H
#define INCLUDES_H

/* C STD */
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* POSIX */
#include <unistd.h>
#include <termios.h>

/* Wiring Pi */
#ifdef RASPBERRY
#include <wiringPi.h>
#endif

/* LAGUNTZAK */
#define BUF_SZ 128
#define BALIOA_ERABILI_GABE(x) (void)(x)
#define INFO(x) (fprintf(stdout, "Info: " x "\n"))
#define ABISUA(x) (fprintf(stderr, "Abisua: " x "\n"))
#define ERROREA(x) (fprintf(stderr, "Errorea: " x "\n"))


#endif