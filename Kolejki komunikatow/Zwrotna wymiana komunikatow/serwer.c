#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Wartosci okreslajace, co nalezy odczytac z kolejki komunikatow
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
	int sum = 0;

	key = ftok(".", 'A');  // Generowanie klucza IPC za pomocą ftok
	// Utworzenie lub pobranie identyfikatora kolejki komunikatów
	msgid = msgget(key, 0666 | IPC_CREAT);
	
	while (1) {
		// Oczekiwanie na wiadomość typu M_DATA
		msgrcv(msgid, &message, sizeof(message) - sizeof(long), M_DATA, 0);
		if (message.data == 0) {
			message.msg_type = M_RESULT;
			message.data = sum;
			// Wysłanie wiadomości M_RESULT z sumą do klienta
			msgsnd(msgid, &message, sizeof(message) - sizeof(long), 0);  
			break;  // Zakończenie pętli
		}
		sum += message.data;  // Dodawanie liczby do sumy
   	}
    return 0;

}
