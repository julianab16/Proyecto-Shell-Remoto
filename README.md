# Proyecto-Shell-Remoto
## Autores 
- **Juliana Melissa Bolaños Araujo** 
- **Gabriela Guzman Botina** 
- **Laura Stefania Salazar Blanco**
## Funcionamiento

## Implemnetación

Asegúrate de estar trabajando en un entorno Linux. Si estás utilizando Windows, puedes descargar e instalar una distribución de Linux como Ubuntu, ya sea mediante WSL (Windows Subsystem for Linux) o utilizando una máquina virtual.


Instrucciones sobre cómo ejecutar el proyecto en el sistema local.

1. Clona el repositorio:
   ```bash
   git clone https://github.com/julianab16/Proyecto-Shell-Remoto.git
   ```
2. Entrar al directorio del proyecto:
   ```bash
   cd Proyecto-Shell-Remoto
   ```
3. Ejecute los siguentes comandos:
   
   Primero el server en una ventana
   ```bash
   gcc -o server server.c
   ```
   Iniciar el servidor
   ```bash
   ./server
   ```

   Despues el cliente en otra ventana
   ```bash
   gcc -o cliente cliente.c
   ```
   Iniciar el cliente
   ```bash
   ./cliente
   ```


