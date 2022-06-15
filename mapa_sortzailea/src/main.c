#include "menu.h"

int main() {
	int aukera = menua();
	while (aukera != 0)
	{
		aukera_exekutatu(aukera);
		aukera = menua();
	}
	return 0;
}
