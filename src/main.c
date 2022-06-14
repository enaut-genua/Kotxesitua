#include "includes.h"

#include "input.h"
#include "kotxea.h"
#include "hardware.h"

int main(void)
{
	// if (kotxea_urruneko_kontrola() == false)
	// {
	// 	ERROREA("Ezin izan da urruneko kontrola hasi.");
	// 	return EXIT_FAILURE;
	// }

	// if (kotxea_marra_jarraitu() == false)
	// {
	// 	ERROREA("Ezin izan da marra jarraitu.");
	// 	return EXIT_FAILURE;
	// }

	if (kotxea_mapa() == false)
	{
		ERROREA("Ezin izan da marra jarraitu.");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
