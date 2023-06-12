#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUF_SIZE 2048
#define FIFO_FILE "myfifo"

int main(int argc, char** argv) {
    char buffer[BUF_SIZE];
	// create FIFO file
    if (mkfifo(FIFO_FILE, 0666) == -1) {
        perror("mkfifo");
        return EXIT_FAILURE;
    }
	//serwer proces writes into FIFO
    int fd = open(FIFO_FILE, O_WRONLY);

    int i;
    for (i = 0; i < 10; ++i) {
        snprintf(buffer, BUF_SIZE, "Serwer: wysyłam linie nr %d\n", i);
        write(fd, buffer, BUF_SIZE);
    }
    unlink(FIFO_FILE);
    close(fd);
    return EXIT_SUCCESS;
}
