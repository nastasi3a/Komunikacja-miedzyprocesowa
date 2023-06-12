#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUF_SIZE 2048

int main(int argc, char** argv) {
    int fd[2]; // File descriptors for the pipe
    char buffer[BUF_SIZE];

    if (pipe(fd) == -1) {
        perror("pipe");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    } else if (pid == 0) { // Child process (server) code
        close(fd[0]); // Close the read end of the pipe

        int i;
        for (i = 0; i < 10; ++i) {
            snprintf(buffer, BUF_SIZE, "Serwer: wysyłam linie nr %d\n", i);
            write(fd[1], buffer, BUF_SIZE);
        }

        close(fd[1]); // Close the write end of the pipe
        return EXIT_SUCCESS;
    } else {
        // Parent process (client)
        close(fd[1]); // Close the write end of the pipe

        while (read(fd[0], buffer, BUF_SIZE) > 0) {
            printf("Serwer wysłał: %s", buffer);
        }

        close(fd[0]); // Close the read end of the pipe
        return EXIT_SUCCESS;
    }
}
