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
            powtorzen = 10;
            break;
        default:
            komunikat = "Jestem rodzicem";
            powtorzen = 5;
            break;
    }
    
    for (int i = 0; i < powtorzen; i++) {
        puts(komunikat);
        system("ps aux | grep zd4 | grep -v grep");
	sleep(1);
    }    
    return 0;
}
