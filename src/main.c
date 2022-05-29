#include "includes.h"

#include "input.h"
#include "kotxea.h"

int main(void)
{
	input_init();
	int c = 0;

#ifdef RASPBERRY
	printf("Raspberry Pi!");
	wiringPiSetup();
#endif

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

	input_destroy();

	return EXIT_SUCCESS;
}
