#ifndef COMANDOS_H
#define COMANDOS_H
#include <stdbool.h>
#include <string.h>

// Estructura para definir un comando
typedef struct {
    const char* name;          // Nombre del comando
    const char* description;   // Descripción del comando
    const char* syntax;        // Sintaxis de uso
} Command;

// Lista de comandos soportados
static const Command SUPPORTED_COMMANDS[] = {
    { .name = "cd", .description = "Cambia el directorio de trabajo actual", .syntax = "cd <ruta>" },
    { .name = "ls", .description = "Lista el contenido del directorio actual", .syntax = "ls [opciones]" },
    { .name = "pwd", .description = "Muestra el directorio de trabajo actual", .syntax = "pwd" },
    { .name = "cat", .description = "Muestra el contenido de un archivo", .syntax = "cat <archivo>" },
    { .name = "mkdir", .description = "Crea un nuevo directorio", .syntax = "mkdir <nombre_directorio>" },
    { .name = "rm", .description = "Elimina archivos o directorios", .syntax = "rm [opciones] <archivo>" },
    { .name = "touch", .description = "Crea un nuevo archivo", .syntax = "touch <nombre_archivo>" },
    { .name = "cp", .description = "Copia archivos o directorios", .syntax = "cp [opciones] <origen> <destino>" },
    { .name = "mv", .description = "Mueve o renombra archivos o directorios", .syntax = "mv <origen> <destino>" },
    { .name = "grep", .description = "Busca patrones en archivos", .syntax = "grep [opciones] <patrón> <archivo>"},
    { .name = "ps", .description = "Muestra los procesos en ejecución", .syntax = "ps [opciones]" },
    { .name = "date", .description = "Obtiene la fecha y hora actual", .syntax = "date" },
    { .name = "exit", .description = "Cierra la conexión con el servidor", .syntax = "exit" }
};

// Número total de comandos soportados
#define NUM_SUPPORTED_COMMANDS (sizeof(SUPPORTED_COMMANDS) / sizeof(Command))

// Funciones de utilidad
static bool is_command_supported(const char* cmd) {
    char command[256];
    sscanf(cmd, "%s", command); // Obtiene el primer token (nombre del comando)

    for(int i = 0; i < NUM_SUPPORTED_COMMANDS; i++) {
        if(strcmp(command, SUPPORTED_COMMANDS[i].name) == 0) {
            return true;
        }
    }
    return false;
}

static const Command* get_command_info(const char* cmd) {
    char command[256];
    sscanf(cmd, "%s", command);

    for(int i = 0; i < NUM_SUPPORTED_COMMANDS; i++) {
        if(strcmp(command, SUPPORTED_COMMANDS[i].name) == 0) {
            return &SUPPORTED_COMMANDS[i];
        }
    }
    return NULL;
}

// Función para imprimir ayuda sobre un comando específico
static void print_command_help(char* buffer, const char* cmd) {
    const Command* command = get_command_info(cmd);
    if(command) {
        sprintf(buffer,
                "Comando: %s\n"
                "Descripción: %s\n"
                "Sintaxis: %s\n",
                command->name,
                command->description,
                command->syntax);
    } else {
        sprintf(buffer, "Comando no encontrado: %s\n", cmd);
    }
}

#endif // COMANDOS_H
