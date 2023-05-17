#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
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
            printf("Czekam na zakończenie procesu potomnego...\n");
            while (waitpid(pid_potomka, NULL, WNOHANG) == 0) {
                printf("Oczekiwanie na zakończenie procesu potomnego...\n");
                sleep(1);
            }
            printf("Proces potomny zakończył działanie\n");
            break;
    }
    for (; powtorzen > 0; powtorzen--) {
        puts(komunikat);
	system("ps aux | grep zd7_1 | grep -v grep");
        sleep(1);
    }
    printf("Koniec procesu %d\n", getpid());
    return 0;
}
