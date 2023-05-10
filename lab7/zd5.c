#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char** argv) {
    pid_t pid_potomka;
    char* kommunikat;
    int powtorzen;
    printf("Na razie działa jeden proces\n");
    pid_potomka = fork();
    switch (pid_potomka) {
        case -1:
            printf("rozwidlenie procesu nie powiodło się\n");
            exit(1);
        case 0:
            kommunikat = "Jestem potomkiem";
            powtorzen = 5;
            sleep(10); // dodanie funkcji sleep()
            printf("Proces potomny: %d zakończył działanie\n", getpid());
            break;
        default:
            kommunikat = "Jestem rodzicem";
            powtorzen = 5;
            sleep(1);
            printf("Proces rodzica: %d utworzył proces potomny o PID: %d\n", getpid(), pid_potomka);
            printf("Wysyłam sygnał SIGKILL do procesu potomnego: %d\n", pid_potomka);
            char command[50];
            sprintf(command, "kill -9 %d", pid_potomka); // wysyłanie sygnału SIGKILL do procesu potomnego
            system(command);
            sleep(5); // oczekiwanie na stworzenie procesu zombie
            printf("Proces rodzica: %d zakończył działanie\n", getpid());
            break;
    }
    for (; powtorzen > 0; powtorzen--) {
        puts(kommunikat);
        sleep(1);
    }
    return 0;
}
