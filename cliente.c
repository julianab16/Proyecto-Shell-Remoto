#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    int e = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    char response[BUFFER_SIZE] = {0};

    // Crear socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }
    printf("Server socket creado satisfactoriamente.\n");
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convertir dirección IP a binario
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Dirección no válida o no soportada");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Conectar al servidor
    if ((e = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        perror("Error al conectar con el servidor");
        close(sock);
        exit(EXIT_FAILURE);
    }

    printf("Conectado al servidor. Ingresa 'exit' para salir.\n");

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        memset(response, 0, BUFFER_SIZE);

        printf("Ingresa un comando: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // Enviar comando al servidor
        send(sock, buffer, strlen(buffer), 0);

        if (strcmp(buffer, "exit\n") == 0) {
            printf("\nSaliendo...\n");
            break;
        }

        // Leer respuesta del servidor
        read(sock, response, BUFFER_SIZE);
        printf("\nRespuesta del servidor:\n%s\n", response);
    }

    close(sock);
    return 0;
}