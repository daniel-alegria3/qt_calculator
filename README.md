# Calculadora en Qt

Este repositorio esta hecho para el projecto Nro. 1 del curso de 'Desarrollo de
Software' del 7mo de la UNSAAC.

## Dependencias
- [Qt](https://www.qt.io/download-dev)

## Construccion
El codigo esta usando [Cmake](https://cmake.org/) y [GCC](https://gcc.gnu.org/)
para generar un ejecutable de linux. Para distribuciones basadas en Archlinux,
correr:

```sh
sudo pacman -S qt6 cmake ninja base-devel
```

Correr `make` dentro del projecto y el ejecutable './build/calculator' deberia
crearse.

## 'Manual' de Usuario
Ingresar una expresion en la entrada; ya sea mediante el teclado o los botones.
Notar que la entrada no dejara entrar characteres desconocidos.

<div align="center">
  <video style="width: 100%; height: auto;" controls>
    <source src="demo.mkv" type="video/x-matroska">
    demo.mkv
  </video>
</div>

