#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 2048

int main(int argc, char** argv) {
    /* Próba uruchomienia komendy */
    FILE* command_result = popen("./serwer", "r");
    if (command_result) {
        char buffer[BUF_SIZE];
        
        /* Oczekiwanie na wynik przez 2 sekundy */
        sleep(2);

        /* Odczyt linii wynikowych */
        while (fgets(buffer, BUF_SIZE, command_result) != NULL) {
            printf("Serwer wysłał: %s", buffer);
        }

        /* Zakończenie odczytu wyników */
        pclose(command_result);
        fflush(stdout);

        return EXIT_SUCCESS;
    } else {
        printf("Niepowodzenie funkcji popen\n");
        fflush(stdout);
        return EXIT_FAILURE;
    }
}
