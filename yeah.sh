#!/bin/bash

# Verifica si el archivo "part1" existe y lo elimina si es así
if [ -f "part1" ]; then
    rm part1
fi

if [ -f "screens_app" ]; then
	rm screens_app
fi

# Limpia y compila el proyecto
make clean && make

# Cambia el nombre del archivo "part1" a "screens"
if [ -f "part1" ]; then
	mv part1 screens_app
	# Copia el archivo "screens_app" a la ubicación deseada en el datafono
	sshpass -p uno.2.tres scp screens_app root@192.168.186.122:~/dev/tests
else
	echo "No se pudo encontrar el archivo, ejecuta nuevamente el script"
fi

