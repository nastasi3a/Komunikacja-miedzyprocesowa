#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc,char**argv){
	pid_t pid_potomka;
	char* kommunikat;
	int powtorzen;
	printf("Na razie działa jeden proces\n");
	pid_potomka=fork(); //tworzenie nowego procesu na zasadzie relacji rodzic - dziecko
	switch (pid_potomka){
		case-1: //utworzenie procesu potomnego się nie powiodło
			printf("rozwidlenie procesu nie powiodło się\n");
			exit(1); //powrót do jądra systemu, z kodem zakończenia 1
		case 0: //kod jest wykonywany w procesie potomnym
			kommunikat="Jestem potomkiem";
			powtorzen = 5;
			break;
		default:
			kommunikat="Jestem rodzicem";
			powtorzen = 5;
			break;
	}
	for(;powtorzen>0;powtorzen--){
	puts(kommunikat); //wyświetlenie wartości zmiennej kommunikat na standardowym wyjściu
	system("ps aux | grep zd2 | grep -v grep");
	sleep(1);
	}
}
