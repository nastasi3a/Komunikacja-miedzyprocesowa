#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define M_TYPE 1
#define MAX_MSG_SIZE 100

struct msg_buffer {
    long msg_type;
    char msg_text[MAX_MSG_SIZE];
};


int msgid1, msgid2; // Identyfikator kolejki

struct msg_buffer message;

// Funkcja wątku odbiorcy
void *receiver(void *arg) {
    while(1) {
        if(msgrcv(msgid1, &message, sizeof(message), M_TYPE, 0) == -1) { //msgid1
            perror("msgrcv");
            exit(1);
        }
        printf("Received: %s\n", message.msg_text);
        if(strcmp(message.msg_text, "exit\n") == 0) exit(0);
    }
}

// Funkcja wątku nadawcy
void *sender(void *arg) {
    message.msg_type = M_TYPE;
    while(1) {
        fgets(message.msg_text, MAX_MSG_SIZE, stdin);
        if(msgsnd(msgid2, &message, sizeof(message), 0) == -1) { //msgid2
            perror("msgsnd");
            exit(1);
        } if (strcmp(message.msg_text, "exit\n") == 0) exit(0);
    }
}

int main() {
    key_t key1, key2;
    pthread_t thread1, thread2;

    key1 = 1234;
    key2 = 1235;
    msgid1 = msgget(key1, 0666 | IPC_CREAT);
    msgid2 = msgget(key2, 0666 | IPC_CREAT);

    // Tworzenie wątków nadawcy i odbiorcy
    pthread_create(&thread1, NULL, receiver, NULL);
    pthread_create(&thread2, NULL, sender, NULL);

    // Oczekiwanie na zakończenie wątków
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
