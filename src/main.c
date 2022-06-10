#include "includes.h"

#include "input.h"
#include "kotxea.h"
#include "hardware.h"

int main(void)
{
	hardware_init();
	
	// while (true)
	// {
	// 	hardware_eskubiko_motorra_piztu();
	// 	hardware_ezkerreko_motorra_piztu();
	// }
	
	
	// kotxea_urruneko_kontrola();

	kotxea_marra_jarraitu();

	return EXIT_SUCCESS;
}
