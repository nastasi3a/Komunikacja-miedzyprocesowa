#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    pid_t pid_potomka;
    char* komunikat;
    int powtorzen;
    printf("Na razie działa jeden proces (PID=%d)\n", getpid());
    pid_potomka = fork();
    switch (pid_potomka) {
        case -1:
            printf("Rozwidlenie procesu nie powiodło się\n");
            exit(1);
        case 0:
            komunikat = "Jestem potomkiem";
            powtorzen = 5;
            printf("%s (PID=%d) rodzic (PID=%d) potomek (PID=%d)\n", komunikat, getpid(), getppid(), pid_potomka);
            break;
        default:
            komunikat = "Jestem rodzicem";
            powtorzen = 5;
            printf("%s (PID=%d) potomek (PID=%d) rodzic (PID=%d)\n", komunikat, getpid(), pid_potomka, getppid());
            break;
    }
}
