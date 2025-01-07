# Proyecto-Shell-Remoto
## Autores 
- **Juliana Melissa Bolaños Araujo** 
- **Gabriela Guzman Botina** 
- **Laura Stefania Salazar Blanco**

## Implementación
Asegúrarse de estar trabajando en un entorno Linux. Si se está utilizando Windows, se puede descargar e instalar una distribución de Linux como Ubuntu, ya sea mediante WSL o utilizando una máquina virtual.

Instrucciones sobre cómo ejecutar el proyecto en el sistema local.

1. Clona el repositorio:
   ```bash
   git clone https://github.com/julianab16/Proyecto-Shell-Remoto.git
   ```
2. Entrar al directorio del proyecto:
   ```bash
   cd Proyecto-Shell-Remoto
   ```
3. Compila y ejecuta el servidor:

   Primero, en una ventana de terminal, compila el servidor:
   ```bash
   gcc -o servidor servidor.c
   ```

   Luego, ejecuta el servidor:
   ```bash
   ./servidor
   ```

4. Compila y ejecuta el cliente:
   En otra ventana de terminal, compila el cliente:
   
   ```bash
   gcc -o cliente cliente.c
   ```
   
   Luego, ejecuta el cliente:
   ```bash
   ./cliente
   ```


