#ifndef INCLUDES_H
#define INCLUDES_H

/* LAGUNTZAK */
#define BUF_SZ 128
#define ERABILI_GABE(x) (void)(x);

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

#endif