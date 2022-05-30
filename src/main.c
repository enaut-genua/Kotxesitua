#include "includes.h"

#include "input.h"
#include "kotxea.h"
#include "hardware.h"

int main(void)
{
	while (input_init() == false)
	{
		ABISUA("Inputa ez da ondo konfiguratu, berriro saiatzen...");		
	}

	int c = 0;

	while ((c = getchar()) != 'e')
	{
		switch (c)
		{
		case 'w':
			// Aurrera
			printf("Aurrera!\n");
			// Bi motoreak batera piztu.
			break;
		case 'a':
			// Ezkerrera
			kotxea_ezkerreko_motorra_mugitu();
			break;
		case 'd':
			// Eskubi
			kotxea_eskubiko_motorra_mugitu();
			break;
		}
	}


	while (input_destroy() == false)
	{
		ABISUA("Inputa ez da ondo borratu, berriro saiatzen...");	
	}
	
	return EXIT_SUCCESS;
}
