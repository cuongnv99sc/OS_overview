#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 63333
#define BUFFER_SIZE 2048
#define MAX_CLIENTS 5

typedef struct {
    char name[50];
    char message[200];
} ClientMessage;

int client_sockets[MAX_CLIENTS];
int client_count = 0;
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void broadcast_message(ClientMessage *client_msg, int sender_socket) {
    pthread_mutex_lock(&clients_mutex);

    for (int i = 0; i < client_count; i++) {
        if (client_sockets[i] != sender_socket) {
            if (send(client_sockets[i], client_msg, sizeof(ClientMessage), 0) == -1) {
                perror("send");
            }
        }
    }

    pthread_mutex_unlock(&clients_mutex);
}

void *handle_client(void *client_socket) {
    int sock = *((int *)client_socket);
    ClientMessage client_msg;
    int bytes_read;

    while ((bytes_read = recv(sock, &client_msg, sizeof(ClientMessage), 0)) > 0) {
        printf("Received message from %s: %s\n", client_msg.name, client_msg.message);
        broadcast_message(&client_msg, sock);
    }

    // Remove client from the list
    pthread_mutex_lock(&clients_mutex);

    for (int i = 0; i < client_count; i++) {
        if (client_sockets[i] == sock) {
            for (int j = i; j < client_count - 1; j++) {
                client_sockets[j] = client_sockets[j + 1];
            }
            client_count--;
            break;
        }
    }

    pthread_mutex_unlock(&clients_mutex);
    close(sock);

    return NULL;
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    pthread_t tid;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 10) == -1) {
        perror("listen");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_size);
        if (client_socket == -1) {
            perror("accept");
            continue;
        }

        pthread_mutex_lock(&clients_mutex);

        if (client_count < MAX_CLIENTS) {
            client_sockets[client_count++] = client_socket;
            pthread_create(&tid, NULL, &handle_client, (void *)&client_socket);
        } else {
            fprintf(stderr, "Max clients reached. Rejecting: %d\n", client_socket);
            close(client_socket);
        }

        pthread_mutex_unlock(&clients_mutex);
    }

    close(server_socket);
    return 0;
}
