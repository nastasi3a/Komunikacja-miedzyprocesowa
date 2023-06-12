#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

//podstawowa wersja programu wyświetla cykliczne 3 napisy po naciśnięciu CTRL+C
//zakończenie programu CTRL+\ (SIGQUIT)

char napisy[4][80]={"Ha! Ha! Ha! To tylko sygnał powierzchowny!\n", "Tylko proces %d śmieje się sygnałowi %d prosto w twarz!\n", "Auć - to bolało!\n", "Dobrze! Dobrze! Już kończę"};
int nr_napisu=0;
sigset_t new_set;

void obsluga_sig_int(int sig) {
	sleep(2);
	printf(napisy[nr_napisu],getpid(),sig);
	nr_napisu=((nr_napisu + 1) % 4);
	if (nr_napisu == 0) exit(0);
}

int main(int argc, char** argv) {
	struct sigaction sact;
	sigemptyset(&sact.sa_mask);
        sigaddset(&sact.sa_mask, SIGINT);
        sigaddset(&sact.sa_mask, SIGQUIT);
	sact.sa_handler = obsluga_sig_int;
	sigaction( SIGINT, &sact, NULL );
	while (true) {
		printf("Cześć tu proces: %d\n",getpid());
		sleep(1);
	}
	return 0;
}
