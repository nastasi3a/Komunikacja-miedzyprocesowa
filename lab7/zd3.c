#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc,char**argv){
	pid_t pid_potomka;
	char* kommunikat;
	int powtorzen;
	printf("Na razie działa jeden proces (PID=%d)\n", getpid());
	pid_potomka=fork();
	switch (pid_potomka){
		case -1:
			printf("rozwidlenie procesu nie powiodło się\n");
			exit(1);
		case 0:
			kommunikat="Jestem potomkiem";
			powtorzen = 5;
			printf("%s (PID=%d) rodzic (PID=%d)\n", kommunikat, getpid(), getppid());
			break;
		default:
			kommunikat="Jestem rodzicem";
			powtorzen = 5;
			printf("%s (PID=%d) potomek (PID=%d)\n", kommunikat, getpid(), pid_potomka);
			break;
	}
}
