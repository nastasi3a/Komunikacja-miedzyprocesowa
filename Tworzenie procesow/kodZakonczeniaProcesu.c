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
	pid_t child_pid;
	printf("Na razie działa jeden proces\n");
	pid_potomka = fork();
	int status;
	switch (pid_potomka) {
		case -1:
			printf("Rozwidlenie procesu nie powiodło się\n");
			exit(1);
		case 0:
			komunikat = "Jestem potomkiem";
			powtorzen = 5;
			child_pid = getpid();
			break;
		default:
			komunikat = "Jestem rodzicem";
			powtorzen = 5;
			printf("Czekam na zakończenie procesu potomnego...\n");
			wait(&status);
			if (WIFEXITED(status)) {
                              int kod_potomka = WEXITSTATUS(status);
                              printf("Proces potomny o PID=%d zakończył działanie z kodem %d.\n", pid_potomka, kod_potomka);
			}
			break;
	}
	for (; powtorzen > 0; powtorzen--) {
	puts(komunikat);
	//system("ps aux | grep zd8 | grep -v grep");
	if (getpid()==child_pid && powtorzen == 1) {
	srand(time(NULL) + getpid()); // ustawienie ziarna losowania
        int kod_zakonczenia = rand() % 256; // wylosowanie kodu zakończenia
        printf("Potomek kończy działanie z kodem %d\n", kod_zakonczenia);
        exit(kod_zakonczenia); // zakończenie procesu potomnego z wylosowanym kodem
        }
	sleep(1);
}
return 0;
}






