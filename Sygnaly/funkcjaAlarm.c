#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

//podstawowa wersja programu wyświetla cykliczne 3 napisy po naciśnięciu CTRL+C
//zakończenie programu CTRL+\ (SIGQUIT)

char napisy[3][80]={"Ha! Ha! Ha! To tylko sygnał powierzchowny!\n", "Tylko proces %d śmieje się sygnałowi %d prosto w twarz!\n", "Auć - to bolało!\n"};
int nr_napisu=0;

void obsluga_sig_int(int sig) {
	printf(napisy[nr_napisu],getpid(),sig);
	nr_napisu=((nr_napisu + 1) % 3);
}

void restore_sig_int(int sig) {
	signal(SIGINT, SIG_DFL); 
}

void obsluga_sig_quit(int sig) {
	signal(SIGINT,restore_sig_int);
}

void obsluga_sig_alarm(int sig) {
	printf("Ding! Ding! Ding! - Przywracam domyślną obsługę CTRL+C.\n");
	signal(SIGINT,restore_sig_int);
}

int main(int argc, char** argv) {
	signal(SIGINT,obsluga_sig_int);
	signal(SIGALRM, obsluga_sig_alarm);
	alarm(15);
	while (true) {
		printf("Cześć tu proces: %d\n",getpid());
		sleep(1);
	}
	return 0;
}
