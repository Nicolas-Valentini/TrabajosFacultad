## Organizacion del Computador 2
Este proyecto fue desarrollado en la asignatura de Organización del Computador 2 y consistió en la creación de un sistema operativo que puede ser ejecutado dentro de una máquina virtual Bochs. Dicha máquina virtual emula la funcionalidad de un procesador Intel 8086. El proyecto incluye la creación de una estructura de kernel, la implementación de la transición del modo real al modo protegido, el diseño de un sistema de interrupciones, la capacidad de paginación y la implementación de un planificador de tareas personalizado.

## Bochs
Para este programa es necesario Bochs 2.7.

Para eso primero es necesario instalar dependecias que puedan faltar 

```bash
sudo apt-get install xorg-dev libx11-dev libxrandr-dev libgtk2.0-dev libreadline-dev
```

Bajar el codigo fuente bochs-2.7.tar.gz de https://sourceforge.net/projects/bochs/files/bochs/2.7/

Descomprimirlo 
```bash
tar -xvf bochs-2.7.tar.gz
```
En la carpeta descomprimida hacer:
```bash
./configure --enable-debugger --disable-docbook --enable-readline \--prefix=$HOME/bochs/
```
```bash
make
```
```bash
make install
```

Para hacer accesible bochs desde cualquier ubicacion, agregar la siguiente linea al final del archivo
.bachrc (localizado en nuestro home)
```bash
export PATH="$HOME/bochs/bin/:$PATH"
```

Para releer al archivo .bashrc en la terminal actual:
```bash
source ∼/.bashrc
```

Listo! ya se puede ejecutar bochs
```bash
bochs
```



