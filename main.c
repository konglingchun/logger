#include "loger.h"

int main(int argc, char *argv[])
{
	printd(DEBUG, "DEBUG\n");
	printd(INFO, "INFO\n");
	printd(WARN, "WARN\n");
	printd(ERROR, "ERROR\n");
	printd(FATAL, "FATAL\n");
	return 0;
}
