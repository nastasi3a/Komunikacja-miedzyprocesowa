#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

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
            powtorzen = 10;
            break;
    }

    for (int i = 0; i < powtorzen; i++) {
        printf("%s (PID=%d, PPID=%d)\n", komunikat, getpid(), getppid());
	system("ps aux | grep zd5 | grep -v grep");
        sleep(1);
    }
    printf("Koniec działania procesu (PID=%d)\n", getpid());

    if (pid_potomka > 0) {
        printf("Proces rodzica (PID=%d) zakończył działanie.\n", getpid());
    } else {
        printf("Proces potomny (PID=%d) zakończył działanie z kodem 0.\n", getpid());
    }

    return 0;
}
