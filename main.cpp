//Radomir Fugiel
//Project01

#include "main.h"

settings Settings;

void sig_handler(int signo) {
  	if (signo == SIGINT) {
   		printf("\nCleaning Up...\n");
		exit(0);
	}
}


int main(int argc, char* argv[]) {
	if (signal(SIGINT, sig_handler) == SIG_ERR)
  		printf("\ncan't catch SIGINT\n");

	parse(argc, argv, Settings);
	watch(Settings);

	return 0;
}
