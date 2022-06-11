#ifndef INPUT_H
#define INPUT_H

#include "includes.h"

/* Inputa martxan jarri. Errorea badago 'false' bueltatu, bestela 'true'. */
bool input_init(void);

/* Teklaren bat sakatu den ikusi. Sakatu bada 'true' bestela 'false'. */
bool input_tekla_sakatu_da(void);

/* Inputa berriro normal jarri. Errorea badago 'false' bestela 'true'. */
bool input_destroy(void);


#endif