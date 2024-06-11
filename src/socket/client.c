#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 63333
#define BUFFER_SIZE 2048
#define SERVER_IP "127.0.0.1"

typedef struct {
    char name[50];
    char message[200];
} ClientMessage;

void send_message(int socket, ClientMessage *client_msg) {
    send(socket, client_msg, sizeof(ClientMessage), 0);
}

void *receive_messages(void *socket) {
    int client_socket = *((int *)socket);
    ClientMessage client_msg;
    int bytes_read;

    while ((bytes_read = recv(client_socket, &client_msg, sizeof(ClientMessage), 0)) > 0) {
        printf("[%s]: %s\n", client_msg.name, client_msg.message);
    }

    return NULL;
}

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    ClientMessage client_msg;
    pthread_t recv_thread;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        printf("Cannot connect to server!\n");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");

    printf("Enter your name: ");
    fgets(client_msg.name, 50, stdin);
    client_msg.name[strcspn(client_msg.name, "\n")] = 0;  // Remove newline character

    pthread_create(&recv_thread, NULL, &receive_messages, (void *)&client_socket);
    printf("Joined the chat group\n");

    while (1) {
        fgets(client_msg.message, 200, stdin);
        client_msg.message[strcspn(client_msg.message, "\n")] = 0;  // Remove newline character

        if (strcmp(client_msg.message, "exit") == 0) {
            break;
        }

        send_message(client_socket, &client_msg);
    }

    close(client_socket);
    return 0;
}
