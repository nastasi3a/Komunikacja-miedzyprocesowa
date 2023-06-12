#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define M_DATA 1
#define M_END 2
#define M_RESULT 3

struct msgbuf {
	long msg_type;
	int data;
} message;



int main() {
	key_t key;
	int msgid;
	struct msgbuf message;
	int number;
	int sum = 0;

	// Generowanie klucza IPC za pomocą ftok
	key = ftok(".", 'A');

	// Utworzenie lub pobranie identyfikatora kolejki komunikatów
	msgid = msgget(key, 0666 | IPC_CREAT);  

	while (1) {
		printf("Enter a number (or 0 to exit): ");
		scanf("%d", &number);
		message.msg_type = M_DATA;
		message.data = number;
		// Wysłanie liczby do serwera
		msgsnd(msgid, &message, sizeof(message) - sizeof(long), 0);
		if (number == 0) {
			message.msg_type = M_END;
			// Wysłanie wiadomości M_END do serwera
			msgsnd(msgid, &message, sizeof(message) - sizeof(long), 0);
			break;  // Zakończenie pętli
		}
	}

	// Oczekiwanie na wiadomość typu M_RESULT
	msgrcv(msgid, &message, sizeof(message) - sizeof(long), M_RESULT, 0);  

	sum = message.data;
	printf("Sum receieved from server: %d\n", sum);  // Wyświetlenie otrzymanej sumy

	return 0;

}
