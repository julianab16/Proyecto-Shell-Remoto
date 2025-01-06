#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "comandos.h"
#include <limits.h>
#define BUFFER_SIZE 3000
#define PORT 8080


int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char result[BUFFER_SIZE] = {0};
    char previous_dir[BUFFER_SIZE] = "";

    // Guarda el directorio actual
    if (getcwd(previous_dir, sizeof(previous_dir)) == NULL) {
          perror("Error al obtener el directorio inicial");
          exit(EXIT_FAILURE);
    }

    // Crear socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }
    printf("Server socket creado satisfactoriamente.\n");

    // Configurar la dirección y puerto
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Asignar el socket al puerto
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Error en bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Escuchar conexiones
    if (listen(server_fd, 3) < 0) {
        perror("Error en listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Esperando comandos del cliente...\n");

    // Aceptar una conexión
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("Error al aceptar conexión");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Nueva conexión aceptada\n");

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        memset(result, 0, BUFFER_SIZE);

        // Leer comando del cliente
        if (read(new_socket, buffer, BUFFER_SIZE) <= 0) {
            printf("Cliente desconectado.\n");
            break;
        }

        // Remover salto de línea al final del comando
        buffer[strcspn(buffer, "\n")] = '\0';

        printf("\nComando recibido: %s\n", buffer);

        // Comando "exit" para cerrar la conexión
        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Cliente desconectado.\n");
            break;
        }
        // Procesar comandos no soportados
        if (!is_command_supported(buffer) && strncmp(buffer, "help", 4) != 0) {
            snprintf(result, BUFFER_SIZE, "Comando no soportado. Use 'help' para ver los comandos disponibles.\n");
        } else if (strncmp(buffer, "cd", 2) == 0) {
            char *path = buffer + 2;
            while (*path == ' ') path++;

            char current_dir[BUFFER_SIZE];

            if (getcwd(current_dir, sizeof(current_dir)) == NULL) {
                snprintf(result, BUFFER_SIZE, "Error al obtener el directorio actual.\n");

            } else if (strcmp(path, "") == 0) {
                // Manejar cd
                if (strlen(previous_dir) == 0) {
                        snprintf(result, BUFFER_SIZE, "No hay directorio anterior registrado.\n");
                } else if (chdir(previous_dir) == 0) {
                        snprintf(result, BUFFER_SIZE, "Directorio cambiado a: %.900s\n", previous_dir);
                        strncpy(previous_dir, current_dir, BUFFER_SIZE); // Actualizar el directorio anterior
                } else {
                        snprintf(result, BUFFER_SIZE, "Error al cambiar al directorio anterior: %.900s\\n", previous_dir);
                }
            } else {
               // Cambiar de directorio
               if (chdir(path) == 0) {
                char cwd[BUFFER_SIZE];
                if (getcwd(cwd, sizeof(cwd)) != NULL) {
                        snprintf(result, BUFFER_SIZE, "Directorio cambiado a: %.900s\n", cwd);
                } else {
                    snprintf(result, BUFFER_SIZE, "No se pudo obtener la ruta actual.\n");
                }
            } else {
                snprintf(result, BUFFER_SIZE, "Error al cambiar al directorio: %s\n", path);
                        }
                }
        // Muestra los comandos desponibles
        } else if (strncmp(buffer, "help ", 4) == 0) {
                if (strcmp(buffer, "help") == 0) {
                        snprintf(result, BUFFER_SIZE, "Comandos disponibles:\n\n");
                        for (int i = 0; i < NUM_SUPPORTED_COMMANDS; i++) {
                                snprintf(result + strlen(result), BUFFER_SIZE - strlen(result),
                                "%s - %s\n", SUPPORTED_COMMANDS[i].name, SUPPORTED_COMMANDS[i].description);
                }
                strncat(result, "\nUsa 'help <comando>' para más información sobre un comando específico.\n",
                BUFFER_SIZE - strlen(result) - 1);
                } else {
                        const char *cmd = buffer + 5;
                        print_command_help(result, cmd);
                        }
        } else {
            // Ejecutar comandos con popen
            FILE *fp = popen(buffer, "r");
            if (fp == NULL) {
                snprintf(result, BUFFER_SIZE, "Error al ejecutar el comando.\n");
            } else {
                size_t read_bytes = fread(result, 1, BUFFER_SIZE - 1, fp);
                if (read_bytes == 0) {
                    snprintf(result, BUFFER_SIZE, "Comando ejecutado con éxito.\n");
                }
                pclose(fp);
            }
        }

        // Enviar resultado al cliente
        send(new_socket, result, strlen(result), 0);
    }

    close(new_socket);
    close(server_fd);
    return 0;
}
