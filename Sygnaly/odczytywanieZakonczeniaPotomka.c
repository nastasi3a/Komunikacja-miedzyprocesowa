#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <signal.h>

int k=0;

void catcher()
{
	pid_t child = wait(NULL);
	if (child!=-1) {
	printf("Proces potomny miał ID: %d\n", child);
	k=1;}
}

int main(int argc, char** argv) {
    struct sigaction sact;
	
    sact.sa_flags = 0;
    sact.sa_handler = catcher;
    sigaction( SIGCHLD, &sact, NULL );
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
            break;
        default:
            komunikat = "Jestem rodzicem";
            powtorzen = 5;
            while (k==0) {
		printf("Oczekiwanie na zakończenie procesu potomnego...\n");
		//system("ps aux | grep zd16 | grep -v grep");
                sleep(1);
            }
	}
   for (; powtorzen > 0; powtorzen--) {
        puts(komunikat);
	system("ps aux | grep zd16 | grep -v grep");
        sleep(1);
    }
    printf("Koniec procesu %d\n", getpid());
    return 0;
}
