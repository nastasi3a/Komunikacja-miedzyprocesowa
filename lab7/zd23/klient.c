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

    int fd = open(FIFO_FILE, O_RDONLY | O_NONBLOCK);

    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    sleep(2);  // 2 s opóźnienia odczytu

    while (read(fd, buffer, BUF_SIZE) > 0) {
        printf("Serwer wysłał: %s", buffer);
    }

    close(fd);

    return EXIT_SUCCESS;
}
