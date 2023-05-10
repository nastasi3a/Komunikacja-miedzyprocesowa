#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char** argv){
	pid_t pid_potomka;
	char* komunikat;
	int powtorzen;
	printf("Na razie działa jeden proces\n");
	pid_potomka = fork();
	switch (pid_potomka) {
		case -1:
			printf("Rozwidlenie procesu nie powiodło się\n");
			exit(1);
		case 0:
			komunikat = "Jestem potomkiem";
			powtorzen = 5;
			srand(time(NULL) + getpid()); // ustawienie ziarna losowania
			int kod_zakonczenia = rand() % 256; // wylosowanie kodu zakończenia
			printf("Potomek kończy działanie z kodem %d\n", kod_zakonczenia);
			exit(kod_zakonczenia); // zakończenie procesu potomnego z wylosowanym kodem
		default:
			komunikat = "Jestem rodzicem";
			powtorzen = 5;
			waitpid(pid_potomka, NULL, 0); // czekanie na zakończenie procesu potomnego
			int kod_zakonczenia_potomka;
			if (WIFEXITED(kod_zakonczenia_potomka)) {
				kod_zakonczenia_potomka = WEXITSTATUS(kod_zakonczenia_potomka);
				printf("Proces potomny o PID=%d zakończył działanie z kodem %d.\n", pid_potomka, kod_zakonczenia_potomka);
			}
			break;
	}
	for (; powtorzen > 0; powtorzen--) {
	puts(komunikat);
	sleep(1);
}
return 0;
}






