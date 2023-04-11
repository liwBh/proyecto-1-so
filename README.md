# Instalación de Libreria

### Comandos de instalación Terminal Librerias

``` sudo apt-get update ```

```sudo apt-get install libgstreamer1.0-dev```

```sudo apt-get install gstreamer1.0-plugins-bad```


### Comandos de instalación Terminal Librerias opcionales

```sudo apt install snapd```

```sudo snap install gstreamer --edge```

### Comandos para compilar en terminal

```gcc -o main main.c $(pkg-config --cflags --libs gstreamer-1.0)```

```./main```