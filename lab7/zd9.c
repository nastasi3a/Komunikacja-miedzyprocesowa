#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {

    printf("Wykonuję polecenie za pomocą funkcji system()\n");
    system("echo Pośpię sobie chwileczkę");
    system("sleep 10");
    printf("Polecenie wywołane za pomocą system() zakończyło się\n");

    printf("Wykonuję polecenie za pomocą funkcji execlp()\n");
    execlp("sh", "sh", "-c", "echo Pośpię sobie chwileczkę ; sleep 10 ; echo \"Polecenie wywołane za pomocą execlp() zakończyło się\"", NULL);
    return 0;

}
