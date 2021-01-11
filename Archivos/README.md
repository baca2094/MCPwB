# Milk Collection Problem with Blending

En este proyecto se llevó a cabo la resolución del MCPwB utilizando como técnica un algoritmo evolutivo.

## Modo de uso

Para utilizar el programa se debe, en primer lugar, crear el archivo ejecutable. Esto se lleva a cabo a través del comando `make` en la misma carpeta que se encuentra este Readme.

Tras ejecutar este comando, se generará un ejecutable llamado *MCPwB*. Este ejecutable recibe 2 parámetros:

* La ruta a la instancia con la información a cargar.
* El número de iteraciones.

Un ejemplo de ejecución es el siguiente:

```bash
./MCPwB ../Instancias/eil22.txt 1000
```
Tras esto, el código empezará a ejecutarse y, tras un tiempo, entregará el resultado. Un ejemplo de esto:

```bash
./MCPwB ../Instancias/eil22.txt 100
9601.18 4834.1 1426.61 = 15861.9

1-14-5-2-8-11-17-20-1 198.817 9800 A
1-21-18-15-3-6-12-9-1 205.896 7200 B
1-4-7-10-22-19-13-16-1 223.391 5500 C

```

Para eliminar los archivos de compilación se debe ejecutar el comando `make clean` por consola.
