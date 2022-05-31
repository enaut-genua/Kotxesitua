#include "input.h"

static struct termios TERM_ZAHARRA = {0};

bool input_init(void)
{
	/* Lortu oraingo terminalaren konfigurazioa eta gorde. */
	if (tcgetattr(STDIN_FILENO, &TERM_ZAHARRA) < 0)
	{
		char errore_mezua[BUF_SZ] = {'\0'};
		snprintf(errore_mezua, BUF_SZ, "input_init() -> tcgetattr(): %s", strerror(errno));
		ERROREA(errore_mezua);
		return false;
	}

	/* Sortu aldagai auxiliar bat oraingo konfigurazioa aldatzeko. */
	struct termios aux_term = TERM_ZAHARRA;

	/* Atera modu kanonikotik eta sartzen den karakterea ezkutatu. */
	aux_term.c_lflag &= ~(ICANON | ECHO);

	/* Jarri hartzen den byte kopurua 1, karaktere bat bakarrik hartzeko -> sizeof(char) == 1 */
	aux_term.c_cc[VMIN] = 1;

	/* Konfigurazioa ezarri orain */
	if (tcsetattr(STDIN_FILENO, TCSANOW, &aux_term) < 0)
	{
		char errore_mezua[BUF_SZ] = {'\0'};
		snprintf(errore_mezua, BUF_SZ, "input_init() -> tcsetattr(): %s", strerror(errno));
		ERROREA(errore_mezua);
		return false;
	}

	return true;
}

bool input_tekla_sakatu_da(void)
{
	struct pollfd stdin_fd = {.fd = STDIN_FILENO, .events = POLLIN};
	return poll(&stdin_fd, 1, 50) > 0 ? true : false;
}

bool input_destroy(void)
{
	/* Aurreko konfigurazioa ezarri dena idatzi eta gero */
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &TERM_ZAHARRA) < 0)
	{
		char errore_mezua[BUF_SZ] = {'\0'};
		snprintf(errore_mezua, BUF_SZ, "input_init() -> tcgetattr(): %s", strerror(errno));
		ERROREA(errore_mezua);
		return false;
	}

	return true;
}