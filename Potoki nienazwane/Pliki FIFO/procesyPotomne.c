#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUF_SIZE 2048
#define FIFO_FILE "myfifo"

int main(int argc, char** argv) {
    	char buffer[BUF_SIZE];
    	int fd;

    	// Create the FIFO file
    	mkfifo(FIFO_FILE, 0666);

    	pid_t pid = fork();

    	if (pid < 0) {
        	perror("fork");
        	return EXIT_FAILURE;
    	} else if (pid == 0) { // serwer code
        	// Child process (server) writes in FIFO
        	fd = open(FIFO_FILE, O_WRONLY);

        	int i;
        	for (i = 0; i < 10; ++i) {
            	snprintf(buffer, BUF_SIZE, "Serwer: wysyłam linie nr %d\n", i);
            	write(fd, buffer, BUF_SIZE);
        	}

		close(fd);
        	return EXIT_SUCCESS;
    } else {
        // Parent process (client)
        fd = open(FIFO_FILE, O_RDONLY);
        
        while (read(fd, buffer, BUF_SIZE) > 0) {
            printf("Serwer wysłał: %s", buffer);
        }
        
        close(fd);
        unlink(FIFO_FILE);
	return EXIT_SUCCESS;
    }
}
