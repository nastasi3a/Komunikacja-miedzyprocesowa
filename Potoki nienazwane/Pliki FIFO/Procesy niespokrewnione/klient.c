#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUF_SIZE 2048
#define FIFO_FILE "myfifo"

int main(int argc, char** argv) {
    char buffer[BUF_SIZE];
    
    int fd = open(FIFO_FILE, O_RDONLY);
    
    while (read(fd, buffer, BUF_SIZE) > 0) {
        printf("Serwer wysłał: %s", buffer);
    }
    
    close(fd);
    return EXIT_SUCCESS;
}

