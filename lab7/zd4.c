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
            sleep(1); // czekaj na proces potomny
            break;
    }
    
    for (int i = 0; i < powtorzen; i++) {
        printf("%s (PID=%d, PPID=%d)\n", komunikat, getpid(), getppid());
        sleep(2);
    }
    printf("Koniec działania procesu (PID=%d)\n", getpid());
    
    if (pid_potomka > 0) {
        int status;
        pid_t result = waitpid(pid_potomka, &status, WNOHANG);
        if (result == 0) {
            printf("Proces potomny (PID=%d) jest jeszcze uruchomiony.\n", pid_potomka);
            system("ps | grep zd4");
        } else {
            printf("Proces potomny (PID=%d) zakończył działanie z kodem %d.\n", pid_potomka, WEXITSTATUS(status));
 }
    } else {
        printf("Proces rodzica (PID=%d) zakończył działanie.\n", getppid());
        int ppid = getppid();
        char command[100]; //napis do przechowywania polecenia powłoki
        sprintf(command, "ps | grep %d", ppid); //zapisanie napisu w podanej jako argument tablice znaków w postaci "ps | grep {ppid}"
        system(command); //wykonanie polecenia
        printf("Proces %d: zostalem osierocony przez rodzica %d.\n", getpid(), ppid);
    }
    
    return 0;
}
