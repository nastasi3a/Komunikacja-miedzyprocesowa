#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

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
            break;
        default:
            komunikat = "Jestem rodzicem";
            powtorzen = 10;
            while (waitpid(pid_potomka, NULL, WNOHANG) == 0) {
                printf("Oczekiwanie na zakończenie procesu potomnego...\n");
                sleep(1);
            }
            printf("Proces potomny o PID=%d zakończył działanie.\n", pid_potomka);
            break;
    }
    for (; powtorzen > 0; powtorzen--) {
        puts(komunikat);
        sleep(1);
    }
    return 0;
}
