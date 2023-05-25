#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define BUF_SIZE 2048
#define FIFO_FILE "myfifo"

int main(int argc, char** argv) {
    char buffer[BUF_SIZE];
    //create FIFO proces if it does not exist yet
    if (mkfifo(FIFO_FILE, 0666) == -1) {
        perror("mkfifo");
        return EXIT_FAILURE;
    }
    //FIFO O_RDONLY opening
    int fd = open(FIFO_FILE, O_WRONLY | O_NONBLOCK);

    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    int i;
    for (i = 0; i < 10; ++i) {
        snprintf(buffer, BUF_SIZE, "Serwer: wysyłam linie nr %d\n", i);
        write(fd, buffer, BUF_SIZE);
        sleep(1);  // 1 s opóźnienia zapisu
    }

    close(fd);

    return EXIT_SUCCESS;
}
