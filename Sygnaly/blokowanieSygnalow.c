#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

//podstawowa wersja programu wyświetla cykliczne 3 napisy po naciśnięciu CTRL+C
//zakończenie programu CTRL+\ (SIGQUIT)

char napisy[4][80]={"Ha! Ha! Ha! To tylko sygnał powierzchowny!\n", "Tylko proces %d śmieje się sygnałowi %d prosto w twarz!\n", "Auć - to bolało!\n", "Dobrze! Dobrze! Już kończę.\n"};
int nr_napisu=0, k=0;
sigset_t new_set, old_set, waiting_set;

void obsluga_sig_int(int sig) {
	printf(napisy[nr_napisu],getpid(),sig);
	nr_napisu=((nr_napisu + 1) % 4);
	if (nr_napisu == 0) exit(0);
}

void obsluga_sig_alarm(int sig) {
printf("Sygnały wystąpiłe w ciągu pierwszych 15 sekund:\n");
	sigpending(&waiting_set);
	if (sigismember(&waiting_set, SIGINT)) printf("SIGINT\n");
	if (sigismember(&waiting_set, SIGQUIT)) printf("SIGQUIT\n");
	k=1;
}

void unblock() {
	sigprocmask(SIG_UNBLOCK, &new_set, NULL); 
	k=0;
}

int main(int argc, char** argv) {
	sigemptyset(&new_set);
	sigemptyset(&old_set);
	sigaddset(&new_set, SIGINT);
	sigaddset(&new_set, SIGQUIT);
	sigprocmask(SIG_BLOCK, &new_set, &old_set);
	signal(SIGINT,obsluga_sig_int);
	signal(SIGALRM,obsluga_sig_alarm);
	alarm(15);
	while (true) {
		if (k) unblock();
		printf("Cześć tu proces: %d\n",getpid());
		sleep(1);
	}
	return 0;
}
